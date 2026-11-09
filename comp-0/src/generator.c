#include generator-misc.c
void generate_0_0(FILE* fptr, struct SAST_Node* node){ // PROGRAM_0
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
}

void generate_0(FILE* fptr, struct SAST_Node* node, int prod_index){ // PROGRAM
    switch (prod_index){
        case 0:
            generate_0_0(fptr, node);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_1_0(FILE* fptr, struct SAST_Node* node){ // ACTION_LIST_0
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[1])));
    fprintf(fptr, "\n");
}

void generate_1_1(FILE* fptr, struct SAST_Node* node){ // ACTION_LIST_1
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[1])));
    fprintf(fptr, "\n");
}

void generate_1_2(FILE* fptr, struct SAST_Node* node){ // ACTION_LIST_2
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[1])));
    fprintf(fptr, "\n");
}

void generate_1(FILE* fptr, struct SAST_Node* node, int prod_index){ // ACTION_LIST
    switch (prod_index){
        case 0:
            generate_1_0(fptr, node);
            return;
        case 1:
            generate_1_1(fptr, node);
            return;
        case 2:
            generate_1_2(fptr, node);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_2_0(FILE* fptr, struct SAST_Node* node){ // FUNCTION_DECLARATION_0
    fprintf(fptr, "FUNCTION_");
    fprintf(fptr, "%d", ((struct Function*)(((struct Token*)(node->children[0]))->data))->id));
    fprintf(fptr, ":");
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[3])));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    fprintf(fptr, "%s", jvm_type(((struct Token*)(node->children[0]))->token));
    fprintf(fptr, "\n");
}

void generate_2(FILE* fptr, struct SAST_Node* node, int prod_index){ // FUNCTION_DECLARATION
    switch (prod_index){
        case 0:
            generate_2_0(fptr, node);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_4_0(FILE* fptr, struct SAST_Node* node){ // STATEMENT_0
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
}

void generate_4_1(FILE* fptr, struct SAST_Node* node){ // STATEMENT_1
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
}

void generate_4_2(FILE* fptr, struct SAST_Node* node){ // STATEMENT_2
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
}

void generate_4_3(FILE* fptr, struct SAST_Node* node){ // STATEMENT_3
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
}

void generate_4_4(FILE* fptr, struct SAST_Node* node){ // STATEMENT_4
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
}

void generate_4(FILE* fptr, struct SAST_Node* node, int prod_index){ // STATEMENT
    switch (prod_index){
        case 0:
            generate_4_0(fptr, node);
            return;
        case 1:
            generate_4_1(fptr, node);
            return;
        case 2:
            generate_4_2(fptr, node);
            return;
        case 3:
            generate_4_3(fptr, node);
            return;
        case 4:
            generate_4_4(fptr, node);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_5_1(FILE* fptr, struct SAST_Node* node){ // VAR_DECLARATION_1
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[2])));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    fprintf(fptr, "%s", jvm_type(((struct SAST_Node*)(node->children[1]))->data_type));
    fprintf(fptr, "store ");
    fprintf(fptr, "%d", ((struct Variable*)(((struct Token*)(node->children[0]))->data))->index));
    fprintf(fptr, "\n");
}

void generate_5(FILE* fptr, struct SAST_Node* node, int prod_index){ // VAR_DECLARATION
    switch (prod_index){
        case 1:
            generate_5_1(fptr, node);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_6_0(FILE* fptr, struct SAST_Node* node){ // EXPRESSION_0
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
}

void generate_6_1(FILE* fptr, struct SAST_Node* node){ // EXPRESSION_1
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
}

void generate_6_2(FILE* fptr, struct SAST_Node* node){ // EXPRESSION_2
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
}

void generate_6(FILE* fptr, struct SAST_Node* node, int prod_index){ // EXPRESSION
    switch (prod_index){
        case 0:
            generate_6_0(fptr, node);
            return;
        case 1:
            generate_6_1(fptr, node);
            return;
        case 2:
            generate_6_2(fptr, node);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_7_0(FILE* fptr, struct SAST_Node* node){ // BOOL_EXPRESSION_0
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
}

void generate_7_1(FILE* fptr, struct SAST_Node* node){ // BOOL_EXPRESSION_1
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[1])));
    fprintf(fptr, "\n");
    fprintf(fptr, "ior");
    fprintf(fptr, "\n");
}

void generate_7(FILE* fptr, struct SAST_Node* node, int prod_index){ // BOOL_EXPRESSION
    switch (prod_index){
        case 0:
            generate_7_0(fptr, node);
            return;
        case 1:
            generate_7_1(fptr, node);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_8_0(FILE* fptr, struct SAST_Node* node){ // AND_EXPRESSION_0
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
}

void generate_8_1(FILE* fptr, struct SAST_Node* node){ // AND_EXPRESSION_1
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[1])));
    fprintf(fptr, "\n");
    fprintf(fptr, "ior");
    fprintf(fptr, "\n");
}

void generate_8(FILE* fptr, struct SAST_Node* node, int prod_index){ // AND_EXPRESSION
    switch (prod_index){
        case 0:
            generate_8_0(fptr, node);
            return;
        case 1:
            generate_8_1(fptr, node);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_9_0(FILE* fptr, struct SAST_Node* node){ // NOT_EXPRESSION_0
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
}

void generate_9_1(FILE* fptr, struct SAST_Node* node){ // NOT_EXPRESSION_1
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
    fprintf(fptr, "iconst_1");
    fprintf(fptr, "\n");
    fprintf(fptr, "ixor");
    fprintf(fptr, "\n");
}

void generate_9(FILE* fptr, struct SAST_Node* node, int prod_index){ // NOT_EXPRESSION
    switch (prod_index){
        case 0:
            generate_9_0(fptr, node);
            return;
        case 1:
            generate_9_1(fptr, node);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_10_0(FILE* fptr, struct SAST_Node* node){ // BOOL_VALUE_0
    fprintf(fptr, "iconst_0");
    fprintf(fptr, "\n");
}

void generate_10_1(FILE* fptr, struct SAST_Node* node){ // BOOL_VALUE_1
    fprintf(fptr, "iconst_1");
    fprintf(fptr, "\n");
}

void generate_10_2(FILE* fptr, struct SAST_Node* node){ // BOOL_VALUE_2
    fprintf(fptr, "");
    int true_counter = increment_counter();
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    int end_counter = increment_counter();
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[2])));
    fprintf(fptr, "\n");
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

void generate_10(FILE* fptr, struct SAST_Node* node, int prod_index){ // BOOL_VALUE
    switch (prod_index){
        case 0:
            generate_10_0(fptr, node);
            return;
        case 1:
            generate_10_1(fptr, node);
            return;
        case 2:
            generate_10_2(fptr, node);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_11_0(FILE* fptr, struct SAST_Node* node){ // ARITHMETIC_EXPRESSION_0
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
}

void generate_11_1(FILE* fptr, struct SAST_Node* node){ // ARITHMETIC_EXPRESSION_1
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[2])));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    fprintf(fptr, "%s", jvm_type(((struct SAST_Node*)(node->children[0]))->data_type));
    fprintf(fptr, "");
    fprintf(fptr, "%s", jvm_arith(((struct Token*)(node->children[1]))->token));
    fprintf(fptr, "\n");
}

void generate_11(FILE* fptr, struct SAST_Node* node, int prod_index){ // ARITHMETIC_EXPRESSION
    switch (prod_index){
        case 0:
            generate_11_0(fptr, node);
            return;
        case 1:
            generate_11_1(fptr, node);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_12_0(FILE* fptr, struct SAST_Node* node){ // MUL_EXPRESSION_0
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
}

void generate_12_1(FILE* fptr, struct SAST_Node* node){ // MUL_EXPRESSION_1
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[1])));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    fprintf(fptr, "%s", jvm_type(((struct SAST_Node*)(node->children[0]))->data_type));
    fprintf(fptr, "");
    fprintf(fptr, "%s", jvm_arith(((struct Token*)(node->children[1]))->token));
    fprintf(fptr, "\n");
}

void generate_12(FILE* fptr, struct SAST_Node* node, int prod_index){ // MUL_EXPRESSION
    switch (prod_index){
        case 0:
            generate_12_0(fptr, node);
            return;
        case 1:
            generate_12_1(fptr, node);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_20_0(FILE* fptr, struct SAST_Node* node){ // TYPE_CONVERSION_0
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    fprintf(fptr, "%s\n", get_convert(((struct SAST_Node*)(node->children[1]))->data_type), ((struct SAST_Node*)(node->children[2]))->data_type)));
    fprintf(fptr, "\n");
}

void generate_20(FILE* fptr, struct SAST_Node* node, int prod_index){ // TYPE_CONVERSION
    switch (prod_index){
        case 0:
            generate_20_0(fptr, node);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_13_0(FILE* fptr, struct SAST_Node* node){ // ARITHMETIC_VALUE_0
    fprintf(fptr, "ldc2_w ");
    fprintf(fptr, "%s", ((struct Token*)(node->children[0]))->token);
    fprintf(fptr, "\n");
}

void generate_13_1(FILE* fptr, struct SAST_Node* node){ // ARITHMETIC_VALUE_1
    fprintf(fptr, "ldc2_w ");
    fprintf(fptr, "%s", ((struct Token*)(node->children[0]))->token);
    fprintf(fptr, "\n");
}

void generate_13_2(FILE* fptr, struct SAST_Node* node){ // ARITHMETIC_VALUE_2
    fprintf(fptr, "ldc ");
    fprintf(fptr, "%s", ((struct Token*)(node->children[0]))->token);
    fprintf(fptr, "\n");
}

void generate_13_3(FILE* fptr, struct SAST_Node* node){ // ARITHMETIC_VALUE_3
    fprintf(fptr, "");
    fprintf(fptr, "%s", jvm_type(((struct SAST_Node*)(node->children[0]))->data_type));
    fprintf(fptr, "load ");
    fprintf(fptr, "%d", ((struct Variable*)(((struct Token*)(node->children[0]))->data))->index));
    fprintf(fptr, "\n");
}

void generate_13_4(FILE* fptr, struct SAST_Node* node){ // ARITHMETIC_VALUE_4
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
}

void generate_13(FILE* fptr, struct SAST_Node* node, int prod_index){ // ARITHMETIC_VALUE
    switch (prod_index){
        case 0:
            generate_13_0(fptr, node);
            return;
        case 1:
            generate_13_1(fptr, node);
            return;
        case 2:
            generate_13_2(fptr, node);
            return;
        case 3:
            generate_13_3(fptr, node);
            return;
        case 4:
            generate_13_4(fptr, node);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_14_0(FILE* fptr, struct SAST_Node* node){ // ASSIGNMENT_0
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[1])));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    fprintf(fptr, "%s", jvm_type(((struct SAST_Node*)(node->children[0]))->data_type));
    fprintf(fptr, "store ");
    fprintf(fptr, "%d", ((struct Variable*)(((struct Token*)(node->children[0]))->data))->index));
    fprintf(fptr, "\n");
}

void generate_14_1(FILE* fptr, struct SAST_Node* node){ // ASSIGNMENT_1
    fprintf(fptr, "");
    fprintf(fptr, "%s", jvm_type(((struct SAST_Node*)(node->children[0]))->data_type));
    fprintf(fptr, "load ");
    fprintf(fptr, "%d", ((struct Variable*)(((struct Token*)(node->children[0]))->data))->index));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[2])));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    fprintf(fptr, "%s", jvm_arith(((struct Token*)(node->children[1]))->token));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    fprintf(fptr, "%s", jvm_type(((struct SAST_Node*)(node->children[0]))->data_type));
    fprintf(fptr, "store ");
    fprintf(fptr, "%d", ((struct Variable*)(((struct Token*)(node->children[0]))->data))->index));
    fprintf(fptr, "\n");
}

void generate_14_2(FILE* fptr, struct SAST_Node* node){ // ASSIGNMENT_2
    fprintf(fptr, "");
    fprintf(fptr, "%s", jvm_type(((struct SAST_Node*)(node->children[0]))->data_type));
    fprintf(fptr, "load ");
    fprintf(fptr, "%d", ((struct Variable*)(((struct Token*)(node->children[0]))->data))->index));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    fprintf(fptr, "%s", jvm_type(((struct SAST_Node*)(node->children[0]))->data_type));
    fprintf(fptr, "const_1");
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    fprintf(fptr, "%s", jvm_arith(((struct Token*)(node->children[1]))->token));
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    fprintf(fptr, "%s", jvm_type(((struct SAST_Node*)(node->children[0]))->data_type));
    fprintf(fptr, "store ");
    fprintf(fptr, "%d", ((struct Variable*)(((struct Token*)(node->children[0]))->data))->index));
    fprintf(fptr, "\n");
}

void generate_14(FILE* fptr, struct SAST_Node* node, int prod_index){ // ASSIGNMENT
    switch (prod_index){
        case 0:
            generate_14_0(fptr, node);
            return;
        case 1:
            generate_14_1(fptr, node);
            return;
        case 2:
            generate_14_2(fptr, node);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_17_0(FILE* fptr, struct SAST_Node* node){ // IF_STATEMENT_0
    fprintf(fptr, "");
    int true_counter = increment_counter();
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    int end_counter = increment_counter();
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
    fprintf(fptr, "iconst_1");
    fprintf(fptr, "\n");
    fprintf(fptr, "if_");
    fprintf(fptr, "%s", jvm_type(((struct SAST_Node*)(node->children[0]))->data_type));
    fprintf(fptr, "cmpeq TRUE_");
    fprintf(fptr, "%d", true_counter);
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[2])));
    fprintf(fptr, "\n");
    fprintf(fptr, "goto END_");
    fprintf(fptr, "%d", end_counter);
    fprintf(fptr, "\n");
    fprintf(fptr, "TRUE_");
    fprintf(fptr, "%d", true_counter);
    fprintf(fptr, ":");
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[1])));
    fprintf(fptr, "\n");
    fprintf(fptr, "END_");
    fprintf(fptr, "%d", end_counter);
    fprintf(fptr, ":");
    fprintf(fptr, "\n");
}

void generate_17(FILE* fptr, struct SAST_Node* node, int prod_index){ // IF_STATEMENT
    switch (prod_index){
        case 0:
            generate_17_0(fptr, node);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_18_0(FILE* fptr, struct SAST_Node* node){ // ELSE_OPT_0
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[0])));
    fprintf(fptr, "\n");
}

void generate_18(FILE* fptr, struct SAST_Node* node, int prod_index){ // ELSE_OPT
    switch (prod_index){
        case 0:
            generate_18_0(fptr, node);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

void generate_19_0(FILE* fptr, struct SAST_Node* node){ // WHILE_STATEMENT_0
    fprintf(fptr, "");
    int block_counter = increment_counter();
    fprintf(fptr, "\n");
    fprintf(fptr, "");
    int end_counter = increment_counter();
    fprintf(fptr, "\n");
    fprintf(fptr, "if_");
    fprintf(fptr, "%s", jvm_type(((struct SAST_Node*)(node->children[0]))->data_type));
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
    fprintf(fptr, "");
    generate(fptr, ((struct SAST_Node*)(node->children[1])));
    fprintf(fptr, "\n");
    fprintf(fptr, "END_");
    fprintf(fptr, "%d", end_counter}:);
    fprintf(fptr, "ND_");
    fprintf(fptr, "%d", end_counter}:);
    fprintf(fptr, "D_");
    fprintf(fptr, "%d", end_counter}:);
    fprintf(fptr, "_");
    fprintf(fptr, "%d", end_counter}:);
    fprintf(fptr, "");
    fprintf(fptr, "%d", end_counter}:);
    fprintf(fptr, "{var end_counter}:}");
    fprintf(fptr, "\n");
}

void generate_19(FILE* fptr, struct SAST_Node* node, int prod_index){ // WHILE_STATEMENT
    switch (prod_index){
        case 0:
            generate_19_0(fptr, node);
            return;
        default:
            printf("Unknown production index");
            exit(1);
    }
}

