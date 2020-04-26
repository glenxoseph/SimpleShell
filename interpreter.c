#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "interpreter.h"

int help() {
    printf("COMMAND             DESCRIPTION \
            \nhelp                Displays all the commands \
            \nquit                Exits / terminates the shell with “Bye!”\
            \nset <VAR> <STRING>  Assigns a value to shell memory\
            \nprint <VAR>         Prints the STRING assigned to VAR \
            \nrun SCRIPT.TXT      Executes the file SCRIPT.TXT \n");
    return 0;
}

int quit() {
    printf("Bye!\n");
    return 25;
}

int set(char * words[]) {
    char * var = words[1];
    char * val = words[2];
    int errorCode = save(var, val);
    bool exceed = (errorCode == 20);
    if (exceed == false) {
        printf("%s: %s \n", var, val);
    }
    return errorCode;
}

int print(char * words[]) {
    return display(words[1]);
}

int run(char * word) {
    char * name = word;
    int errorCode;
    FILE *file = fopen(name, "r");
    bool noFile = (file == NULL);
    if (noFile == true) {
        return 22;
    }
    char input[1000];

    while (fgets(input, 999, file)) {
        int errorCode = parse(input);
        bool quit = (errorCode == 25);
        if (quit == true) {
            exit(0);
        }
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
    fclose(file);
    return 0;
}

int interpreter(char * words[], int length) {

    bool helpCon = (strcmp(words[0], "help") == 0);
    bool quitCon = (strcmp(words[0], "quit") == 0);
    bool setCon = (strcmp(words[0], "set") == 0);
    bool printCon = (strcmp(words[0], "print") == 0);
    bool runCon = (strcmp(words[0], "run") == 0);
    bool wrongLength = (length != 1);

    int errorCode;

    if (helpCon == true) {
        if (wrongLength == true) {
            return 24;
        }
        errorCode = help();
    }
    else if (quitCon == true) {
        if (wrongLength == true) {
            return 24;
        }
        errorCode = quit();
    }
    else if (setCon == true) {
        bool smallArg = (length < 3);
        bool largeArg = (length > 3);
        if (smallArg == true) {
            return 27;
        } else if (largeArg == true) {
            return 26;
        }
        errorCode = set(words);
    }
    else if (printCon == true) {
        bool smallArg = (length < 2);
        bool largeArg = (length > 2);
        if (smallArg == true) {
            return 27;
        } else if (largeArg == true) {
            return 26;
        }
        errorCode = print(words);
    }
    else if (runCon == true) {
        bool smallArg = (length < 2);
        bool largeArg = (length > 2);
        if (smallArg == true) {
            return 27;
        } else if (largeArg == true) {
            return 26;
        }
        errorCode = run(words[1]);
    }
    else {
        errorCode = 23;
    }

    return errorCode;
}
