#include <stdlib.h>
#include <stdio.h>
#include "generator.c"

char* read_file(char* filename){
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    if (fseek(file, 0L, SEEK_END) != 0) {
        fclose(file);
        exit(1);
    }
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        exit(1);
    }
    rewind(file);

    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        fclose(file);
        perror("Memory allocation failed");
        exit(1);
    }
    size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
    buffer[bytes_read] = '\0';

    fclose(file);
    return buffer;
}

int main(int argc, char** argv){
    if (argc < 2){
        printf("Input required\n");
        exit(1);
    }
    char* file_contents = read_file(argv[1]);
    struct AST_Node* node = parse_ast(read_file(argv[1]));
    struct SAST_Node* simp_node = simplify(node);
    struct Variable_Linked_List* variables = NULL;
    struct Function_Linked_List* functions = NULL;
    validate(simp_node, &variables, &functions);
    generate_code("test.j", simp_node, variables, functions);
    free(file_contents);
    return 0;
}

/*
TODO:
    - Implement predefined functions such as print
*/