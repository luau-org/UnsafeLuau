#include <ctype.h>
#include "ullex.h"


lex_State* init_lexer(char* source) {
    lex_State* state = calloc(1, sizeof(struct LEX_STATE));
    state->source = source;
    state->sourcelen = strlen(source);
    return state;
}

SemanticInfo* init_string_info(char* s) {
    SemanticInfo* semInfo = calloc(1, sizeof(SemanticInfo));
    semInfo->string = s;
    return semInfo;
}

Token* init_token(int token) {
    Token* token_T = calloc(1, sizeof(struct TOKEN));
    token_T->token = token;
    return token_T;
}

Token* init_token_with_semantic_info(int token, SemanticInfo* semInfo) {
    Token* token_T = init_token(token);
    token_T->seminfo = semInfo;
    return token_T;
}

void lexer_next(lex_State* state) {
    if (state->position < state->sourcelen && state->current != '\0') {
        state->position++;
        state->current = state->source[state->position];
    }
}

int lexer_lookahead(lex_State* state, char character) {
    if (state->source[state->position+1] == character) {
        lexer_next(state);
        return 0;
    }

    return 1;
}

Token* lexer_lex(lex_State* state) {
    while (state->current != '\0') {
        switch (state->current) {
            case ' ':
            case '\f':
            case '\t':
            case '\v': {
                lexer_next(state);
                break;
            }
            case '=': {
                lexer_next(state);
                if (lexer_lookahead(state, '='))
                    return init_token(TK_EQ);  /* '==' */
                else
                    return init_token('=');
            }
            case '<': {
                lexer_next(state);
                if (lexer_lookahead(state, '='))
                    return init_token(TK_LE);  /* '<=' */
                else if (lexer_lookahead(state, '<'))
                    return init_token(TK_SHL);  /* '<<' */
                else
                    return init_token('<');
            }
            case '>': {
                lexer_next(state);
                if (lexer_lookahead(state, '='))
                    return init_token(TK_GE);  /* '>=' */
                else if (lexer_lookahead(state, '<'))
                    return init_token(TK_SHR);  /* '>>' */
                else
                    return init_token('>');
            }
            case ':': {
                lexer_next(state);
                if (lexer_lookahead(state, ':'))
                    return init_token(TK_DBCOLON);
                else
                    return init_token(':');
            }
            case '/': {
                lexer_next(state);
                if (lexer_lookahead(state, '/'))
                    return init_token(TK_IDIV);  /* '//' */
                else
                    return init_token('/');
            }
            case '~': {
                lexer_next(state);
                if (lexer_lookahead(state, '='))
                    return init_token(TK_NE);  /* '~=' */
                else
                    return init_token('~');
            }
            case '.': {
                if (lexer_lookahead(state, '.')) {
                    if (lexer_lookahead(state, '.'))
                        return init_token(TK_DOTS);   /* '...' */
                    else
                        return init_token(TK_CONCAT);   /* '..' */
                }

                return init_token('.');
            }
            case '\"': {

            }
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9': {
                break;
            }
        }
    }

    perror("Missing token handling");
}