#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct err{
   int line;
   int column;
   char* text;
   char symb;
}error;

error push_error(int, int, char*, char);
void print_err(error, FILE*, char*);

#endif // ERROR_H_INCLUDED
