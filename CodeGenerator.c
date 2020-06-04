#include "CodeGenerator.h"

void CodeGenerator (struct node* p, int *count_ident, struct map *ident, FILE *f){
    if (p!=NULL)
    {
        if (strcmp(p->inf, "identifier")==0){
            for (int i=0; i<*count_ident; i++){
                if (strcmp(p->children[0]->inf, ident[i].str)==0){
                    //fprintf(f, "Code Generator: Error(line %d, column %d): Redefinition of '%s'\n",p->children[0]->line, p->children[0]->column, p->children[0]->inf);
                    char *str=(char*)malloc(sizeof(char)*30);
                    strcpy(str, "Redefinition of ");
                    strcat(str, p->children[0]->inf);
                    err_codgen = push_error(p->children[0]->line, p->children[0]->column, str,NULL);
                    free(str);
                    return;
                }
            }
            if (p->children[0]!=NULL){
                fprintf(f, "%s ", p->children[0]->inf);
                *count_ident=*count_ident+1;
            }
        }
        else if (strcmp(p->inf, "procedure-identifier")==0){
            fprintf(f, ";");
        }
        else if (strcmp(p->inf, "=")==0){
            fprintf(f, " equ ");
        }
        else if (strcmp(p->inf, "constant")==0){
            if (p->children[0]!=NULL) {
                fprintf(f, "%s\n", p->children[0]->inf);
            }
        }
        else if (strcmp(p->inf, "constant-declarations")==0){
            fprintf(f, "\n\ndata SEGMENT\n\n");
        }
        else if (strcmp(p->inf, "BEGIN")==0){
            fprintf(f, "\ndata ENDS\n\ncode SEGMENT\n\n\tASSUME cs:code, ds:data\nbegin:\n\tpush	ebp\n\tmov	ebp, esp\n\txor	eax, eax\n\tmov	esp, ebp\n\tpop	ebp\n");
        }
        else if (strcmp(p->inf, "END")==0){
            fprintf(f, "\n\n\tret   0\n\n\tmov ax, 4c00h\n\tint 21h\ncode ENDS\n\tend begin\n\n\n\n");
        }
        for (int i=0; i<p->amount_children; i++)
        {
            CodeGenerator(p->children[i], count_ident,ident, f);
        }
    }
}
