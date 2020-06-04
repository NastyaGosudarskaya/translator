#include "AMK.h"
void print_AMK_table(int amount, AMK *table_amk)
{
    FILE *f=fopen("amk_table.txt", "wt");
    for (int i=0; i<amount; i++)
    {
        fprintf(f, "%-5d %-30s %-30s %-1d %-1d\n",i ,table_amk[i].addr, table_amk[i].oper_code, table_amk[i].AT,  table_amk[i].AF);
    }
    fclose(f);
}

int fill_amk_table(AMK **table_amk)
{
    *table_amk=(AMK*)malloc(33 * sizeof(AMK));

    (*table_amk)[0].addr="signal-program";
    (*table_amk)[0].oper_code="<program>";
    (*table_amk)[0].AT=1;
    (*table_amk)[0].AF=1;

    (*table_amk)[1].addr="program";
    (*table_amk)[1].oper_code="PROGRAM";
    (*table_amk)[1].AT=0;
    (*table_amk)[1].AF=1;

    (*table_amk)[2].addr="program";
    (*table_amk)[2].oper_code="<procedure-identifier>";
    (*table_amk)[2].AT=0;
    (*table_amk)[2].AF=1;

    (*table_amk)[3].addr="program";
    (*table_amk)[3].oper_code=";";
    (*table_amk)[3].AT=0;
    (*table_amk)[3].AF=1;

    (*table_amk)[4].addr="program";
    (*table_amk)[4].oper_code="<block>";
    (*table_amk)[4].AT=0;
    (*table_amk)[4].AF=1;

    (*table_amk)[5].addr="program";
    (*table_amk)[5].oper_code=".";
    (*table_amk)[5].AT=1;
    (*table_amk)[5].AF=1;

    (*table_amk)[6].addr="procedure-identifier";
    (*table_amk)[6].oper_code="<identifier>";
    (*table_amk)[6].AT=1;
    (*table_amk)[6].AF=1;

    int i=7;

    (*table_amk)[i].addr="block";
    (*table_amk)[i].oper_code="<declarations>";
    (*table_amk)[i].AT=0;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="block";
    (*table_amk)[i].oper_code="BEGIN";
    (*table_amk)[i].AT=0;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="block";
    (*table_amk)[i].oper_code="<statements-list>";
    (*table_amk)[i].AT=0;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="block";
    (*table_amk)[i].oper_code="END";
    (*table_amk)[i].AT=1;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="declarations";
    (*table_amk)[i].oper_code="<constant-declarations>";
    (*table_amk)[i].AT=1;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="constant-declarations";
    (*table_amk)[i].oper_code="CONST";
    (*table_amk)[i].AT=0;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="constant-declarations";
    (*table_amk)[i].oper_code="<constant-declarations-list>";
    (*table_amk)[i].AT=1;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="constant-declarations-list";
    (*table_amk)[i].oper_code="<constant-declaration>";
    (*table_amk)[i].AT=0;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="constant-declarations-list";
    (*table_amk)[i].oper_code="<constant-declarations-list>";
    (*table_amk)[i].AT=1;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="constant-declaration";
    (*table_amk)[i].oper_code="<constant-identifier>";
    (*table_amk)[i].AT=0;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="constant-declaration";
    (*table_amk)[i].oper_code="=";
    (*table_amk)[i].AT=0;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="constant-declaration";
    (*table_amk)[i].oper_code="<constant>";
    (*table_amk)[i].AT=1;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="constant-identifier";
    (*table_amk)[i].oper_code="<identifier>";
    (*table_amk)[i].AT=1;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="statements-list";
    (*table_amk)[i].oper_code="<statement>";
    (*table_amk)[i].AT=0;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="statements-list";
    (*table_amk)[i].oper_code="<statements-list>";
    (*table_amk)[i].AT=1;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="statement";
    (*table_amk)[i].oper_code="IF";
    (*table_amk)[i].AT=0;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="statement";
    (*table_amk)[i].oper_code="<cond>";
    (*table_amk)[i].AT=0;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="statement";
    (*table_amk)[i].oper_code="THEN";
    (*table_amk)[i].AT=0;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="statement";
    (*table_amk)[i].oper_code="<statements-list>";
    (*table_amk)[i].AT=0;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="statement";
    (*table_amk)[i].oper_code="<else>";
    (*table_amk)[i].AT=0;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="statement";
    (*table_amk)[i].oper_code="ENDIF";
    (*table_amk)[i].AT=1;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="cond";
    (*table_amk)[i].oper_code="<identifier>";
    (*table_amk)[i].AT=0;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="cond";
    (*table_amk)[i].oper_code="=";
    (*table_amk)[i].AT=0;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="cond";
    (*table_amk)[i].oper_code="<identifier>";
    (*table_amk)[i].AT=1;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="ELSE";
    (*table_amk)[i].oper_code="ELSE";
    (*table_amk)[i].AT=0;
    (*table_amk)[i].AF=1;
    i++;

    (*table_amk)[i].addr="ELSE";
    (*table_amk)[i].oper_code="<statements-list>";
    (*table_amk)[i].AT=1;
    (*table_amk)[i].AF=1;
    i++;

    //ELSE <statements-list>
    //IF <cond> THEN <statements-list> <else> ENDIF
    return i;
}
