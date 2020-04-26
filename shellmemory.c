#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "shellmemory.h"

static struct newNode shellMemory[1000] = {0};
static int size = 0;

int display(char * var) {
    int index = 0;
    while (index < size) {
        int cmp = strcmp(shellMemory[index].var, var);
        bool identical = (cmp == 0);
        if (identical) {
            printf("%s\n", strdup(shellMemory[index].val));
            return 0;
        }
        index = index + 1;
    }
    return 21;
}

int save(char * var, char * val) {
    if (size > 1000) { // exceed
        return 20;
    }
    int index = 0;
    while (index < size) {
        int cmp = strcmp(shellMemory[index].var, var);
        bool identical = (cmp == 0);
        if (identical) {
            shellMemory[index].val = strdup(val);
            return 0;
        }
        index = index + 1;
    }
    struct newNode node = {node.var = var, node.val = val};
    shellMemory[size] = node;
    size = size + 1;
    return 0;
}
