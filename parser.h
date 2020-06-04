#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "tree.h"
#include "token.h"
#include "Error.h"
#include "AMK.h"
#include "header_for_lexer.h"

struct node* parser(token *tokens, AMK* table_amk, int amount_amk, const char *file_out, struct map* ident, struct map *constant, int amount_ident, int amount_constant);
int signal_program(token *tok, struct node **p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant);
int program(token *tok, struct node *p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant);
int procedure_identifier(token *tok, struct node *p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant);
int constant_identifier(token *tok, struct node *p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant);
int identifier(token *tok, struct node *p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant);
int block(token *tok, struct node *p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant);
int statements_list(token *tok, struct node *p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant);
int declarations(token *tok, struct node *p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant);
int constant_declarations(token *tok, struct node *p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant);
int constant_declarations_list(token *tok, struct node *p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant);
int constant_declaration(token *tok, struct node *p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant);
int constanta(token *tok, struct node *p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant);
int choose_func_for_call(char *oper_code, token *tok, struct node *p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant);
int find_row_in_amk_po_str(char *str, AMK* table_amk, int amount_amk);
int find_amount_row(char *str, AMK* table_amk, int amount_amk);
int check_AT_AF(int i_count, int j, token *tok, struct node *p2, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant);


int statement(token *tok, struct node *p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant);
int cond(token *tok, struct node *p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant);
int ELSE(token *tok, struct node *p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant);

error err_parser;
int current;

#endif // PARSER_H_INCLUDED
