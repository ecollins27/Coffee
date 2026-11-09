#include "ast.c"

struct SAST_Node {
    char* name;
    int num_children;
    void** children;
    char* is_token;
    struct SAST_Node* parent;

};

void print_full_simple_tree(struct SAST_Node* node, int depth){
    for (int i = 0; i < depth; i++){
        printf("  ");
    }
    if (node == NULL){
        printf("NULL\n");
        return;
    }
    printf("%s\n", node->name);
    for (int i = 0; i < node->num_children; i++){
        if (node->is_token[i]){
            for (int j = 0; j < depth + 1; j++){
                printf("  ");
            }
            struct Token* token = (struct Token*)(node->children[i]);
            printf("(\"%s\",%s)\n", token->token, type_names[token->type]);
        } else {
            print_full_simple_tree((struct SAST_Node*)(node->children[i]), depth + 1);
        }
    }
}

struct SAST_Node* simplify(struct AST_Node* ast){
    if (ast == NULL || equals(ast->production[0],"`epsilon")){
        return NULL;
    }
    struct SAST_Node* node = (struct SAST_Node*)malloc(sizeof(struct SAST_Node));
    char** production = ast->production;
    int prod_length = 0;
    while (production[prod_length][0] != '\0'){
        prod_length++;
    }
    int num_children = 0;
    for (int i = 0; i < prod_length; i++){
        if (production[i][0] == '`'){
            num_children++;
        }
    }
    node->name = non_terminals[ast->prod_index[0]];
    node->num_children = num_children;
    node->children = malloc(num_children * sizeof(void*));
    node->is_token = (char*)malloc(num_children * sizeof(char));
    int counter = 0;
    for (int i = 0; i < prod_length; i++){
        if (production[i][0] == '`'){
            if (get_token_type_index(&production[i][1]) >= 0){
                node->is_token[counter] = 1;
                node->children[counter] = ast->children[i];
            } else {
                node->is_token[counter] = 0;
                node->children[counter] = simplify(ast->children[i]);
                if (node->children[counter] != NULL){
                    ((struct SAST_Node*)(node->children[counter]))->parent = node;
                }
            }
            counter++;
        }
    }
    return node;
}