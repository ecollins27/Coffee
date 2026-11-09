with open('config/tokens.txt', 'r') as f:
    tokens = f.read().split('\n')
tokens = [[f"\"{e}\"" for e in line.split(' ')] for line in tokens]
c_content = """#include "str-util.c"

int get_length(char* str){
    int index = 0;
    while (str[index] != '\\0'){index++;}
    return index;
}

int is_token_type(char* str, int length, int token_type){
    switch (token_type){"""
for i, line in enumerate(tokens):
   c_content += f"""        case {i}: // {line[0].upper()}
            char* tokens_{i}[{len(line) - 1}] = {{{','.join(line[1:])}}};
            for (int i = 0; i < {len(line) - 1}; i++){{
                int t_length = get_length(tokens_{i}[i]);
                if (length >= t_length && equals_l(tokens_{i}[i], str, length)){{
                    return 1;
                }}
            }}
            return 0;
"""
c_content += f"""        case {len(tokens)}: // VARIABLE/METHOD NAMES
            return is_name(str, length);
        case {len(tokens) + 1}: // INTEGERS
            return is_integer(str, length, 0);
        case {len(tokens) + 2}: // FLOATS
            return is_number(str, length, 0);
        case {len(tokens) + 3}: // STRINGS
            return is_valid_string(str, length);
        default:
            return 0;
    }}
}}

#define NUM_TOKEN_TYPES {len(tokens) + 5}
"""
type_names = [f"{line[0]}" for line in tokens]
c_content += f"char* type_names[NUM_TOKEN_TYPES] = {{{','.join(type_names)},\"name\",\"int_literal\",\"float_literal\",\"string_literal\",\"end\"}};"
with open('src/tokens.c', 'w') as f:
    f.write(c_content)
with open('config/cfg.txt', 'r') as f:
    lines = f.read().split('\n')
    type_line = ','.join([type_name[1:-1] for type_name in type_names])
    type_line += ",name,int_literal,float_literal,string_literal,epsilon,end"
    lines[0] = type_line
with open('config/cfg.txt', 'w') as f:
    f.write('\n'.join(lines))