#include "validator.c"

int c = 0;
int* counter = &c;

void generate(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions);

char* jvm_raw_type(char* type){
    return type;
}

char* jvm_type(struct Type* type){
    if (equals(type->type, "array")){
        return "a";
    }
    char* ret = (char*)malloc(2 * sizeof(char));
    ret[0] = type->type[0];
    ret[1] = '\0';
    return ret;
}

char* type_descriptor(struct Type* type){
    if (equals(type->type, "void")){
        return "V";
    } else if (equals(type->type, "array")){
        char* sub_descriptor = type_descriptor(type->sub_type);
        int length = 0;
        while (sub_descriptor[length] != '\0'){length++;}
        char* desc = (char*)malloc((length + 1) * sizeof(char));
        desc[0] = '[';
        for (int i = 0; i < length; i++){
            desc[i + 1] = sub_descriptor[i];
        }
        return desc;
    } else if (equals(type->type, "int")){
        return "I";
    } else if (equals(type->type, "float")){
        return "F";
    } else if (equals(type->type, "long")){
        return "J";
    } else if (equals(type->type, "double")){
        return "D";
    } else {
        printf("Unknown type %s\n", type->type);
        exit(1);
    }
}

char* jvm_arith(char* op){
    if (op[0] == '+'){
        return "add";
    } else if (op[0] == '-'){
        return "sub";
    } else if (op[0] == '*'){
        return "mul";
    } else if (op[0] == '/'){
        return "div";
    } else {
        printf("Unknown arithmetic operator \"%s\"\n", op);
        exit(1);
    }
}

char* jvm_rel(char* op){
    if (equals(op, "<=")){
        return "cmple";
    } else if (equals(op, "<")){
        return "cmplt";
    } else if (equals(op, ">=")){
        return "cmpge";
    } else if (equals(op, ">")){
        return "cmpgt";
    } else if (equals(op, "==")){
        return "cmpeq";
    } else if (equals(op, "!=")){
        return "cmpne";
    } else {
        printf("Unknown relation operator \"%s\"\n", op);
        exit(1);
    }
}

char* get_convert(struct Type* type1, struct Type* type2){
    char* convert_instr = (char*)malloc(4 * sizeof(char));
    convert_instr[0] = jvm_type(type1)[0];
    convert_instr[1] = '2';
    convert_instr[2] = jvm_type(type2)[0];
    convert_instr[3] = '\0';
    return convert_instr;
}

int increment_counter(){
    int val = *counter;
    *counter += 1;
    return val;
}

void write_signature(FILE* fptr, int function_id, struct Function_Linked_List* functions){
    while (functions != NULL){
        if (functions->value->id == function_id){
            int predefined = 0;
            for (int i = 0; i < NUM_PREDEFINED; i++){
                if (equals(functions->value->name, predefined_functions[i])){
                    fprintf(fptr, "IO/%s(", predefined_functions[i]);
                    predefined = 1;
                }
            }
            if (!predefined){
                fprintf(fptr, "Main/function_%d(", function_id);
            }
            struct Variable_Linked_List* params = functions->value->params;
            while (params != NULL && params->prev != NULL){
                params = params->prev;
            }
            while (params != NULL){
                fprintf(fptr, "%s", type_descriptor(params->value->type));
                params = params->next;
            }
            fprintf(fptr, ")");
            if (predefined){
                fprintf(fptr, "V");
            } else {
                fprintf(fptr, "%s", type_descriptor(functions->value->return_type));
            }
            return;
        }
        functions = functions->prev;
    }
}

void generate_functions(FILE* fptr, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){
    while (functions != NULL){
        if (equals(functions->value->name, "main")){
            fprintf(fptr, ".method public static main([Ljava/lang/String;)V\n");
        } else {
            fprintf(fptr, ".method public static function_%d(", functions->value->id);
            struct Variable_Linked_List* params = functions->value->params;
            while (params != NULL && params->prev != NULL){
                params = params->prev;
            }
            while (params != NULL){
                fprintf(fptr, "%s", type_descriptor(params->value->type));
                params = params->next;
            }
            fprintf(fptr, ")");
            fprintf(fptr, "%s ;%s\n", type_descriptor(functions->value->return_type), functions->value->name);
        }
        fprintf(fptr,".limit stack 2\n.limit locals 1\n");
        generate(fptr, functions->value->statement_list, variables, functions);
        fprintf(fptr, "return\n.end method\n\n");
        functions = functions->prev;
    }
}

void generate_code(char* filename, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){
    FILE* fptr = fopen(filename, "w");
    fprintf(fptr, ".class public Main\n.super java/lang/Object\n\n");
    generate_functions(fptr, variables, functions);
    fclose(fptr);
}