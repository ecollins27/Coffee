int equals(char* str1, char* str2){
    int index = 0;
    while (1){
        if (str1[index] != str2[index]){
            return 0;
        } else if (str1[index] == '\0'){
            return 1;
        }
        index++;
    }
}

void copy_to(char* src, char** dest, int length){
    *dest = (char*)malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; i++){
        (*dest)[i] = src[i];
    }
    (*dest)[length] = '\0';
}

int equals_l(char* str1, char* str2, int length){
    for (int i = 0; i < length; i++){
        if (str1[i] != str2[i]){
            return 0;
        }
    }
    return 1;
}

int is_whitespace(char c){
    return c == '\t' || c == '\n' || c == ' ';
}

int is_numeric(char c){
    return c >= 48 && c <= 57;
}

int is_letter(char c){
    return (c >= 65 && c<= 90) || (c >= 97 && c<= 122);
}

int is_name(char* str, int length){
    if (str[0] == '\0'){
        return 0;
    }
    for (int i = 0; i < length; i++){
        if (i == 0 && !is_letter(str[i]) && str[i] != '_'){
            return 0;
        } else if (!is_letter(str[i]) && !is_numeric(str[i]) && str[i] != '_'){
            return 0;
        }
    }
    return 1;
}

int is_integer(char* str, int length, int require_positive){
    if (!require_positive && str[0] == '-'){
        return is_integer(&str[1], length - 1, 1);
    }
    for (int i = 0; i < length; i++){
        if (!is_numeric(str[i])){
            return 0;
        }
    }
    return 1;
}

int is_number(char* str, int length, int require_positive){
    if (!require_positive && str[0] == '-'){
        return is_number(&str[1], length - 1, 1);
    }
    for (int i = 0; i < length; i++){
        if (str[i] == '.'){
            return is_number(&str[i + 1], length - i, 1);
        } else if (!is_numeric(str[i])){
            return 0;
        }
    }
    return 1;
}

int is_valid_string(char* str, int length){
    if (str[0] != '\"' || str[length - 1] != '\"'){
        return 0;
    }
    for (int i = 1; i < length - 1; i++){
        if (!(str[i] >= 32 && str[i] <= 126) || str[i] == '\"'){
            return 0;
        }
    }
    return 1;
}