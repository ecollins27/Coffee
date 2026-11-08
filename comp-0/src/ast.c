#include "token-parser.c"
#include "cfg.c"

struct AST_Node {
    int prod_index[2];
    char** production;
    void** children;
    struct AST_Node* parent;
};

struct State_Stack {
    int value;
    struct State_Stack* below;
};

struct Node_Stack {
    void* value;
    int is_token;
    struct Node_Stack* below;
};

int get_terminal_index(struct Token* token){
    char* str;
    if (equals(type_names[token->type], "constant")){
        str = token->token;
    } else {
        str = type_names[token->type];
    }
    for (int i = 0; i < NUM_TERMINALS; i++){
        if (equals(str, terminals[i])){
            return i;
        }
    }
    return -1;
}

struct State_Stack* add_to_state_stack(struct State_Stack* stack, int value){
    struct State_Stack* top = (struct State_Stack*)malloc(sizeof(struct State_Stack));
    top->value = value;
    top->below = stack;
    return top;
}

struct Node_Stack* add_to_value_stack(struct Node_Stack* stack, void* value, int is_token){
    struct Node_Stack* top = (struct Node_Stack*)malloc(sizeof(struct Node_Stack));
    top->value = value;
    top->is_token = is_token;
    top->below = stack;
    return top;
}

int get_token_type_index(char* type){
    for (int i = 0; i < NUM_TOKEN_TYPES; i++){
        if (equals(type_names[i], type)){
            return i;
        }
    }
    return -1;
}

void print_full_tree(struct AST_Node* node, int depth){
    for (int i = 0; i < depth; i++){
        printf("  ");
    }
    printf("%s %p\n", non_terminals[node->prod_index[0]], node);
    for (int i = 0; node->production[i][0] != '\0'; i++){
        if (equals(node->production[i],"`epsilon")){
            for (int j = 0; j < depth + 1; j++){
                printf("  ");
            }
            printf("epsilon\n");
        } else if (node->production[i][0] == '`' && get_token_type_index(&node->production[i][1]) < 0){
            print_full_tree((struct AST_Node*)(node->children[i]), depth + 1);
        } else {
            for (int j = 0; j < depth + 1; j++){
                printf("  ");
            }
            struct Token* token = (struct Token*)(node->children[i]);
            printf("(\"%s\",%s) %p\n", token->token, type_names[token->type], token);
        }
    }
}

int matches_node(char* prod_element, struct Node_Stack* top){
    if (prod_element[0] == '`' && get_token_type_index(&prod_element[1]) < 0){
        if (top->is_token){
            printf("Expected AST_Node.  Found token\n");
            exit(1);
        } else if (!equals(non_terminals[((struct AST_Node*)(top->value))->prod_index[0]], &prod_element[1])){
            printf("Expected non-terminal of type %s.  Found type %s\n", non_terminals[((struct AST_Node*)(top->value))->prod_index[0]], &prod_element[1]);
            exit(1);
        }
        return 1;
    } else {
        if (!top->is_token){
            printf("Expected token.  Found AST_Node\n");
        }
        struct Token* value = (struct Token*)(top->value);
        if (prod_element[0] == '`' && !equals(&prod_element[1], type_names[value->type])){
            printf("Expected token of type %s.  Found (\"%s\",%s)\n", &prod_element[1], value->token, type_names[value->type]);
            exit(1);
        } else if (prod_element[0] != '`' && !equals(prod_element, value->token)){
            printf("Expected token (\"%s\",constant).  Found (\"%s\",%s)\n", prod_element, value->token, type_names[value->type]);
        }
        return 2;
    }
}

struct AST_Node* reduce(struct Node_Stack** value_stack, struct State_Stack** state_stack, int non_terminal_index, int prod_index){
    int prod_length = 0;
    while (full_cfg[non_terminal_index][prod_index][prod_length][0] != '\0'){prod_length++;}
    struct AST_Node* node = (struct AST_Node*)malloc(sizeof(struct AST_Node));
    node->prod_index[0] = non_terminal_index;
    node->prod_index[1] = prod_index;
    node->production = full_cfg[non_terminal_index][prod_index];
    node->children = malloc(prod_length * sizeof(void*));
    if (prod_length == 1 && equals(node->production[0],"`epsilon")){
        return node;
    }
    for (int i = prod_length - 1; i >= 0; i--){
        if (*value_stack == NULL || *state_stack == NULL){
            printf("Premature EOF\n");
            exit(1);
        }
        struct Node_Stack* top = *value_stack;
        *value_stack = (*value_stack)->below;
        struct State_Stack* state_top = *state_stack;
        *state_stack = (*state_stack)->below;
        int match_code = matches_node(node->production[i], top);
        if (match_code){
            node->children[i] = top->value;
            if (match_code == 1){
                ((struct AST_Node*)(node->children[i]))->parent = node;
            }
        }
        free(top);
        free(state_top);
    }
    return node;
}

struct AST_Node* parse_ast(char* str){
    struct Token* next_token = get_next_token(&str);
    int next_token_index = get_terminal_index(next_token);
    struct State_Stack* state_stack = add_to_state_stack(NULL, 0);
    struct Node_Stack* value_stack = NULL;
    while (1){
        if (next_token_index < 0){
            printf("Unknown token (\"%s\",%s)\n", next_token->token, type_names[next_token->type]);
            exit(1);
        } else if (state_stack == NULL){
            printf("Premature EOF\n");
            exit(1);
        }
        int* action = action_table[state_stack->value][next_token_index];
        // printf("Next Token: (\"%s\", %s)\n", next_token->token, type_names[next_token->type]);
        // printf("Next Action: %d %d %d\n", action[0], action[1], action[2]);
        // printf("Current State: %d\n\n", state_stack->value);
        if (action[0] == ACCEPT){
            if (value_stack == NULL || value_stack->is_token){
                printf("Cannot accept on current value stack\n");
                exit(1);
            }
            return (struct AST_Node*)value_stack->value;
        } else if (action[0] == SHIFT){
            value_stack = add_to_value_stack(value_stack, next_token, 1);
            next_token = get_next_token(&str);
            next_token_index = get_terminal_index(next_token);
            state_stack = add_to_state_stack(state_stack, action[1]);
        } else if (action[0] == REDUCE){
            struct AST_Node* node = reduce(&value_stack, &state_stack, action[1], action[2]);
            value_stack = add_to_value_stack(value_stack, node, 0);
            if (state_stack == NULL){
                printf("Premature EOF\n");
                exit(1);
            }
            state_stack = add_to_state_stack(state_stack, goto_table[state_stack->value][node->prod_index[0]]);
        } else {
            printf("Unexpected token (\"%s\",%s)\n", next_token->token, type_names[next_token->type]);
            exit(1);
        }
    }
    return NULL;
}