#include "Error.h"

error push_error(int line, int column, char *text, char symb){
    error err;
    err.column=column;
    err.line=line;
    err.text=(char*)malloc(sizeof(char)*strlen(text));
    strcpy(err.text, text);
    err.symb=symb;
    return err;
}

void print_err(error err, FILE *file_out, char *type){
    if (err.symb!=NULL){
        fprintf(file_out,"\n\n%s:Error(line %d, column %d): %s '%c'\n\n",type, err.line, err.column, err.text, err.symb);
    }
    else{
        fprintf(file_out,"\n\n%s:Error(line %d, column %d): %s\n\n",type, err.line, err.column, err.text);
    }
}
