#include "sast.c"


struct Variable {
    char* name;
    int id;
    int scope;
    int active;
};

struct Variable_Linked_List {
    struct Variable* value;
    struct Variable_Linked_List* next;
    struct Variable_Linked_List* prev;
};

struct Function {
    char* name;
    int num_params;
    struct Variable_Linked_List* params;
    int id;
    int scope;
    int active;
};

struct Function_Linked_List {
    struct Function* value;
    struct Function_Linked_List* next;
    struct Function_Linked_List* prev;
};

int contains_variable(struct Variable_Linked_List* variables, char* name, int scope){
    if (variables != NULL){
        while (variables != NULL){
            if (equals(variables->value->name, name) && variables->value->scope <= scope && variables->value->active){
                return 1;
            }
            variables = variables->prev;
        }
    }
    return 0;
}

int contains_function(struct Function_Linked_List* functions, char* name, int scope){
    if (functions != NULL){
        while (functions != NULL){
            if (equals(functions->value->name, name) && functions->value->scope <= scope && functions->value->active){
                return 1;
            }
            functions = functions->prev;
        }
    }
    return 0;
}

void add_variable(struct Variable_Linked_List** variables,  char* name, int scope){
    struct Variable* variable = (struct Variable*)malloc(sizeof(struct Variable));
    variable->name = name;
    if (*variables == NULL){
        variable->id = 0;
    } else {
        variable->id = (*variables)->value->id + 1;
    }
    variable->scope = scope;
    variable->active = 1;
    struct Variable_Linked_List* linked_list = (struct Variable_Linked_List*)malloc(sizeof(struct Variable_Linked_List));
    linked_list->value = variable;
    linked_list->prev = *variables;
    if (*variables != NULL){
        (*variables)->next = linked_list;
    }
    *variables = linked_list;
}

void add_function(struct Function_Linked_List** functions, char* name, int scope){
    struct Function* function = (struct Function*)malloc(sizeof(struct Function));
    function->name = name;
    if (*functions == NULL){
        function->id = 0;
    } else {
        function->id = (*functions)->value->id + 1;
    }
    function->scope = scope;
    function->active = 1;
    struct Function_Linked_List* linked_list = (struct Function_Linked_List*)malloc(sizeof(struct Function_Linked_List));
    linked_list->value = function;
    linked_list->prev = *functions;
    if (*functions != NULL){
        (*functions)->next = linked_list;
    }
    *functions = linked_list;
}

void deactivate_variables(struct Variable_Linked_List* variables, int scope){
    if (variables != NULL){
        while (variables != NULL){
            if (variables->value->scope > scope){
                variables->value->active = 0;
            }
            variables = variables->prev;
        }
    }
}

void deactivate_functions(struct Function_Linked_List* functions, int scope){
    if (functions != NULL){
        while (functions != NULL){
            if (functions->value->scope > scope){
                functions->value->active = 0;
            }
            functions = functions->prev;
        }
    }
}

void validate_ast_scope(struct SAST_Node* node, int scope, struct Variable_Linked_List** variables, struct Function_Linked_List** functions){
    if (node == NULL){
        return;
    }
    for (int i = 0; i < node->num_children; i++){
        if (node->is_token[i] || node->children[i] == NULL){
            continue;
        }
        struct SAST_Node* child = node->children[i];
        if (equals(child->name, "var_declaration")){
            char* name = ((struct Token*)(child->children[1]))->token;
            if (contains_variable(*variables, name, scope)){
                printf("Variable \"%s\" already exists in current scope\n", name);
                exit(0);
            }
            validate_ast_scope(child->children[2], scope, variables, functions);
            add_variable(variables, name, scope);
        } else if (equals(child->name, "function_declaration")){
            char* name = ((struct Token*)(child->children[1]))->token;
            if (contains_function(*functions, name, scope)){
                printf("Function \"%s\" already exists in the current scope\n", name);
                exit(0);
            }
            validate_ast_scope(child->children[2], scope + 1, variables, functions);
            add_function(functions, name, scope);
            validate_ast_scope(child->children[3], scope + 1, variables, functions);
            deactivate_variables(*variables, scope);
            deactivate_functions(*functions, scope);
        } else if (equals(child->name, "if_statement")){
            validate_ast_scope(child->children[0], scope, variables, functions);
            validate_ast_scope(child->children[1], scope + 1, variables, functions);
            deactivate_variables(*variables, scope);
            deactivate_functions(*functions, scope);
            validate_ast_scope(child->children[2], scope, variables, functions);
        } else if (equals(child->name, "else_opt")){
            validate_ast_scope(child->children[0], scope + 1, variables, functions);
            deactivate_variables(*variables, scope);
            deactivate_functions(*functions, scope);
        } else if (equals(child->name, "while_statement")){
            validate_ast_scope(child->children[0], scope, variables, functions);
            validate_ast_scope(child->children[1], scope + 1, variables, functions);
            deactivate_variables(*variables, scope);
            deactivate_functions(*functions, scope);
        } else if (equals(child->name, "ref_value") && child->num_children == 1){
            char* name = ((struct Token*)(child->children[0]))->token;
            if (!contains_variable(*variables, name, scope)){
                printf("Variable \"%s\" does not exist in current scope\n", name);
                exit(1);
            }
        } else if (equals(child->name, "function_call")){
            char* name = ((struct Token*)(child->children[0]))->token;
            if (!contains_function(*functions, name, scope)){
                printf("Function \"%s\" does not exist in current scope\n", name);
                exit(1);
            }
            validate_ast_scope(child->children[1], scope, variables, functions);
        } else {
            validate_ast_scope(child, scope, variables, functions);
        }
    }
}

void validate_ast(struct SAST_Node* node){
    struct Variable_Linked_List* variables = NULL;
    struct Function_Linked_List* functions = NULL;
    validate_ast_scope(node, 0, &variables, &functions);
}