#ifndef UNSAFELUAU_LEX_H
#define UNSAFELUAU_LEX_H

#include <limits.h>
#include <malloc.h>
#include <string.h>

#define FIRST_RESERVED	(UCHAR_MAX + 1)

enum RESERVED {
    TK_AND = FIRST_RESERVED, TK_BREAK,
    TK_DO, TK_ELSE, TK_ELSEIF, TK_END, TK_FALSE, TK_FOR, TK_FUNCTION,
    TK_GOTO, TK_IF, TK_IN, TK_LOCAL, TK_NIL, TK_NOT, TK_OR, TK_REPEAT,
    TK_RETURN, TK_THEN, TK_TRUE, TK_UNTIL, TK_WHILE,

    TK_IDIV, TK_CONCAT, TK_DOTS, TK_EQ, TK_GE, TK_LE, TK_NE,
    TK_SHL, TK_SHR,
    TK_DBCOLON, TK_EOS,
    TK_FLT, TK_INT, TK_NAME, TK_STRING
};

typedef union {
    double number;
    int integer;
    char* string;
} SemanticInfo;

typedef struct TOKEN {
    int token;
    SemanticInfo* seminfo;
} Token;

typedef struct LEX_STATE {
    char* source;
    unsigned long long sourcelen;
    int position;
    char current;
} lex_State;

lex_State* init_lexer(char* source);
void lexer_next(lex_State* state);
char lexer_peek(lex_State* state);
int lexer_lookahead(lex_State* state, char character);
Token* lexer_read_identifier(lex_State* state);
Token* lexer_lex(lex_State* state);

#endif
