#ifndef AMK_H_INCLUDED
#define AMK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AMK
{
    char *addr;
    char *oper_code;
    int AT;
    int AF;
} AMK;
void print_AMK_table(int, AMK*);
int fill_amk_table(AMK**);
#endif // AMK_H_INCLUDED
