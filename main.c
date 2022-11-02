#include <stdio.h>
#include <debugapi.h>
#include "Compiler/ullex.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        perror("Incorrect amount of arguments passed, should be \"uluau.exe <version> <optimization> <file>\"");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(argv[3], "r");

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* string = malloc(fsize + 1);
    fread(string, fsize, 1, fp);
    fclose(fp);

    lex_State* ls = init_lexer(string);

    printf("%llu", ls->sourcelen);

    while (ls->current != '\0') {
        Token* token_T = lexer_lex(ls);
        printf("%d", token_T->token);
    }

    return 0;
}
