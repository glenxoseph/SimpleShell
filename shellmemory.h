#ifndef SHELLMEMORY_H_
#define SHELLMEMORY_H_
#include "interpreter.h"
#include "shell.h"

typedef struct newNode {
    char * var;
    char * val;
} node;

int display(char * var);
int save(char * var, char * val);

#endif
