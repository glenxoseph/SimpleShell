#ifndef INTERPRETER_H_
#define INTERPRETER_H_
#include "shellmemory.h"
#include "shell.h"

int interpreter(char * words[], int length);
int set(char * words[]);
int print(char * words[]);
int run(char * word);
int help();
int quit();

#endif
