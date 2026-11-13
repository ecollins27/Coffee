#include "generator-misc.c"
void generate_0_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // PROGRAM_0
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
}

void generate_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // PROGRAM
    switch (prod_index){
        case 0:
            generate_0_0(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_1_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // ACTION_LIST_0
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
    generate(fptr, (struct SAST_Node*)(node->children[1]), variables, functions);
}

void generate_1_1(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // ACTION_LIST_1
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
    generate(fptr, (struct SAST_Node*)(node->children[1]), variables, functions);
}

void generate_1(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // ACTION_LIST
    switch (prod_index){
        case 0:
            generate_1_0(fptr, node, variables, functions);
            return;
        case 1:
            generate_1_1(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_2_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // STATEMENT_LIST_0
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
    generate(fptr, (struct SAST_Node*)(node->children[1]), variables, functions);
}

void generate_2(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // STATEMENT_LIST
    switch (prod_index){
        case 0:
            generate_2_0(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_3_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // FUNCTION_DECLARATION_0
    fprintf(fptr, "FUNCTION_");
    fprintf(fptr, "%d", ((struct Token*)(node->children[0]))->data);
    fprintf(fptr, ":");
    fprintf(fptr, "\n");
    generate(fptr, (struct SAST_Node*)(node->children[3]), variables, functions);
    fprintf(fptr, "return");
    fprintf(fptr, "\n");
}

void generate_3_1(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // FUNCTION_DECLARATION_1
    fprintf(fptr, "FUNCTION_");
    fprintf(fptr, "%d", ((struct Token*)(node->children[0]))->data);
    fprintf(fptr, ":");
    fprintf(fptr, "\n");
    generate(fptr, (struct SAST_Node*)(node->children[2]), variables, functions);
    fprintf(fptr, "return");
    fprintf(fptr, "\n");
}

void generate_3(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // FUNCTION_DECLARATION
    switch (prod_index){
        case 0:
            generate_3_0(fptr, node, variables, functions);
            return;
        case 1:
            generate_3_1(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_6_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // STATEMENT_0
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
}

void generate_6_1(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // STATEMENT_1
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
}

void generate_6_2(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // STATEMENT_2
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
}

void generate_6_3(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // STATEMENT_3
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
}

void generate_6_4(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // STATEMENT_4
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
}

void generate_6_5(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // STATEMENT_5
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
    fprintf(fptr, "%s", jvm_type(((struct SAST_Node*)(node->children[0]))->type));
    fprintf(fptr, "return");
    fprintf(fptr, "\n");
}

void generate_6_6(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // STATEMENT_6
    fprintf(fptr, "return");
    fprintf(fptr, "\n");
}

void generate_6(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // STATEMENT
    switch (prod_index){
        case 0:
            generate_6_0(fptr, node, variables, functions);
            return;
        case 1:
            generate_6_1(fptr, node, variables, functions);
            return;
        case 2:
            generate_6_2(fptr, node, variables, functions);
            return;
        case 3:
            generate_6_3(fptr, node, variables, functions);
            return;
        case 4:
            generate_6_4(fptr, node, variables, functions);
            return;
        case 5:
            generate_6_5(fptr, node, variables, functions);
            return;
        case 6:
            generate_6_6(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_7_1(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // VAR_DECLARATION_1
    generate(fptr, (struct SAST_Node*)(node->children[2]), variables, functions);
    fprintf(fptr, "%s", jvm_type(get_variable_by_id(variables, ((struct Token*)(node->children[1]))->data)->type));
    fprintf(fptr, "store ");
    fprintf(fptr, "%d", get_variable_by_id(variables, ((struct Token*)(node->children[1]))->data)->index);
    fprintf(fptr, "\n");
}

void generate_7(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // VAR_DECLARATION
    switch (prod_index){
        case 1:
            generate_7_1(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_8_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // EXPRESSION_0
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
}

void generate_8_1(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // EXPRESSION_1
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
}

void generate_8_2(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // EXPRESSION_2
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
}

void generate_8_3(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // EXPRESSION_3
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
    generate(fptr, (struct SAST_Node*)(node->children[1]), variables, functions);
    fprintf(fptr, "%s", jvm_type(((struct SAST_Node*)(node->children[0]))->type));
    fprintf(fptr, "aload");
    fprintf(fptr, "\n");
}

void generate_8(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // EXPRESSION
    switch (prod_index){
        case 0:
            generate_8_0(fptr, node, variables, functions);
            return;
        case 1:
            generate_8_1(fptr, node, variables, functions);
            return;
        case 2:
            generate_8_2(fptr, node, variables, functions);
            return;
        case 3:
            generate_8_3(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_9_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // BOOL_EXPRESSION_0
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
}

void generate_9_1(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // BOOL_EXPRESSION_1
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
    generate(fptr, (struct SAST_Node*)(node->children[1]), variables, functions);
    fprintf(fptr, "ior");
    fprintf(fptr, "\n");
}

void generate_9(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // BOOL_EXPRESSION
    switch (prod_index){
        case 0:
            generate_9_0(fptr, node, variables, functions);
            return;
        case 1:
            generate_9_1(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_10_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // AND_EXPRESSION_0
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
}

void generate_10_1(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // AND_EXPRESSION_1
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
    generate(fptr, (struct SAST_Node*)(node->children[1]), variables, functions);
    fprintf(fptr, "ior");
    fprintf(fptr, "\n");
}

void generate_10(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // AND_EXPRESSION
    switch (prod_index){
        case 0:
            generate_10_0(fptr, node, variables, functions);
            return;
        case 1:
            generate_10_1(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_11_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // NOT_EXPRESSION_0
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
}

void generate_11_1(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // NOT_EXPRESSION_1
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
    fprintf(fptr, "iconst_1");
    fprintf(fptr, "\n");
    fprintf(fptr, "ixor");
    fprintf(fptr, "\n");
}

void generate_11(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // NOT_EXPRESSION
    switch (prod_index){
        case 0:
            generate_11_0(fptr, node, variables, functions);
            return;
        case 1:
            generate_11_1(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_12_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // BOOL_VALUE_0
    fprintf(fptr, "iconst_0");
    fprintf(fptr, "\n");
}

void generate_12_1(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // BOOL_VALUE_1
    fprintf(fptr, "iconst_1");
    fprintf(fptr, "\n");
}

void generate_12_2(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // BOOL_VALUE_2
    int true_counter = increment_counter();
    int end_counter = increment_counter();
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
    generate(fptr, (struct SAST_Node*)(node->children[2]), variables, functions);
    fprintf(fptr, "if_i");
    fprintf(fptr, "%s", jvm_rel(((struct Token*)(node->children[1]))->token));
    fprintf(fptr, " TRUE_");
    fprintf(fptr, "%d", true_counter);
    fprintf(fptr, "\n");
    fprintf(fptr, "iconst_0");
    fprintf(fptr, "\n");
    fprintf(fptr, "goto END_");
    fprintf(fptr, "%d", end_counter);
    fprintf(fptr, "\n");
    fprintf(fptr, "TRUE_");
    fprintf(fptr, "%d", true_counter);
    fprintf(fptr, ":");
    fprintf(fptr, "\n");
    fprintf(fptr, "iconst_1");
    fprintf(fptr, "\n");
    fprintf(fptr, "END_");
    fprintf(fptr, "%d", end_counter);
    fprintf(fptr, ":");
    fprintf(fptr, "\n");
}

void generate_12(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // BOOL_VALUE
    switch (prod_index){
        case 0:
            generate_12_0(fptr, node, variables, functions);
            return;
        case 1:
            generate_12_1(fptr, node, variables, functions);
            return;
        case 2:
            generate_12_2(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_13_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // ARITHMETIC_EXPRESSION_0
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
}

void generate_13_1(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // ARITHMETIC_EXPRESSION_1
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
    generate(fptr, (struct SAST_Node*)(node->children[2]), variables, functions);
    fprintf(fptr, "%s", jvm_type(((struct SAST_Node*)(node->children[0]))->type));
    fprintf(fptr, "%s", jvm_arith(((struct Token*)(node->children[1]))->token));
    fprintf(fptr, "\n");
}

void generate_13(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // ARITHMETIC_EXPRESSION
    switch (prod_index){
        case 0:
            generate_13_0(fptr, node, variables, functions);
            return;
        case 1:
            generate_13_1(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_14_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // MUL_EXPRESSION_0
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
}

void generate_14_1(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // MUL_EXPRESSION_1
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
    generate(fptr, (struct SAST_Node*)(node->children[1]), variables, functions);
    fprintf(fptr, "%s", jvm_type(((struct SAST_Node*)(node->children[0]))->type));
    fprintf(fptr, "%s", jvm_arith(((struct Token*)(node->children[1]))->token));
    fprintf(fptr, "\n");
}

void generate_14(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // MUL_EXPRESSION
    switch (prod_index){
        case 0:
            generate_14_0(fptr, node, variables, functions);
            return;
        case 1:
            generate_14_1(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_22_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // TYPE_CONVERSION_0
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
    fprintf(fptr, "%s\n", get_convert(((struct SAST_Node*)(node->children[1]))->type, ((struct SAST_Node*)(node->children[2]))->type));
    fprintf(fptr, "\n");
}

void generate_22(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // TYPE_CONVERSION
    switch (prod_index){
        case 0:
            generate_22_0(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_15_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // ARITHMETIC_VALUE_0
    fprintf(fptr, "ldc ");
    fprintf(fptr, "%s", ((struct Token*)(node->children[0]))->token);
    fprintf(fptr, "\n");
}

void generate_15_1(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // ARITHMETIC_VALUE_1
    fprintf(fptr, "ldc ");
    fprintf(fptr, "%s", ((struct Token*)(node->children[0]))->token);
    fprintf(fptr, "\n");
}

void generate_15_2(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // ARITHMETIC_VALUE_2
    fprintf(fptr, "ldc ");
    fprintf(fptr, "%s", ((struct Token*)(node->children[0]))->token);
    fprintf(fptr, "\n");
}

void generate_15_3(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // ARITHMETIC_VALUE_3
    generate(fptr, (struct SAST_Node*)(node->children[1]), variables, functions);
    fprintf(fptr, "newarray ");
    fprintf(fptr, "%s", jvm_raw_type(((struct Token*)(node->children[0]))->token));
    fprintf(fptr, "\n");
}

void generate_15_4(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // ARITHMETIC_VALUE_4
    fprintf(fptr, "%s", jvm_type(get_variable_by_id(variables, ((struct Token*)(node->children[0]))->data)->type));
    fprintf(fptr, "load ");
    fprintf(fptr, "%d", get_variable_by_id(variables, ((struct Token*)(node->children[0]))->data)->index);
    fprintf(fptr, "\n");
}

void generate_15_5(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // ARITHMETIC_VALUE_5
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
}

void generate_15(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // ARITHMETIC_VALUE
    switch (prod_index){
        case 0:
            generate_15_0(fptr, node, variables, functions);
            return;
        case 1:
            generate_15_1(fptr, node, variables, functions);
            return;
        case 2:
            generate_15_2(fptr, node, variables, functions);
            return;
        case 3:
            generate_15_3(fptr, node, variables, functions);
            return;
        case 4:
            generate_15_4(fptr, node, variables, functions);
            return;
        case 5:
            generate_15_5(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_16_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // ASSIGNMENT_0
    generate(fptr, (struct SAST_Node*)(node->children[1]), variables, functions);
    fprintf(fptr, "%s", jvm_type(get_variable_by_id(variables, ((struct Token*)(node->children[0]))->data)->type));
    fprintf(fptr, "store ");
    fprintf(fptr, "%d", get_variable_by_id(variables, ((struct Token*)(node->children[0]))->data)->index);
    fprintf(fptr, "\n");
}

void generate_16_1(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // ASSIGNMENT_1
    fprintf(fptr, "%s", jvm_type(get_variable_by_id(variables, ((struct Token*)(node->children[0]))->data)->type));
    fprintf(fptr, "load ");
    fprintf(fptr, "%d", get_variable_by_id(variables, ((struct Token*)(node->children[0]))->data)->index);
    fprintf(fptr, "\n");
    generate(fptr, (struct SAST_Node*)(node->children[2]), variables, functions);
    fprintf(fptr, "%s", jvm_arith(((struct Token*)(node->children[1]))->token));
    fprintf(fptr, "\n");
    fprintf(fptr, "%s", jvm_type(get_variable_by_id(variables, ((struct Token*)(node->children[0]))->data)->type));
    fprintf(fptr, "store ");
    fprintf(fptr, "%d", get_variable_by_id(variables, ((struct Token*)(node->children[0]))->data)->index);
    fprintf(fptr, "\n");
}

void generate_16_2(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // ASSIGNMENT_2
    fprintf(fptr, "%s", jvm_type(get_variable_by_id(variables, ((struct Token*)(node->children[0]))->data)->type));
    fprintf(fptr, "load ");
    fprintf(fptr, "%d", get_variable_by_id(variables, ((struct Token*)(node->children[0]))->data)->index);
    fprintf(fptr, "\n");
    fprintf(fptr, "%s", jvm_type(get_variable_by_id(variables, ((struct Token*)(node->children[0]))->data)->type));
    fprintf(fptr, "const_1");
    fprintf(fptr, "\n");
    fprintf(fptr, "%s", jvm_arith(((struct Token*)(node->children[1]))->token));
    fprintf(fptr, "\n");
    fprintf(fptr, "%s", jvm_type(get_variable_by_id(variables, ((struct Token*)(node->children[0]))->data)->type));
    fprintf(fptr, "store ");
    fprintf(fptr, "%d", get_variable_by_id(variables, ((struct Token*)(node->children[0]))->data)->index);
    fprintf(fptr, "\n");
}

void generate_16(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // ASSIGNMENT
    switch (prod_index){
        case 0:
            generate_16_0(fptr, node, variables, functions);
            return;
        case 1:
            generate_16_1(fptr, node, variables, functions);
            return;
        case 2:
            generate_16_2(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_17_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // FUNCTION_CALL_0
    generate(fptr, (struct SAST_Node*)(node->children[1]), variables, functions);
    fprintf(fptr, "invokestatic ");
    write_signature(fptr, ((struct Token*)(node->children[0]))->data, functions);
    fprintf(fptr, "\n");
}

void generate_17_1(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // FUNCTION_CALL_1
    fprintf(fptr, "invokestatic ");
    write_signature(fptr, ((struct Token*)(node->children[0]))->data, functions);
    fprintf(fptr, "\n");
}

void generate_17(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // FUNCTION_CALL
    switch (prod_index){
        case 0:
            generate_17_0(fptr, node, variables, functions);
            return;
        case 1:
            generate_17_1(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_18_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // PARAMS_0
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
    generate(fptr, (struct SAST_Node*)(node->children[1]), variables, functions);
}

void generate_18_1(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // PARAMS_1
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
}

void generate_18(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // PARAMS
    switch (prod_index){
        case 0:
            generate_18_0(fptr, node, variables, functions);
            return;
        case 1:
            generate_18_1(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_19_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // IF_STATEMENT_0
    int true_counter = increment_counter();
    int end_counter = increment_counter();
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
    fprintf(fptr, "iconst_0");
    fprintf(fptr, "\n");
    fprintf(fptr, "if_");
    fprintf(fptr, "%s", jvm_type(((struct SAST_Node*)(node->children[0]))->type));
    fprintf(fptr, "cmpgt TRUE_");
    fprintf(fptr, "%d", true_counter);
    fprintf(fptr, "\n");
    generate(fptr, (struct SAST_Node*)(node->children[2]), variables, functions);
    fprintf(fptr, "goto END_");
    fprintf(fptr, "%d", end_counter);
    fprintf(fptr, "\n");
    fprintf(fptr, "TRUE_");
    fprintf(fptr, "%d", true_counter);
    fprintf(fptr, ":");
    fprintf(fptr, "\n");
    generate(fptr, (struct SAST_Node*)(node->children[1]), variables, functions);
    fprintf(fptr, "END_");
    fprintf(fptr, "%d", end_counter);
    fprintf(fptr, ":");
    fprintf(fptr, "\n");
}

void generate_19(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // IF_STATEMENT
    switch (prod_index){
        case 0:
            generate_19_0(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_20_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // ELSE_OPT_0
    generate(fptr, (struct SAST_Node*)(node->children[0]), variables, functions);
}

void generate_20(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // ELSE_OPT
    switch (prod_index){
        case 0:
            generate_20_0(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_21_0(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){ // WHILE_STATEMENT_0
    int block_counter = increment_counter();
    int end_counter = increment_counter();
    fprintf(fptr, "if_");
    fprintf(fptr, "%s", jvm_type(((struct SAST_Node*)(node->children[0]))->type));
    fprintf(fptr, "cmpeq BLOCK_");
    fprintf(fptr, "%d", block_counter);
    fprintf(fptr, "\n");
    fprintf(fptr, "goto END_");
    fprintf(fptr, "%d", end_counter);
    fprintf(fptr, "\n");
    fprintf(fptr, "BLOCK_");
    fprintf(fptr, "%d", block_counter);
    fprintf(fptr, ":");
    fprintf(fptr, "\n");
    generate(fptr, (struct SAST_Node*)(node->children[1]), variables, functions);
    fprintf(fptr, "END_");
    fprintf(fptr, "%d", end_counter);
    fprintf(fptr, ":");
    fprintf(fptr, "\n");
}

void generate_21(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions, int prod_index){ // WHILE_STATEMENT
    switch (prod_index){
        case 0:
            generate_21_0(fptr, node, variables, functions);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate(FILE* fptr, struct SAST_Node* node, struct Variable_Linked_List* variables, struct Function_Linked_List* functions){
    if (node == NULL){
        return;
    }
        switch (node->prod_index[0]){
        case 0:
            generate_0(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 1:
            generate_1(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 2:
            generate_2(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 3:
            generate_3(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 6:
            generate_6(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 7:
            generate_7(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 8:
            generate_8(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 9:
            generate_9(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 10:
            generate_10(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 11:
            generate_11(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 12:
            generate_12(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 13:
            generate_13(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 14:
            generate_14(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 22:
            generate_22(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 15:
            generate_15(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 16:
            generate_16(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 17:
            generate_17(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 18:
            generate_18(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 19:
            generate_19(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 20:
            generate_20(fptr, node, variables, functions, node->prod_index[1]);
            return;
        case 21:
            generate_21(fptr, node, variables, functions, node->prod_index[1]);
            return;
        default:
            printf("Unknown production index %d", node->prod_index[0]);
            exit(1);
    }

}
    
    