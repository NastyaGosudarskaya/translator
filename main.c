#include "tree.h"
#include "header_for_lexer.h"
#include "parser.h"
#include "CodeGenerator.h"

int main(int argc, const char *argv[])
{
    if(argc>1)
    {
        //lexer
        struct map keywords[keywords_size], delim[delim_size], *ident=NULL, *constant=NULL;

        int *SymbolCategories = fill_attr(SymbolCategories);
        fill_tables(keywords, delim);
        int amount_ident=0, amount_constant=0;
        char *str1=(char*)malloc(sizeof(char) * (strlen(argv[1])+9));
        strcpy(str1, argv[1]);
        char *str2=(char*)malloc(sizeof(char) * (strlen(argv[1]) + 12));
        strcpy(str2, argv[1]);
        strcat(str1, "input.sig");
        strcat(str2, "expected.txt");
        lexer(str1, SymbolCategories, &amount_ident, &amount_constant, keywords, delim, &ident, &constant, str2);
        free(SymbolCategories);
        print_tables(amount_ident, amount_constant, keywords, delim, ident, constant);
        //parser
        struct AMK *table_amk=NULL;
        int amount_amk=fill_amk_table(&table_amk);
        print_AMK_table(amount_amk, table_amk);
        token *tokens=NULL;
        tokens = fill_token(tokens);

        struct node *root=NULL;
        root = parser(tokens, table_amk, amount_amk, str2, ident, constant, amount_ident, amount_constant);

        //code generator
        int count_ident=0, count_constant=0;
        FILE *f=fopen(str2,"at");
        CodeGenerator(root, &count_ident, ident, f);
        if (err_codgen.line!=NULL) print_err(err_codgen, f, "Code Generator");
        fclose(f);
        free(str1);
        free(str2);
    }
    return 0;
}
