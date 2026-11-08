from dataclasses import dataclass

with open('config/cfg.txt', 'r') as f:
    data = f.read().split('\n')
token_types = data[0].split(',')
data = data[1:]
cfg = {}
for line in data:
    if line:
        spl = line.split('---')
        cfg[spl[0].strip()] = spl[1].strip().split('$')
        cfg[spl[0].strip()] = [el.strip().split(' ') for el in cfg[spl[0].strip()]]

first_dict = {}
follow_dict = {}

def get_constant_tokens():
    with open('config/tokens.txt', 'r') as f:
        lines = f.read().split('\n')
        for line in lines:
            if line.startswith('constant'):
                return line.split(' ')[1:]

def first(prod, seen):
    first_set = set()
    if isinstance(prod, str):
        if prod in seen:
            return first_set
        seen.add(prod)
        for p in cfg[prod[1:]]:
            if p[0].startswith('`') and not p[0][1:] in token_types:
                    first_set.update(first(p, seen))
            else:
                first_set.add(p[0])
        return first_set
    else:
        # if len(prod) == 0:
        #     first_set.add('`epsilon')
        #     return first_set
        index = 0
        ret = False
        while index < len(prod) and not ret:
            if prod[index].startswith('`') and not prod[index][1:] in token_types:
                sub_first = first(prod[index], seen)
                if "`epsilon" in sub_first:
                    ret = False
                    sub_first.remove('`epsilon')
                else:
                    ret = True
                first_set.update(sub_first)
            else:
                first_set.add(prod[index])
                ret = True
            index += 1
        if index >= len(prod) and not ret:
            first_set.add('`epsilon')
        return first_set

@dataclass(frozen=True)
class ProdState:
    prod_name: str
    prod: tuple
    index: int
    next_token: str

    def __repr__(self):
        string = f"[{self.prod_name} -> "
        for i, el in enumerate(self.prod):
            string += " "
            if self.index == i:
                string += "."
            string += el
        if self.index >= len(prod):
            string += "."
        return f"{string} , {self.next_token}]"

def closure(prod_states):
    made_changes = False
    closure_set = prod_states.copy()
    for prod_state in prod_states:
        if prod_state.index < len(prod_state.prod) and prod_state.prod[prod_state.index].startswith('`') and not prod_state.prod[prod_state.index][1:] in token_types:
            name = prod_state.prod[prod_state.index]
            for p in cfg[name[1:]]:
                for e in follow_dict[name[1:]]:
                    ps = ProdState(name, tuple(p), 0, e)
                    if not ps in closure_set:
                        made_changes = True
                    closure_set.add(ps)
        elif prod_state.index < len(prod_state.prod) and prod_state.prod[prod_state.index] == '`epsilon':
            ps = ProdState(prod_state.prod_name, prod_state.prod, prod_state.index + 1, prod_state.next_token)
            if not ps in closure_set:
                made_changes = True
            closure_set.add(ps)
    return closure_set, made_changes

def total_closure(prod_states):
    changes = True
    while changes:
        prod_states, changes = closure(prod_states)
    return prod_states

def goto(prod_states, input):
    new_state = set()
    for prod_state in prod_states:
        if prod_state.index < len(prod_state.prod) and prod_state.prod[prod_state.index] == input:
            new_state.add(ProdState(prod_state.prod_name, prod_state.prod, prod_state.index + 1, prod_state.next_token))
    return new_state

def generate_states(initial_state):
    transitions = {}
    all_states = {initial_state: 0}
    queue = [initial_state]
    while len(queue) > 0:
        state = queue.pop(0)
        old_id = all_states[state]
        for valid_symbol in VALID_SYMBOLS:
            new_state = frozenset(total_closure(goto(state, valid_symbol)))
            if new_state in all_states:
                new_id = all_states[new_state]
            else:
                new_id = len(all_states)
                all_states[new_state] = new_id
                queue.append(new_state)
            transitions[(old_id, valid_symbol)] = new_id
    return all_states, transitions

for key in cfg.keys():
    first_dict[key] = first(f"`{key}", set())
    follow_dict[key] = set()
changes = True
while changes:
    changes = False
    for key in cfg.keys():
        for k in cfg.keys():
            for prod in cfg[k]:
                try:
                    follow_set = first(prod[(prod.index(f"`{key}") + 1):],set())
                    if "`epsilon" in follow_set:
                        follow_set.remove("`epsilon")
                        follow_set.update(follow_dict[k])
                    prev = follow_dict[key].copy()
                    follow_dict[key].update(follow_set)
                    if prev != follow_dict[key]:
                        changes = True
                except ValueError:
                    continue
follow_dict['program'].add('`end')

terminals = [f"`{tt}" for tt in token_types]
terminals.extend(get_constant_tokens())
nonterminals = [f"`{key}" for key in list(cfg.keys())]
VALID_SYMBOLS = [f"`{key}" for key in cfg.keys()]
VALID_SYMBOLS.extend(terminals)

initial_state = set()
initial_state.add(ProdState(prod_name='S', prod=tuple(['`program']), index=0, next_token='`end'))
initial_state = total_closure(initial_state)

all_states, transitions = generate_states(frozenset(initial_state))
state_id_lookup = {value: key for key, value in all_states.items()}
action_table = []
goto_table = []
for i in range(len(all_states)):
    action_table.append([("",)] * len(terminals))
    goto_table.append([-1] * len(nonterminals))
actions = {"ACCEPT": 0, "SHIFT": 1, "REDUCE": 2}
for state_id in state_id_lookup:
    state = state_id_lookup[state_id]
    for prod_state in state:
        if prod_state.index >= len(prod_state.prod):
            next_token_index = terminals.index(prod_state.next_token)
            if action_table[state_id][next_token_index][0] != "":
                print(f"Reduce conflict when reducing {prod_state.prod_name} -> {' '.join(prod_state.prod)} with token \"{prod_state.next_token}\" from state {state_id}.  Existing action:")
                print(action_table[state_id][next_token_index])
            if prod_state.prod_name == 'S' and prod_state.index > 0:
                action_table[state_id][next_token_index] = ("ACCEPT",)
            else:
                action_table[state_id][next_token_index] = ("REDUCE", prod_state.prod_name, prod_state.prod)
        elif prod_state.prod[prod_state.index] in terminals:
            action_table[state_id][terminals.index(prod_state.prod[prod_state.index])] = ("SHIFT", transitions[(state_id, prod_state.prod[prod_state.index])])
for transition_key in transitions.keys():
    if transition_key[1] in nonterminals:
        goto_table[transition_key[0]][nonterminals.index(transition_key[1])] = transitions[transition_key]

c_content = """
char* empty = "";
"""
cfg_array = ""
for i, nonterminal in enumerate(nonterminals):
    nonterminal_array = ""
    for j, production in enumerate(cfg[nonterminal[1:]]):
        c_content += f"char* prod_{i}_{j}[{len(production) + 1}] = {{{','.join([f'\"{el}\"' for el in production])},\"\"}};\n"
        nonterminal_array += f"prod_{i}_{j},"
    c_content += f"char** prod_{i}[{len(cfg[nonterminal[1:]]) + 1}] = {{{nonterminal_array[:-1]},&empty}};\n"
    cfg_array += f"prod_{i},"
c_content += f"char*** full_cfg[{len(nonterminals)}] = {{{cfg_array[:-1]}}};\n\n"
c_content += f"#define NUM_NON_TERMINALS {len(nonterminals)}\n"
c_content += f"#define NUM_TERMINALS {len(terminals)}\n"
c_content += f"#define NUM_STATES {len(state_id_lookup)}\n"
for key in actions.keys():
    c_content += f"#define {key} {actions[key]}\n"
c_content += f"char* terminals[NUM_TERMINALS] = {{{','.join([f'\"{t[1:] if t.startswith('`') else t}\"' for t in terminals])}}};\n"
c_content += f"char* non_terminals[NUM_NON_TERMINALS] = {{{','.join([f'\"{t[1:]}\"' for t in nonterminals])}}};\n"

action_array = ""
for i in range(len(state_id_lookup)):
    action_array += "{"
    for j, action in enumerate(action_table[i]):
        if action[0] == 'ACCEPT':
            action_array += f"{{{actions['ACCEPT']},0,0}},"
        elif action[0] == 'REDUCE':
            prod_index = -1
            for k, prod in enumerate(cfg[action[1][1:]]):
                if tuple(prod) == action[2]:
                    prod_index = k
            if prod_index == -1:
                print(f"Unable to find production index for {action[1][1:]} -> \"{action[2]}\"")
                exit(1)
            action_array += f"{{{actions['REDUCE']},{nonterminals.index(action[1])},{prod_index}}},"
        elif action[0] == 'SHIFT':
            action_array += f"{{{actions['SHIFT']},{action[1]},0}},"
        else:
            action_array += f"{{-1,0,0}},"
    action_array = f"{action_array[:-1]}}},\n"
c_content += f"int action_table[NUM_STATES][NUM_TERMINALS][3] = {{{action_array[:-1]}}};\n\n"

goto_array = ""
for i in range(len(state_id_lookup)):
    goto_array += f"{{{','.join([str(e) for e in goto_table[i]])}}},\n"
c_content += f"int goto_table[NUM_STATES][NUM_NON_TERMINALS] = {{{goto_array[:-2]}}};\n"

with open('src/cfg.c', 'w') as f:
    f.write(c_content)

with open('debug/states.txt', 'w') as f:
    for key in state_id_lookup.keys():
        f.write(f"State {key}:\n")
        for prod_state in state_id_lookup[key]:
            f.write(f"{prod_state}\n")