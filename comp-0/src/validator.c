#include "sast.c"

struct Type {
    char* type;
    struct Type* sub_type;
};

struct Variable {
    struct Type* type;
    char* name;
    int id;
    int index;
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
    struct Variable_Linked_List* params;
    struct SAST_Node* statement_list;
    struct Type* return_type;
    int id;
    int scope;
    int active;
    int num_calls;
    int predefined;
};

struct Function_Linked_List {
    struct Function* value;
    struct Function_Linked_List* next;
    struct Function_Linked_List* prev;
};

int get_compatibility(struct Type* type1, struct Type* type2){
    // 0 = incompatible
    // 1 = compatible no conversion
    // 2 = compatible conversion required
    if (type1 == NULL || type2 == NULL){
        return 0;
    }
    if (equals(type1->type, "array") || equals(type2->type, "array")){
        if (!equals(type1->type,type2->type) || get_compatibility(type1->sub_type, type2->sub_type) != 1){
            return 0;
        }
        return 1;
    }
    char* types[6] = {"int", "long", "float", "double", "char", "void"};
    int lookup[6][6] = {
//                     int long float double char void
        /* int    */ { 1,  0,   0,    0,     1,   0 },
        /* long   */ { 2,  1,   0,    0,     2,   0 },
        /* float  */ { 2,  0,   1,    0,     2,   0 },
        /* double */ { 2,  2,   2,    1,     2,   0 },
        /* char   */ { 1,  0,   0,    0,     1,   0 },
        /* void   */ { 0,  0,   0,    0,     0,   0 },
    };
    int index1 = 0;
    while (!equals(types[index1], type1->type)){index1++;}
    int index2 = 0;
    while (!equals(types[index2], type2->type)){index2++;}
    return lookup[index1][index2];
}

void add_conversion(struct SAST_Node* node, int child, char* from, char* to){
    if (equals(from, to)){
        printf("Cannot convert to identical types \"%s\" and \"%s\"\n", from, to);
        exit(1);
    }
    struct SAST_Node* conversion = (struct SAST_Node*)malloc(sizeof(struct SAST_Node));
    conversion->children = malloc(sizeof(struct SAST_Node*));
    conversion->children[0] = node->children[child];
    conversion->is_token = (char*)malloc(sizeof(char));
    conversion->is_token[0] = node->is_token[child];
    conversion->num_children = 1;
    conversion->name = "type_conversion";
    conversion->prod_index[0] = -1;
    conversion->prod_index[1] = 0;
    struct Type* type = (struct Type*)malloc(sizeof(struct Type));
    type->sub_type = NULL;
    type->type = to;
    conversion->type = type;
    conversion->parent = node;
    if (!node->is_token[child]){
        ((struct SAST_Node*)(node->children[child]))->parent = conversion;
    }
    node->is_token[child] = 0;
    node->children[child] = conversion;
}

void print_type(struct Type* type){
    if (type == NULL){
        printf("null");
        return;
    }
    if (equals(type->type, "array")){
        print_type(type->sub_type);
        printf("[]");
    } else if (equals(type->type, "pointer")){
        print_type(type->sub_type);
        printf("*");
    } else {
        printf("%s", type->type);
    }
}

struct Type* parse_type(struct SAST_Node* node){
    if (!equals(node->name, "type")){
        printf("Return type must be production \"type\"\n");
        exit(1);
    }
    struct Type* type = (struct Type*)malloc(sizeof(struct Type));
    if (node->is_token[0]){
        type->type = ((struct Token*)(node->children[0]))->token;
        type->sub_type = NULL;
    } else {
        if (node->prod_index[1] == 1){
            type->type = "pointer";
        } else {
            type->type = "array";
        }
        type->sub_type = parse_type(node->children[0]);
    }
    return type;
}

struct Variable* get_variable_by_id(struct Variable_Linked_List* variables, int id){
    while (variables != NULL){
        if (variables->value->id == id){
            return variables->value;
        }
        variables = variables->prev;
    }
    return NULL;
}

struct Function* get_function_by_id(struct Function_Linked_List* functions, int id){
    while (functions != NULL){
        if (functions->value->id == id){
            return functions->value;
        }
        functions = functions->prev;
    }
    return NULL;
}

struct Type* get_variable_type(struct Variable_Linked_List* variables, char* name, int scope){
    if (variables != NULL){
        while (variables != NULL){
            if (equals(variables->value->name, name) && variables->value->scope <= scope && variables->value->active){
                return variables->value->type;
            }
            variables = variables->prev;
        }
    }
    return NULL;
}

struct Variable* get_variable(struct Variable_Linked_List* variables, char* name, int scope){
    if (variables != NULL){
        while (variables != NULL){
            if (equals(variables->value->name, name) && variables->value->scope <= scope && variables->value->active){
                return variables->value;
            }
            variables = variables->prev;
        }
    }
    return NULL;
}

struct Type* get_function_return_type(struct Function_Linked_List* functions, char* name, int scope){
    if (functions != NULL){
        while (functions != NULL){
            if (equals(functions->value->name, name) && functions->value->scope <= scope && functions->value->active){
                return functions->value->return_type;
            }
            functions = functions->prev;
        }
    }
    return NULL;
}

struct Variable_Linked_List* get_function_params(struct Function_Linked_List* functions, char* name, int scope){
    if (functions != NULL){
        while (functions != NULL){
            if (equals(functions->value->name, name) && functions->value->scope <= scope && functions->value->active){
                return functions->value->params;
            }
            functions = functions->prev;
        }
    }
    return NULL;
}

void validate_ast_scope(struct SAST_Node* node, int scope, struct Variable_Linked_List** variables, struct Function_Linked_List** functions);

void validate_function_params(struct Variable_Linked_List* params, struct SAST_Node* node, int scope, struct Variable_Linked_List** variables, struct Function_Linked_List** functions){
    if (params == NULL && node != NULL){
        printf("Function takes no parameters.  Too many parameters found\n");
        exit(1);
    }
    int num_params = 1;
    while (params->prev != NULL){
        num_params++;
        params = params->prev;
    }
    while (params != NULL){
        if (node == NULL){
            printf("Function takes %d parameters.  Insufficient parameters found\n", num_params);
            exit(1);
        }
        validate_ast_scope(node->children[0], scope, variables, functions);
        struct Type* param_type = params->value->type;
        struct Type* node_type = ((struct SAST_Node*)(node->children[0]))->type;
        int compat = get_compatibility(param_type, node_type);
        if (compat == 0){
            printf("Cannot convert type \"");
            print_type(param_type);
            printf("\" to type \"");
            print_type(node_type);
            printf("\"\n");
            exit(1);
        } else if (compat == 2){
            add_conversion(node, 1, node_type->type, param_type->type);
            node = node->children[1];
        }
        if (equals(node->name, "type_conversion")){
            node = node->children[0];
        } else if (node->num_children >= 2){
            node->children[1];
        } else {
            node = NULL;
        }
        params = params->next;
    }
    if (node != NULL){
        printf("Function takes %d parameters.  Too many parameters found\n", num_params);
        exit(1);
    }
}

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
                functions->value->num_calls++;
                return 1;
            }
            functions = functions->prev;
        }
    }
    return 0;
}

int get_available_index(struct Variable_Linked_List* variables, int scope){
    if (variables == NULL){
        return 0;
    }
    while (variables->prev != NULL){
        variables = variables->prev;
    }
    int index = 0;
    while (variables->next != NULL){
        if (variables->value->scope <= scope && variables->value->active){
            index++;
        }
        variables = variables->next;
    }
    return index;
}

int add_variable(struct Variable_Linked_List** variables,  char* name, int scope, struct Type* type){
    struct Variable* variable = (struct Variable*)malloc(sizeof(struct Variable));
    variable->name = name;
    if (*variables == NULL){
        variable->id = 0;
    } else {
        variable->id = (*variables)->value->id + 1;
    }
    variable->scope = scope;
    variable->active = 1;
    variable->index = get_available_index(*variables, scope);
    variable->type = type;
    struct Variable_Linked_List* linked_list = (struct Variable_Linked_List*)malloc(sizeof(struct Variable_Linked_List));
    linked_list->value = variable;
    linked_list->prev = *variables;
    if (*variables != NULL){
        (*variables)->next = linked_list;
    }
    *variables = linked_list;
    return variable->id;
}

struct Function* add_function(struct Function_Linked_List** functions, char* name, int scope, struct Variable_Linked_List* params, struct Type* return_type){
    struct Function* function = (struct Function*)malloc(sizeof(struct Function));
    function->name = name;
    if (*functions == NULL){
        function->id = 0;
    } else {
        function->id = (*functions)->value->id + 1;
    }
    function->scope = scope;
    function->active = 1;
    function->params = params;
    function->return_type = return_type;
    function->num_calls = 0;
    function->predefined = 0;
    struct Function_Linked_List* linked_list = (struct Function_Linked_List*)malloc(sizeof(struct Function_Linked_List));
    linked_list->value = function;
    linked_list->prev = *functions;
    if (*functions != NULL){
        (*functions)->next = linked_list;
    }
    *functions = linked_list;
    return function;
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

void add_params(struct Variable_Linked_List* variables, struct Variable_Linked_List** params, int scope){
    if (variables == NULL){
        return;
    }
    while (variables->prev != NULL){
        variables = variables->prev;
    }
    while (variables != NULL){
        if (variables->value->scope == scope && variables->value->active){
            struct Variable_Linked_List* linked_list = (struct Variable_Linked_List*)malloc(sizeof(struct Variable_Linked_List));
            linked_list->value = variables->value;
            linked_list->prev = *params;
            if (*params != NULL){
                (*params)->next = linked_list;
            }
            *params = linked_list;
        }
        variables = variables->next;
    }
}

void validate_ast_scope(struct SAST_Node* node, int scope, struct Variable_Linked_List** variables, struct Function_Linked_List** functions){
    if (node == NULL){
        return;
    }
    if (equals(node->name, "var_declaration")){
        char* name = ((struct Token*)(node->children[1]))->token;
        if (contains_variable(*variables, name, scope)){
            printf("Variable \"%s\" already exists in current scope\n", name);
            exit(0);
        }
        validate_ast_scope(node->children[2], scope, variables, functions);
        struct Type* type = parse_type(node->children[0]);
        if (equals(type->type, "void")){
            printf("Cannot declare variable of type \"void\"\n");
            exit(1);
        }
        if (node->prod_index[1] == 1){
            struct Type* assignment_type = ((struct SAST_Node*)(node->children[2]))->type;
            int compat = get_compatibility(type, assignment_type);
            if (compat == 0){
                printf("Cannot convert type \"");
                print_type(type);
                printf("\" to type \"");
                print_type(assignment_type);
                printf("\"\n");
                exit(1);
            } else if (compat == 2){
                add_conversion(node, 2, assignment_type->type, type->type);
            }
        }
        int id = add_variable(variables, name, scope, type);
        ((struct Token*)(node->children[1]))->data = id;
    } else if (equals(node->name, "function_declaration")){
        // print_full_simple_tree(node, 0);
        char* name = ((struct Token*)(node->children[1]))->token;
        if (contains_function(*functions, name, scope)){
            printf("Function \"%s\" already exists in the current scope\n", name);
            exit(0);
        }
        struct Type* return_type = parse_type(node->children[0]);
        if (node->prod_index[1] == 0){
            validate_ast_scope(node->children[2], scope + 1, variables, functions);
        }
        struct Variable_Linked_List* params = NULL;
        add_params(*variables, &params, scope + 1);
        struct Function* func = add_function(functions, name, scope, params, return_type);
        ((struct Token*)(node->children[1]))->data = func->id;
        node->parent->children[0] = NULL;
        if (node->prod_index[1] == 0){
            validate_ast_scope(node->children[3], scope + 1, variables, functions);
            func->statement_list = node->children[3];
        } else {
            validate_ast_scope(node->children[2], scope + 1, variables, functions);
            func->statement_list = node->children[2];
        }
        deactivate_variables(*variables, scope);
    } else if (equals(node->name, "assignment")){
        char* name = ((struct Token*)(node->children[0]))->token;
        if (!contains_variable(*variables, name, scope)){
            printf("Variable \"%s\" does not exists in current scope\n", name);
            exit(0);
        }
        struct Variable* var = get_variable(*variables, name, scope);
        struct Type* var_type = var->type;
        ((struct Token*)(node->children[0]))->data = var->id;
        struct Type* assignment_type;
        if (node->prod_index[1] == 0){
            validate_ast_scope(node->children[1], scope, variables, functions);
            assignment_type = ((struct SAST_Node*)(node->children[1]))->type;
        } else if (node->prod_index[1] == 1){
            validate_ast_scope(node->children[2], scope, variables, functions);
            assignment_type = ((struct SAST_Node*)(node->children[2]))->type;
        } else {
            assignment_type = (struct Type*)malloc(sizeof(struct Type));
            assignment_type->type = "int";
            assignment_type->sub_type = NULL;
        }
        int compat = get_compatibility(var_type, assignment_type);
        if (compat == 0){
            printf("Cannot convert type \"");
            print_type(var_type);
            printf("\" to type \"");
            print_type(assignment_type);
            printf("\"\n");
            exit(1);
        } else if (compat == 2 && node->prod_index[1] < 2){
            add_conversion(node, node->prod_index[1] == 0? 1:2, assignment_type->type, var_type->type);
        }
    } else if (equals(node->name, "if_statement")){
        validate_ast_scope(node->children[0], scope, variables, functions);
        validate_ast_scope(node->children[1], scope + 1, variables, functions);
        deactivate_variables(*variables, scope);
        validate_ast_scope(node->children[2], scope, variables, functions);
    } else if (equals(node->name, "else_opt")){
        validate_ast_scope(node->children[0], scope + 1, variables, functions);
        deactivate_variables(*variables, scope);
    } else if (equals(node->name, "while_statement")){
        validate_ast_scope(node->children[0], scope, variables, functions);
        validate_ast_scope(node->children[1], scope + 1, variables, functions);
        deactivate_variables(*variables, scope);
    } else if (equals(node->name, "arithmetic_value")){
        struct Type* type;
        switch (node->prod_index[1]){
            case 0: // int literal
                type = (struct Type*)malloc(sizeof(struct Type));
                type->type = "int";
                type->sub_type = NULL;
                node->type = type;
                break;
            case 1: // float literal
                struct Type* type = (struct Type*)malloc(sizeof(struct Type));
                type->type = "float";
                type->sub_type = NULL;
                node->type = type;
                break;
            case 2: // string literal
                type = (struct Type*)malloc(sizeof(struct Type));
                type->type = "array";
                struct Type* sub_type = (struct Type*)malloc(sizeof(struct Type));
                sub_type->type = "char";
                sub_type->sub_type = NULL;
                type->sub_type = sub_type;
                node->type = type;
                break;
            case 3: // array literal
                type = parse_type(node->children[0]);
                node->type = type;
                break;
            case 4: // variable
                char* name = ((struct Token*)(node->children[0]))->token;
                if (!contains_variable(*variables, name, scope)){
                    printf("Variable \"%s\" does not exist in current scope\n", name);
                    exit(1);
                }
                struct Variable* var = get_variable(*variables, name, scope);
                node->type = var->type;
                ((struct Token*)(node->children[0]))->data = var->id;
                break;
            case 5: // function_call
                validate_ast_scope(node->children[0], scope, variables, functions);
                node->type = ((struct SAST_Node*)(node->children[0]))->type;
                break;
        }
    } else if (equals(node->name, "bool_expression") || equals(node->name, "and_expression") || equals(node->name, "arithmetic_expression") || equals(node->name, "mul_expression")){
        if (node->prod_index[1] == 0){
            validate_ast_scope(node->children[0], scope, variables, functions);
            node->type = ((struct SAST_Node*)(node->children[0]))->type;
        } else {
            validate_ast_scope(node->children[0], scope, variables, functions);
            validate_ast_scope(node->children[2], scope, variables, functions);
            struct Type* type1 = ((struct SAST_Node*)(node->children[0]))->type;
            struct Type* type2 = ((struct SAST_Node*)(node->children[2]))->type;
            int compat = get_compatibility(type1, type2);
            int reverse_compat = get_compatibility(type2, type1);
            if (compat > reverse_compat && compat != 1){
                add_conversion(node, 2, type2->type, type1->type);
                node->type = type1;
            } else if (reverse_compat >= compat && compat != 1){
                add_conversion(node, 0, type1->type, type2->type);
                node->type = type2;
            } else {
                node->type = type1;
            }
        }
    } else if (equals(node->name, "not_expression")){
        validate_ast_scope(node->children[0], scope, variables, functions);
        node->type = ((struct SAST_Node*)(node->children[0]))->type;
    } else if (equals(node->name, "bool_value")){
        if (node->prod_index[1] == 0 || node->prod_index[1] == 1){
            struct Type* type = (struct Type*)malloc(sizeof(struct Type*));
            type->type = "int";
            type->sub_type = NULL;
            node->type = type;
        } else {
            validate_ast_scope(node->children[0], scope, variables, functions);
            validate_ast_scope(node->children[2], scope, variables, functions);
            struct Type* type1 = ((struct SAST_Node*)(node->children[0]))->type;
            struct Type* type2 = ((struct SAST_Node*)(node->children[2]))->type;
            int compat = get_compatibility(type1, type2);
            int reverse_compat = get_compatibility(type2, type1);
            if (compat > reverse_compat && compat != 1){
                add_conversion(node, 2, type2->type, type1->type);
                node->type = type1;
            } else if (reverse_compat >= compat && compat != 1){
                add_conversion(node, 0, type1->type, type2->type);
                node->type = type2;
            } else {
                node->type = type1;
            }
        }
    } else if (equals(node->name, "expression")){
        if (node->prod_index[1] < 3){
            validate_ast_scope(node->children[0], scope, variables, functions);
            node->type = ((struct SAST_Node*)(node->children[0]))->type;
        } else {
            validate_ast_scope(node->children[0], scope, variables, functions);
            validate_ast_scope(node->children[1], scope, variables, functions);
            struct Type* array_type = ((struct SAST_Node*)(node->children[0]))->type;
            struct Type* index_type = ((struct SAST_Node*)(node->children[1]))->type;
            if (equals(array_type->type,"array")){
                printf("Expression must be of type array to be indexable\n");
                exit(1);
            }
            struct Type* int_type = (struct Type*)malloc(sizeof(struct Type));
            int compat = get_compatibility(int_type, index_type);
            if (compat == 0){
                printf("Index must convertable to type int\n");
                exit(1);
            } else if (compat == 2){
                add_conversion(node, 1, index_type->type, "int");
            }
            node->type = array_type->sub_type;
        }
    } else if (equals(node->name, "function_call")){
        char* name = ((struct Token*)(node->children[0]))->token;
        if (!contains_function(*functions, name, scope)){
            printf("Function \"%s\" does not exist in current scope\n", name);
            exit(1);
        }
        validate_ast_scope(node->children[1], scope, variables, functions);
        struct Type* return_type = get_function_return_type(*functions, name, scope);
        node->type = return_type;
        validate_function_params(get_function_params(*functions, name, scope), node->prod_index[1] == 1? NULL:(node->children[1]), scope, variables, functions);
    } else {
        for (int i = 0; i < node->num_children; i++){
            if (node->is_token[i] || node->children[i] == NULL){
                continue;
            }
            struct SAST_Node* child = node->children[i];
            validate_ast_scope(child, scope, variables, functions);
        }
    }
}

void validate(struct SAST_Node* node, struct Variable_Linked_List** variables, struct Function_Linked_List** functions){
    validate_ast_scope(node, 0, variables, functions);
    struct Function_Linked_List* func_cp = *functions;
    while (func_cp != NULL){
        if (func_cp->value->num_calls <= 0 && !equals(func_cp->value->name, "main")){
            printf("Function \"%s\" is never called\n", func_cp->value->name);
            exit(1);
        }
        func_cp = func_cp->prev;
    }
}