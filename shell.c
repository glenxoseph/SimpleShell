#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "interpreter.h"
#include "shellmemory.h"
#include "shell.h"

// error code
// exceed memory: 20
// variable does not exist: 21
// no such file: 22
// invalid command: 23
// wrong arguments: 24
// exit: 25
// too many arguments: 26
// too few arguments: 27

int parse(char input[]) {
    char tmp[200];
    int a, b;
    char * words[100];
    a = 0;
    b = 0;
    for (; input[a] == ' ' && a < 1000; a++);

    int w = 0;

    while (input[a] != '\0' && input[a] != '\n' && input[a] != '\r' && a < 1000) {

        for (b = 0; (input[a] != '\r') && (input[a] != ' ') && (input[a] != '\0') && (input[a] != '\n') && (a < 1000); a++, b++) {
            tmp[b] = input[a];
        }

        tmp[b] = '\0';
        words[w] = strdup(tmp);

        a++;
        w++;
    }
    return interpreter(words, w);
}


int main() {
    printf("Welcome to the Glen Xu shell! \n");
    printf("Version 1.0 Created January 2020 \n");
    char prompt[100] = {'$', '\0'};
    char input[1000];
    int errorCode = 0;

    while (1) {
        printf("%s ", prompt);
        fgets(input, 999, stdin);
        errorCode = parse(input);

        bool exceedCon = (errorCode == 20);
        bool dNECon = (errorCode == 21);
        bool noFileCon = (errorCode == 22);
        bool invalidCon = (errorCode == 23);
        bool wrongArgCon = (errorCode == 24);
        bool exitCon = (errorCode == 25);
        bool tooManyArgCon = (errorCode == 26);
        bool tooFewArgCon = (errorCode == 27);

        if (exitCon == true) {
            exit(0);
            break;
        } else if (wrongArgCon == true) {
            printf("Wrong argument! \n");
        } else if (tooFewArgCon == true) {
            printf("Need more arguments! \n");
        } else if (tooManyArgCon == true) {
            printf("Too many arguments! \n");
        } else if (exceedCon == true) {
            printf("Not enough memory! \n");
        } else if (noFileCon == true) {
            printf("Script not found! \n");
        } else if (invalidCon == true) {
            printf("Unknown Command! \n");
        } else if (dNECon == true) {
            printf("Variable does not exist! \n");
        }
    }
}
