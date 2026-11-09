with open('config/jvm.txt', 'r') as f:
    lines = f.read().split('\n')
with open('config/cfg.txt', 'r') as f:
    nonterminals = [line.split('---')[0] for line in f.read().split('\n') if line]
nonterminals.append('type_conversion')
nonterminals = nonterminals[1:]

def run_command(command):
    if command[0] == 'generate':
        index = command[1].split('_')[-1]
        return f"    generate(fptr, ((struct SAST_Node*)(node->children[{index}])));\n"
    elif command[0] == 'jvm_raw_type':
        index = command[1].split('_')[-1]
        return f"    fprintf(fptr, \"%s\", jvm_type(((struct Token*)(node->children[{index}]))->token));\n"
    elif command[0] == 'jvm_type':
        index = command[1].split('_')[-1]
        return f"    fprintf(fptr, \"%s\", jvm_type(((struct SAST_Node*)(node->children[{index}]))->data_type));\n"
    elif command[0] == 'jvm_arith':
        index = command[1].split('_')[-1]
        return f"    fprintf(fptr, \"%s\", jvm_arith(((struct Token*)(node->children[{index}]))->token));\n"
    elif command[0] == 'jvm_rel':
        index = command[1].split('_')[-1]
        return f"    fprintf(fptr, \"%s\", jvm_rel(((struct Token*)(node->children[{index}]))->token));\n"
    elif command[0] == 'index':
        return f"    fprintf(fptr, \"%d\", ((struct Variable*)(((struct Token*)(node->children[0]))->data))->index));\n"
    elif command[0] == 'function_id':
        return f"    fprintf(fptr, \"%d\", ((struct Function*)(((struct Token*)(node->children[0]))->data))->id));\n"
    elif command[0] == 'cache-counter':
        return f"    int {command[1]} = increment_counter();\n"
    elif command[0] == 'var':
        return f"    fprintf(fptr, \"%d\", {command[1]});\n"
    elif command[0] == 'convert':
        index1 = command[1].split('_')[-1]
        index2 = command[2].split('_')[-1]
        return f"    fprintf(fptr, \"%s\\n\", get_convert(((struct SAST_Node*)(node->children[{index1}]))->data_type), ((struct SAST_Node*)(node->children[{index2}]))->data_type)));\n"
    elif command[0] == 'value':
        index = command[1].split('_')[-1]
        return f"    fprintf(fptr, \"%s\", ((struct Token*)(node->children[{index}]))->token);\n"
    else:
        print(f"Unknown command {' '.join(command)}")
        exit(1)
    


code_generations = {}
latest_prod = ()
for line in lines:
    if line:
        if not line.startswith("    "):
            prod_name = '_'.join(line[:-1].split('_')[:-1])
            prod_index = line[:-1].split('_')[-1]
            latest_prod = (prod_name, prod_index)
            if not prod_name in code_generations:
                code_generations[prod_name] = {}
        else:
            if not latest_prod[1] in code_generations[latest_prod[0]]:
                code_generations[latest_prod[0]][latest_prod[1]] = [line]
            else:
                code_generations[latest_prod[0]][latest_prod[1]].append(line)

exceptions = {'function_call', 'param_declarations', 'params'}
for nonterminal in nonterminals:
    if not nonterminal in code_generations and not nonterminal in exceptions:
        print(f"No generation found for production \"{nonterminal}\"")
        exit(1)

c_content = "#include generator-misc.c\n"

for key in code_generations:
    key_index = nonterminals.index(key)
    switch_content = "    switch (prod_index){\n"
    for prod_index in code_generations[key]:
        c_content += f"void generate_{key_index}_{prod_index}(FILE* fptr, struct SAST_Node* node){{ // {key.upper()}_{prod_index}\n"
        for line in code_generations[key][prod_index]:
            line = line[4:]
            while line:
                insertion_index = line.find("{{")
                if insertion_index < 0:
                    c_content += f"    fprintf(fptr, \"{line}\");\n"
                    line = ""
                else:
                    c_content += f"    fprintf(fptr, \"{line[:insertion_index]}\");\n"
                    exit_index = line.find("}}")
                    c_content += run_command(line[(insertion_index + 2):exit_index].split(' '))
                    line = line[(exit_index + 2):]
            c_content += f"    fprintf(fptr, \"\\n\");\n"
        c_content += "}\n\n"
        switch_content += f"""        case {prod_index}:
            generate_{key_index}_{prod_index}(fptr, node);
            return;
"""
    switch_content += """        default:
            printf(\"Unknown production index\");
            exit(1);
    }\n"""
    c_content += f"void generate_{key_index}(FILE* fptr, struct SAST_Node* node, int prod_index){{ // {key.upper()}\n{switch_content}}}\n\n"



with open('src/generator.c', 'w') as f:
    f.write(c_content)