#include "tokens.c"

struct Token {
    char* token;
    int type;
    int data;
};

void print_token(struct Token* token){
    printf("Token(token=\"%s\", type=%d)\n", token->token, token->type);
}

int get_token_type(char* str, int token_length){
    for (int i = 0; i < NUM_TOKEN_TYPES; i++){
        if (is_token_type(str, token_length, i)){
            return i;
        }
    }
    return -1;
}

struct Token* get_next_token(char** str){
    while (is_whitespace((*str)[0]) || (*str)[0] == '\0'){
        if ((*str)[0] == '\0'){
            struct Token* token = (struct Token*)malloc(sizeof(struct Token));
            token->type = NUM_TOKEN_TYPES - 1;
            token->token = "\0";
            return token;
        }
        *str = &(*str)[1];
    }
    int token_length = 1;
    int max_token_length = 0;
    int max_token_type = -1;
    if ((*str)[0] == ';'){
        max_token_length = 1;
        max_token_type = get_token_type(*str, max_token_length);
    } else {
        while ((*str)[token_length - 1] != '\0' && (*str)[token_length - 1] != ';'){
            int type = get_token_type(*str, token_length);
            if (type >= 0){
                max_token_length = token_length;
                max_token_type = type;
            }
            token_length++;
        }
    }
    if (max_token_length == 0 || max_token_type < 0){
        printf("Unknown character %c\n", (*str)[0]);
        return NULL;
    }
    // if ((token_type == NUM_TOKEN_TYPES || requres_whitespace[token_type]) && !(is_whitespace((*str)[token_length]) || (*str)[token_length] == '\0')){
    //     printf("Token type %d requires trailing whitespace\n", token_type);
    //     return NULL;
    // }
    struct Token* token = (struct Token*)malloc(sizeof(struct Token));
    token->type = max_token_type;
    copy_to(*str, &(token->token), max_token_length);
    *str = &(*str)[max_token_length];
    return token;
}