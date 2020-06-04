#ifndef CODEGENERATOR_H_INCLUDED
#define CODEGENERATOR_H_INCLUDED

#include "tree.h"
#include "header_for_lexer.h"
#include "Error.h"

void CodeGenerator (struct node* p, int*, struct map *ident, FILE *f);

error err_codgen;
#endif // CODEGENERATOR_H_INCLUDED
