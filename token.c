#include "token.h"
int count_token(token* tokens)
{
    FILE *f;
    if(f=fopen("result.txt","rt"))
    {
        int count_row=0;
        char *str=(char*)malloc(sizeof(char)*32);
        while(fgets(str, 255, f))
        {
            count_row++;
        }
        fclose(f);
        return count_row;
    }
    else
    {
        printf("Can't open file 'result.txt'");
    }
}
token* fill_token(token* tokens)
{
    FILE *f;
    if(f=fopen("result.txt","rt"))
    {
        int count_row=0;
        char *str=(char*)malloc(sizeof(char)*32);
        while(fgets(str, 255, f))
        {
            count_row++;
        }
        rewind(f);
        int i=0;
        tokens=(token*)malloc(count_row*sizeof(token));
        while(i<count_row)
        {
            fscanf(f, "%d %d %d", &tokens[i].lex_code, &tokens[i].row, &tokens[i].column);
            //printf("%d %d %d\n", tokens[i].lex_code, tokens[i].row, tokens[i].column);
            i++;
        }
        fclose(f);
        return tokens;
    }
    else
    {
        printf("Can't open file 'result.txt'");
    }
}
char* find_str_po_lex_code(int code)
{
    FILE *f;
    if (600<code && 700>code)
    {
        f=fopen("identifiers.txt","rt");
    }
    if (300<code && 400>code)
    {
        f=fopen("keywords.txt","rt");
    }
    if (500<code && 600>code)
    {
        f=fopen("constants.txt","rt");
    }
    if (0<code && 100>code)
    {
        f=fopen("delimiters.txt","rt");
    }
    char *str=malloc(sizeof(char));
    int code_from_table;
    while(fscanf(f, "%d %s", &code_from_table, str)!=EOF)
    {
        if (code_from_table==code)
        {
            fclose(f);
            return str;
        }
        //free(str);
    }
}
