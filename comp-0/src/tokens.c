#include "str-util.c"

int get_length(char* str){
    int index = 0;
    while (str[index] != '\0'){index++;}
    return index;
}

int is_token_type(char* str, int length, int token_type){
    switch (token_type){        case 0: // "TYPE"
            char* tokens_0[5] = {"int","float","bool","string","void"};
            for (int i = 0; i < 5; i++){
                int t_length = get_length(tokens_0[i]);
                if (length >= t_length && equals_l(tokens_0[i], str, length)){
                    return 1;
                }
            }
            return 0;
        case 1: // "ASSIGNMENT_OP"
            char* tokens_1[4] = {"+=","-=","*=","/="};
            for (int i = 0; i < 4; i++){
                int t_length = get_length(tokens_1[i]);
                if (length >= t_length && equals_l(tokens_1[i], str, length)){
                    return 1;
                }
            }
            return 0;
        case 2: // "UNARY_ASSIGNMENT_OP"
            char* tokens_2[2] = {"++","--"};
            for (int i = 0; i < 2; i++){
                int t_length = get_length(tokens_2[i]);
                if (length >= t_length && equals_l(tokens_2[i], str, length)){
                    return 1;
                }
            }
            return 0;
        case 3: // "ADD_OP"
            char* tokens_3[2] = {"+","-"};
            for (int i = 0; i < 2; i++){
                int t_length = get_length(tokens_3[i]);
                if (length >= t_length && equals_l(tokens_3[i], str, length)){
                    return 1;
                }
            }
            return 0;
        case 4: // "MUL_OP"
            char* tokens_4[3] = {"*","/","%"};
            for (int i = 0; i < 3; i++){
                int t_length = get_length(tokens_4[i]);
                if (length >= t_length && equals_l(tokens_4[i], str, length)){
                    return 1;
                }
            }
            return 0;
        case 5: // "REL_OP"
            char* tokens_5[5] = {"<",">","==",">=","<="};
            for (int i = 0; i < 5; i++){
                int t_length = get_length(tokens_5[i]);
                if (length >= t_length && equals_l(tokens_5[i], str, length)){
                    return 1;
                }
            }
            return 0;
        case 6: // "CONSTANT"
            char* tokens_6[20] = {"=",",",";","(",")","[","]","{","}","*","if","else","while","for","struct","true","false","&&","||","!"};
            for (int i = 0; i < 20; i++){
                int t_length = get_length(tokens_6[i]);
                if (length >= t_length && equals_l(tokens_6[i], str, length)){
                    return 1;
                }
            }
            return 0;
        case 7: // VARIABLE/METHOD NAMES
            return is_name(str, length);
        case 8: // NUMBERS
            return is_number(str, length, 0);
        case 9: // STRINGS
            return is_valid_string(str, length);
        default:
            return 0;
    }
}

#define NUM_TOKEN_TYPES 11
char* type_names[NUM_TOKEN_TYPES] = {"type","assignment_op","unary_assignment_op","add_op","mul_op","rel_op","constant","name","number","string_literal","end"};