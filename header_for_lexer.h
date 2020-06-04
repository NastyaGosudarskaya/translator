#ifndef HEADER_FOR_LEXER_H_INCLUDED
#define HEADER_FOR_LEXER_H_INCLUDED

#define keywords_size 8
#define delim_size 5
#include "Error.h"
#include "token.h"
struct map
{
    char *str;
    int key;
};

void lexer(char * file, int *SymbolCategories, int *count_ident, int *count_constant, struct map keywords[keywords_size], struct map delim[delim_size], struct map **ident, struct map **constant, char *file_out);
int* fill_attr(int *SymbolCategories);
void fill_tables(struct map keywords[keywords_size], struct map delim[delim_size]);
void print_tables(int count_ident, int count_constant,  struct map keywords[keywords_size], struct map delim[delim_size], struct map *ident, struct map *constant);

error err_lexer;
#endif // HEADER_FOR_LEXER_H_INCLUDED
