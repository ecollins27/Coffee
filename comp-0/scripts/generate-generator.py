with open('config/jvm.txt', 'r') as f:
    lines = f.read().split('\n')
with open('config/cfg.txt', 'r') as f:
    nonterminals = [line.split('---')[0] for line in f.read().split('\n') if line]
exceptions = {'param_declarations', 'type'}
nonterminals.append('type_conversion')
nonterminals = nonterminals[1:]

def run_command(command):
    if command[0] == 'generate':
        index = command[1].split('_')[-1]
        return f"    generate(fptr, (struct SAST_Node*)(node->children[{index}]), variables, functions);\n"
    elif command[0] == 'jvm_raw_type':
        index = command[1].split('_')[-1]
        return f"    fprintf(fptr, \"%s\", jvm_raw_type(((struct Token*)(node->children[{index}]))->token));\n"
    elif command[0] == 'jvm_var_type':
        index = command[1].split('_')[-1]
        return f"    fprintf(fptr, \"%s\", jvm_type(get_variable_by_id(variables, ((struct Token*)(node->children[{index}]))->data)->type));\n"
    elif command[0] == 'jvm_type':
        index = command[1].split('_')[-1]
        return f"    fprintf(fptr, \"%s\", jvm_type(((struct SAST_Node*)(node->children[{index}]))->type));\n"
    elif command[0] == 'jvm_arith':
        index = command[1].split('_')[-1]
        return f"    fprintf(fptr, \"%s\", jvm_arith(((struct Token*)(node->children[{index}]))->token));\n"
    elif command[0] == 'jvm_rel':
        index = command[1].split('_')[-1]
        return f"    fprintf(fptr, \"%s\", jvm_rel(((struct Token*)(node->children[{index}]))->token));\n"
    elif command[0] == 'index':
        index = command[1].split('_')[-1]
        return f"    fprintf(fptr, \"%d\", get_variable_by_id(variables, ((struct Token*)(node->children[{index}]))->data)->index);\n"
    elif command[0] == 'function_id':
        return f"    fprintf(fptr, \"%d\", ((struct Token*)(node->children[0]))->data);\n"
    elif command[0] == 'cache-counter':
        return f"    int {command[1]} = increment_counter();\n"
    elif command[0] == 'var':
        return f"    fprintf(fptr, \"%d\", {command[1]});\n"
    elif command[0] == 'convert':
        index1 = command[1].split('_')[-1]
        index2 = command[2].split('_')[-1]
        return f"    fprintf(fptr, \"%s\\n\", get_convert(((struct SAST_Node*)(node->children[{index1}]))->type, ((struct SAST_Node*)(node->children[{index2}]))->type));\n"
    elif command[0] == 'signature':
        index = command[1].split('_')[-1]
        return f"    write_signature(fptr, ((struct Token*)(node->children[{index}]))->data, functions);\n"
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

for nonterminal in nonterminals:
    if not nonterminal in code_generations and not nonterminal in exceptions:
        print(f"No generation found for production \"{nonterminal}\"")
        exit(1)

c_content = "#include \"generator-misc.c\"\n"

outer_switch_content = "    switch (node->prod_index[0]){\n"
for key in code_generations:
    key_index = nonterminals.index(key)
    switch_content = "    switch (prod_index){\n"
    for prod_index in code_generations[key]:
        c_content += f"void generate_{key_index}_{prod_index}(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){{ // {key.upper()}_{prod_index}\n"
        for line in code_generations[key][prod_index]:
            line = line[4:]
            add_new_line = True
            while line:
                insertion_index = line.find("{{")
                if insertion_index < 0:
                    c_content += f"    fprintf(fptr, \"{line}\");\n"
                    line = ""
                else:
                    if line[:insertion_index]:
                        c_content += f"    fprintf(fptr, \"{line[:insertion_index]}\");\n"
                    exit_index = line.find("}}")
                    command = line[(insertion_index + 2):exit_index].split(' ')
                    c_content += run_command(command)
                    line = line[(exit_index + 2):]
                    if command[0] == 'cache-counter' or command[0] == 'generate':
                        add_new_line = False
            if add_new_line:
                c_content += f"    fprintf(fptr, \"\\n\");\n"
        c_content += "}\n\n"
        switch_content += f"""        case {prod_index}:
            generate_{key_index}_{prod_index}(fptr, node, variables, functions);
            return;
"""
    switch_content += """        default:
            printf(\"Unknown production index\");
            exit(1);
    }\n"""
    c_content += f"void generate_{key_index}(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){{ // {key.upper()}\n{switch_content}}}\n\n"
    outer_switch_content += f"""        case {key_index}:
            generate_{key_index}(fptr, node, variables, functions, node->prod_index[1]);
            return;
"""
outer_switch_content += """        default:
            printf(\"Unknown production index %d\", node->prod_index[0]);
            exit(1);
    }\n"""
c_content += f"""void generate(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){{
    if (node == NULL){{
        return;
    }}
    {outer_switch_content}
}}
    
    """



with open('src/generator.c', 'w') as f:
    f.write(c_content)