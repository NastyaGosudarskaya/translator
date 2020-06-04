#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct token
{
    int lex_code;
    int row;
    int column;
} token;
token* fill_token(token*);
char* find_str_po_lex_code(int code);
int count_token(token* tokens);
#endif // TOKEN_H_INCLUDED
