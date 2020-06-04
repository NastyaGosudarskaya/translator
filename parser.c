#include "parser.h"

struct node* parser(token *tokens, AMK* table_amk, int amount_amk,const char *file_out, struct map* ident, struct map *constant, int amount_ident, int amount_constant)
{
    current=0;
    struct node *root = NULL;
    signal_program(tokens, &root, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    FILE *f=fopen(file_out, "at");
    print_tree_in_file(root, 1, f);
    if (err_parser.line != NULL) print_err(err_parser, f, "Parser");
    fprintf(f, "\n");
    fclose(f);
    return root;
}

int signal_program(token *tok, struct node **p, struct AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant)
{
    *p=add_node("signal-program", *p);
    if (choose_func_for_call(table_amk[0].oper_code, tok, *p, table_amk, amount_amk, ident, constant, amount_ident, amount_constant) == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int program(token *tok, struct node *p, struct AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant)
{
    struct node *p2=NULL;
    p2=add_node("program",p);
    int j=find_row_in_amk_po_str("program", table_amk, amount_amk);
    return check_AT_AF(find_amount_row("program", table_amk, amount_amk), j, tok, p2, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
}
int procedure_identifier(token *tok, struct node *p, struct AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant)
{
    struct node *p2=NULL;
    p2=add_node("procedure-identifier",p);
    int j=find_row_in_amk_po_str("procedure-identifier", table_amk, amount_amk);
    int i_count=find_amount_row("procedure-identifier", table_amk, amount_amk);
    return check_AT_AF(i_count, j, tok, p2, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
}

int identifier(token *tok, struct node *p, struct AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant)
{
    struct node *p2=NULL, *p3=NULL;
    p2=add_node("identifier",p);
    for (int i=0; i<amount_ident; i++){
        if (ident[i].key == tok[current].lex_code){
            p3=add_node(ident[i].str, p2);
            p3->column = tok[current].column;
            p3->line = tok[current].row;
            current++;
            return 1;
        }
    }
    char *str=(char*)malloc(sizeof(char)*30);
    strcpy(str, "Expected ");
    strcat(str, p2->inf);
    err_parser = push_error(tok[current-1].row, tok[current-1].column+strlen(find_str_po_lex_code(tok[current-1].lex_code)),str, NULL);
    free(str);
    return 0;
}
int constant_identifier(token *tok, struct node *p, struct AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant)
{
    struct node *p2=NULL;
    p2=add_node("constant-identifier",p);
    int j=find_row_in_amk_po_str("constant-identifier", table_amk, amount_amk);
    int i_count=find_amount_row("constant-identifier", table_amk, amount_amk);
    return check_AT_AF(i_count, j, tok, p2, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
}
int block(token *tok, struct node *p, struct AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant)
{
    struct node *p2=NULL;
    p2=add_node("block",p);
    int j=find_row_in_amk_po_str("block", table_amk, amount_amk);
    return check_AT_AF(find_amount_row("block", table_amk, amount_amk), j, tok, p2, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
}

int statements_list(token *tok, struct node *p, struct AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant)
{
    struct node *p2=NULL;
    p2=add_node("statements-list",p);
    if ((count_token(tok) != current) && ((strcmp(find_str_po_lex_code(tok[current].lex_code), "IF")==0)))
    {
        int j=find_row_in_amk_po_str("statements-list", table_amk, amount_amk);
        return check_AT_AF(find_amount_row("statements-list", table_amk, amount_amk), j, tok, p2, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    }
    else
    {
        struct node *p3=NULL;
        p3=add_node("empty",p2);
        return 1;
    }
}

int declarations(token *tok, struct node *p, struct AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant)
{
    struct node *p2=NULL;
    p2=add_node("declarations",p);
    int j=find_row_in_amk_po_str("declarations", table_amk, amount_amk);
    return check_AT_AF(find_amount_row("declarations", table_amk, amount_amk), j, tok, p2, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
}
int constant_declarations(token *tok, struct node *p, struct AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant)
{
    struct node *p2=NULL;
    p2=add_node("constant-declarations",p);
    if ((count_token(tok) != current) && (strcmp(find_str_po_lex_code(tok[current].lex_code), "CONST")==0))
    {
        int j=find_row_in_amk_po_str("constant-declarations", table_amk, amount_amk);
        return check_AT_AF(find_amount_row("constant-declarations", table_amk, amount_amk), j, tok, p2, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    }
    else
    {
        struct node *p3=NULL;
        p3=add_node("empty",p2);
        return 1;
    }
}
int constant_declarations_list(token *tok, struct node *p, struct AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant)
{
    struct node *p2=NULL;
    p2=add_node("constant-declarations-list",p);
    if (tok[current].lex_code<700 && tok[current].lex_code>600)
    {
        int j=find_row_in_amk_po_str("constant-declarations-list", table_amk, amount_amk);
        return check_AT_AF(find_amount_row("constant-declarations-list", table_amk, amount_amk), j, tok, p2, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    }
    else
    {
        struct node *p3=NULL;
        p3=add_node("empty",p2);
        return 1;
    }
}
int constant_declaration(token *tok, struct node *p, struct AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant)
{
    struct node *p2=NULL;
    p2=add_node("constant-declaration",p);
    int j=find_row_in_amk_po_str("constant-declaration", table_amk, amount_amk);
    return check_AT_AF(find_amount_row("constant-declaration", table_amk, amount_amk), j, tok, p2, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
}
int constanta(token *tok, struct node *p, struct AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant)
{
    struct node *p2=NULL, *p3=NULL;
    p2=add_node("constant",p);
    for (int i=0; i<amount_constant; i++){
        if (constant[i].key == tok[current].lex_code){
            p3=add_node(constant[i].str, p2);
            p3->column = tok[current].column;
            p3->line = tok[current].row;
            current++;
            return 1;
        }
    }
    char *str=(char*)malloc(sizeof(char)*30);
    strcpy(str, "Expected ");
    strcat(str, p2->inf);
    err_parser = push_error(tok[current-1].row, tok[current-1].column+strlen(find_str_po_lex_code(tok[current-1].lex_code)),str, NULL);
    free(str);
    return 0;
}
int choose_func_for_call(char *oper_code, token *tok, struct node *p, struct AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant)
{
    int flag=0;
    if (strcmp(oper_code, "<signal-program>")==0)
        flag = signal_program(tok, p, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    if (strcmp(oper_code, "<program>")==0)
        flag = program(tok, p, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    if (strcmp(oper_code, "<procedure-identifier>")==0)
        flag = procedure_identifier(tok, p, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    if (strcmp(oper_code, "<block>")==0)
        flag = block(tok, p, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    if (strcmp(oper_code, "<statements-list>")==0)
        flag = statements_list(tok, p, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    if (strcmp(oper_code, "<declarations>")==0)
        flag = declarations(tok, p, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    if (strcmp(oper_code, "<constant-declarations>")==0)
        flag = constant_declarations(tok, p,table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    if (strcmp(oper_code, "<constant-declarations-list>")==0)
        flag = constant_declarations_list(tok, p,table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    if (strcmp(oper_code, "<constant-declaration>")==0)
        flag = constant_declaration(tok, p, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    if (strcmp(oper_code, "<constant>")==0)
        flag = constanta(tok, p, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    if (strcmp(oper_code, "<constant-identifier>")==0)
        flag = constant_identifier(tok, p, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    if (strcmp(oper_code, "<identifier>")==0)
        flag = identifier(tok, p, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    if (strcmp(oper_code, "<statement>")==0)
        flag = statement(tok, p, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    if (strcmp(oper_code, "<cond>")==0)
        flag = cond(tok, p, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    if (strcmp(oper_code, "<else>")==0)
        flag = ELSE(tok, p, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);

    return flag;
}

int find_row_in_amk_po_str(char *str, struct AMK* table_amk, int amount_amk)
{
    for (int i=0; i<amount_amk; i++)
    {
        if (strcmp(table_amk[i].addr, str)==0)
        {
            return i;
        }
    }
    return -1;
}
int find_amount_row(char *str, struct AMK* table_amk, int amount_amk)
{
    int count=0;
    for (int i=0; i<amount_amk; i++)
    {
        if (strcmp(table_amk[i].addr, str)==0)
        {
            count++;
        }
    }
    return count;
}
int check_AT_AF(int i_count, int j, token *tok, struct node *p2, struct AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant)
{
    if (count_token(tok)==0)
    {
        char *str=(char*)malloc(sizeof(char)*30);
        strcpy(str, "Expected ");
        strcat(str, p2->inf);
        err_parser = push_error(1, 1, str, NULL);
        free(str);
        return 0;
    }
    for (int i=0; i<i_count; i++)
    {
        if (table_amk[j+i].oper_code[0]=='<')
        {
            if (choose_func_for_call(table_amk[j+i].oper_code, tok, p2, table_amk, amount_amk, ident, constant, amount_ident, amount_constant) == 1)
            {
                if (table_amk[j+i].AT==1)
                {
                    return 1;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                if (table_amk[j+i].AF==1)
                {
                    return 0;
                }
                else
                {
                    continue;
                }
            }
        }
        else
        {
            if (count_token(tok) == current)
            {
                char *str=(char*)malloc(sizeof(char)*30);
                strcpy(str, "Expected ");
                strcat(str, table_amk[j+i].oper_code);
                err_parser = push_error(tok[current-1].row, tok[current-1].column + strlen(find_str_po_lex_code(tok[current-1].lex_code)), str, NULL);
                free(str);
                return 0;
            }
            if (strcmp(find_str_po_lex_code(tok[current].lex_code), table_amk[j+i].oper_code)==0)
            {
                struct node *p3=NULL;
                p3=add_node(find_str_po_lex_code(tok[current].lex_code), p2);
                if (table_amk[j+i].AT==1)
                {
                    current++;
                    return 1;
                }
                else
                {
                    current++;
                    continue;
                }
            }
            else
            {
                if (table_amk[j+i].AF==1)
                {
                    char *str=(char*)malloc(sizeof(char)*30);
                    strcpy(str, "Expected ");
                    strcat(str, table_amk[j+i].oper_code);
                    err_parser = push_error(tok[current].row, tok[current].column, str, NULL);
                    free(str);
                    return 0;
                }
                else
                {
                    continue;
                }
            }
        }
    }
    char *str=(char*)malloc(sizeof(char)*30);
    strcpy(str, "Expected ");
    strcat(str, p2->inf);
    err_parser = push_error(tok[current-1].row, tok[current-1].column + strlen(find_str_po_lex_code(tok[current-1].lex_code)), str, NULL);
    free(str);
}



int statement(token *tok, struct node *p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant){
    struct node *p2=NULL;
    p2=add_node("statement",p);
    int j=find_row_in_amk_po_str("statement", table_amk, amount_amk);
    return check_AT_AF(find_amount_row("statement", table_amk, amount_amk), j, tok, p2, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);

}
int cond(token *tok, struct node *p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant){
    struct node *p2=NULL;
    p2=add_node("cond",p);
    int j=find_row_in_amk_po_str("cond", table_amk, amount_amk);
    return check_AT_AF(find_amount_row("cond", table_amk, amount_amk), j, tok, p2, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
}
int ELSE(token *tok, struct node *p, AMK* table_amk, int amount_amk, struct map* ident, struct map *constant, int amount_ident, int amount_constant){
    struct node *p2=NULL;
    p2=add_node("else",p);

    if ((count_token(tok) != current) && (strcmp(find_str_po_lex_code(tok[current].lex_code), "ELSE")==0))
    {
        int j=find_row_in_amk_po_str("ELSE", table_amk, amount_amk);
        return check_AT_AF(find_amount_row("ELSE", table_amk, amount_amk), j, tok, p2, table_amk, amount_amk, ident, constant, amount_ident, amount_constant);
    }
    else
    {
        struct node *p3=NULL;
        p3=add_node("empty",p2);
        return 1;
    }

}
