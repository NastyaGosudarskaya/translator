#include <stdio.h>
#include <stdlib.h>
#include "header_for_lexer.h"

void lexer(char * file, int *SymbolCategories, int *count_ident, int *count_constant, struct map keywords[keywords_size], struct map delim[delim_size], struct map **ident, struct map **constant, char *file_out)
{
    *count_ident=0;
    *count_constant=0;
    FILE *f, *out, *out2;
    int flag_err=0;
    if (f = fopen(file, "rt"))
    {
        out=fopen(file_out,"wt");
        out2=fopen("result.txt","wt");
        char symb = fgetc(f);
        int row=1, column=0;
        char *buffer=NULL;
        while (symb!=EOF)
        {
            column++;
            //ws
            if (SymbolCategories[(int)symb] == 0)
            {
                if (symb=='\n')
                {
                    row++;
                    column=0;
                }
                symb = fgetc(f);
                continue;
            }
            //digit or +,-
            if (SymbolCategories[(int)symb] == 1 || SymbolCategories[(int)symb] == 4)
            {
                char *buffer=(char *) malloc(sizeof(char));
                int i=0;
                buffer[i++]=symb;
                symb = fgetc(f);
                column++;
                int flag=0;
                while ((SymbolCategories[(int)symb] == 1))
                {
                    buffer = (char*)realloc(buffer, (i+1)* sizeof(char));
                    buffer[i++]=symb;
                    symb = fgetc(f);
                    column++;
                    flag=1;
                }
                if ((buffer[0]== '+' || buffer[0]== '-')&&flag==0)
                {
                    char *error_text="Expected digit after";
                    err_lexer=push_error(row, column-1, error_text, buffer[0]);
                    //printf("Lexer: ERROR(line %d, column %d): Expected digit after '%c'\n", row, column-1, buffer[0]);
                    flag_err=1;
                    break;
                }
                column--;
                if (symb=='#')
                {
                    column++;
                    buffer = (char*)realloc(buffer, (i+1)* sizeof(char));
                    buffer[i++]=symb;
                    symb = fgetc(f);
                    int flag = 0;
                    if (SymbolCategories[(int)symb] == 4)
                    {
                        column++;
                        buffer = (char*)realloc(buffer, (i+1)* sizeof(char));
                        buffer[i++]=symb;
                        symb = fgetc(f);
                    }
                    while ((SymbolCategories[(int)symb] == 1))
                    {
                        column++;
                        buffer = (char*)realloc(buffer, (i+1)* sizeof(char));
                        buffer[i++]=symb;
                        symb = fgetc(f);
                        flag=1;
                    }
                    if (flag==0)
                    {
                        char *error_text="Expected digit after '#'\n";
                        err_lexer=push_error(row, column, error_text, NULL);
                        //printf("Lexer: ERROR(line %d, column %d): Expected digit after '#'\n", row, column);
                        flag_err=1;
                        break;
                    }
                }
                buffer = (char*)realloc(buffer, i * sizeof(char));
                buffer[i]='\0';

                if (*constant==NULL)
                {
                    *constant=(struct map*)malloc(sizeof(struct map));
                }
                else
                {
                    for (i=0; i<*count_constant; i++)
                    {
                        if (strcmp((*constant)[i].str, buffer) == 0)
                        {
                            fprintf(out, "%d %d %d \t", (*constant)[i].key,row, column - strlen(buffer) + 1);
                            fprintf(out2, "%d %d %d\n", (*constant)[i].key,row, column - strlen(buffer) + 1);
                            fputs((*constant)[i].str, out);
                            fprintf(out, "\t CONSTANT\n");
                            break;
                        }
                    }
                    if (i==*count_constant)
                    {
                        *constant=(struct map*)realloc(*constant, (*count_constant + 1) * sizeof(struct map));
                    }
                    else
                    {
                        free(buffer);
                        continue;
                    }
                }
                (*constant)[*count_constant].key=501+ *count_constant;
                (*constant)[*count_constant].str=(char*)malloc(sizeof(char)*strlen(buffer));
                strcpy((*constant)[*count_constant].str, buffer);
                fprintf(out, "%d %d %d \t", (*constant)[*count_constant].key,row, column - strlen(buffer) + 1);
                fprintf(out2, "%d %d %d\n", (*constant)[*count_constant].key,row, column - strlen(buffer) + 1);
                fputs((*constant)[*count_constant].str, out);
                fprintf(out, "\t CONSTANT\n");
                *count_constant = *count_constant+1;
                free(buffer);
                continue;
            }
            //let
            if (SymbolCategories[(int)symb] == 2)
            {
                char *buffer=(char *) malloc(sizeof(char));
                int i=0;
                buffer[i++]=symb;
                symb = fgetc(f);
                column++;
                while ((SymbolCategories[(int)symb] == 1) || (SymbolCategories[(int)symb] == 2))
                {
                    buffer = (char*)realloc(buffer, (i+1)* sizeof(char));
                    buffer[i++]=symb;
                    symb = fgetc(f);
                    column++;
                }
                column--;
                buffer = (char*)realloc(buffer, i * sizeof(char));
                buffer[i]='\0';
                for (i=0; i<keywords_size; i++)
                {
                    if (strcmp(keywords[i].str, buffer)==0)
                    {
                        fprintf(out, "%d %d %d \t", keywords[i].key,row, column - strlen(buffer) + 1);
                        fprintf(out2, "%d %d %d\n", keywords[i].key,row, column - strlen(buffer) + 1);
                        fputs(keywords[i].str, out);
                        fprintf(out, "\t KEYWORDS\n");
                        break;
                    }
                }
                if (i == keywords_size)
                {
                    if (*ident==NULL)
                    {
                        *ident=(struct map*)malloc(sizeof(struct map));
                    }
                    else
                    {
                        for (i=0; i<*count_ident; i++)
                        {
                            if (strcmp((*ident)[i].str, buffer) == 0)
                            {
                                fprintf(out, "%d %d %d \t", (*ident)[i].key,row, column - strlen(buffer) + 1);
                                fprintf(out2, "%d %d %d\n", (*ident)[i].key,row, column - strlen(buffer) + 1);
                                fputs((*ident)[i].str, out);
                                fprintf(out, "\t IDENTIFIER\n");
                                break;
                            }
                        }
                        if (i==*count_ident)
                        {
                            *ident=(struct map*)realloc(*ident, (*count_ident + 1) * sizeof(struct map));
                        }
                        else
                        {
                            free(buffer);
                            continue;
                        }
                    }
                    (*ident)[*count_ident].key=601+(*count_ident);
                    (*ident)[*count_ident].str=(char*)malloc(sizeof(char)*strlen(buffer));
                    strcpy((*ident)[*count_ident].str, buffer);
                    fprintf(out, "%d %d %d \t", (*ident)[*count_ident].key,row, column - strlen(buffer) + 1);
                    fprintf(out2, "%d %d %d\n", (*ident)[*count_ident].key,row, column - strlen(buffer) + 1);
                    fputs((*ident)[*count_ident].str, out);
                    fprintf(out, "\t IDENTIFIER\n");
                    *count_ident=*count_ident+1;
                }
                free(buffer);
                continue;
            }
            //dlm
            if (SymbolCategories[(int)symb] == 3)
            {
                fprintf(out, "%d  %d %d \t %c \t DELIMITER\n", (int)symb,row, column, symb);
                fprintf(out2, "%d %d %d\n", (int)symb,row, column, symb);
                symb = fgetc(f);
                continue;
            }
            //com
            if (SymbolCategories[(int)symb] == 5)
            {
                int begin_com_column = column, begin_com_row=row;
                symb = fgetc(f);
                column++;
                if (symb=='*')
                {
                    symb = fgetc(f);
                    while (symb!=EOF)
                    {
                        if (symb=='\n')
                        {
                            column=0;
                            row++;
                            symb = fgetc(f);
                            continue;
                        }
                        else
                        {
                            column++;
                        }
                        if (symb=='*')
                        {
                            symb = fgetc(f);
                            if (symb==')')
                            {
                                column++;
                                symb = fgetc(f);
                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }
                        symb = fgetc(f);
                    }
                    if (symb==EOF)
                    {
                        char *error_text="unterminated comment\n";
                        err_lexer=push_error(begin_com_row, begin_com_column, error_text, NULL);
                        //printf("Lexer: ERROR(line %d, column %d): unterminated comment\n", begin_com_row, begin_com_column);
                        flag_err=1;
                        break;
                    }
                }
                else
                {
                    char *error_text="Expected '*' after '('\n";
                    err_lexer=push_error(row, column, error_text, NULL);
                    //printf("Lexer: ERROR(line %d, column %d): Expected '*' after '('\n", row, column);
                    flag_err=1;
                    break;
                }
            }
            //err
            if (SymbolCategories[(int)symb] == 6)
            {
                char *error_text=(char)malloc(20*sizeof(char));
                error_text="Illegal symbol";
                err_lexer=push_error(row, column, error_text, symb);
                //printf("Lexer: ERROR(line %d, column %d): Illegal symbol '%c'\n", row, column, symb);
                flag_err=1;
                break;
            }
        }
        if (flag_err==1) print_err(err_lexer,out ,"Lexer");
        fclose(f);
        fprintf(out, "\n");
        fclose(out);
        fclose(out2);
    }
    else
    {
        printf("Can't open the file");
    }
}

int* fill_attr(int *SymbolCategories)
{
    SymbolCategories=(int*)malloc(128*sizeof(int));

    for (int i = 0; i < 128; i++)
        SymbolCategories[i] = 6;

    for (int i = 9; i <= 13; i++)
        SymbolCategories[i] = 0;
    SymbolCategories[32] = 0;

    for (int i = 48; i <= 57; i++)
        SymbolCategories[i] = 1;

    for (int i = 65; i <= 90; i++)
        SymbolCategories[i] = 2;

    SymbolCategories[35] = 3;
    SymbolCategories[41] = 3;
    SymbolCategories[46] = 3;
    SymbolCategories[59] = 3;
    SymbolCategories[61] = 3;

    SymbolCategories[40] = 5;

    SymbolCategories[43] = 4;//+
    SymbolCategories[45] = 4;//-

    return SymbolCategories;
}
void fill_tables(struct map keywords[keywords_size], struct map delim[delim_size])
{
    for (int i=0; i<8; i++)
    {
        keywords[i].key=301+i;
    }
    keywords[0].str="PROGRAM";
    keywords[1].str="CONST";
    keywords[2].str="BEGIN";
    keywords[3].str="END";
    keywords[4].str="IF";
    keywords[5].str="THEN";
    keywords[6].str="ELSE";
    keywords[7].str="ENDIF";

    delim[0].str=";";
    delim[1].str="=";
    delim[2].str="#";
    delim[3].str=")";
    delim[4].str=".";
    for (int i=0; i<delim_size; i++)
    {
        delim[i].key=(int)delim[i].str[0];
    }
}

void print_tables(int count_ident, int count_constant,  struct map keywords[keywords_size], struct map delim[delim_size], struct map *ident, struct map *constant)
{
    FILE *f = fopen("identifiers.txt", "wt");
    int i=0;
    //printf("Identifiers:\n\n");
    for (i=0; i<count_ident;i++)
    {
        fprintf(f,"%d ", ident[i].key);
        fputs(ident[i].str, f);
        fprintf(f, "\n");
    }
    fclose(f);
    f = fopen("constants.txt", "wt");
    //printf("____________________\nConstants:\n\n");
    for (i=0; i<count_constant;i++)
    {
        fprintf(f, "%d ", constant[i].key);
        fputs(constant[i].str, f);
        fprintf(f, "\n");
    }
    fclose(f);
    f = fopen("keywords.txt", "wt");
    //printf("____________________\nKeywords:\n\n");
    for (i=0; i<keywords_size;i++)
    {
        fprintf(f, "%d ", keywords[i].key);
        fputs(keywords[i].str, f);
        fprintf(f, "\n");
    }
    fclose(f);
    f = fopen("delimiters.txt", "wt");
    //printf("____________________\nDelimiters:\n\n");
    for (i=0; i<delim_size;i++)
    {
        fprintf(f, "%d ", delim[i].key);
        fputs(delim[i].str, f);
        fprintf(f, "\n");
    }
    fclose(f);
}
