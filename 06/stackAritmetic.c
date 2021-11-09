#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aritTrans.h"
#include "utils.h"

int aritmeticHandler(char *line, char *filename, FILE *writeToPtr) {
    char *firstWord = getWord(line, 1);
    if (firstWord == NULL) {
        printf("Invalid read in instruction\n");
        return 1;
    }

    // printf("the first word of -%s- is -%s-\n", line, firstWord);

    char *asmCode = NULL;
    // TODO: make enum and make this a switch
    if (strcmp(firstWord, "push") == 0) asmCode = push(line, filename);
    else if (strcmp(firstWord, "pop") == 0) asmCode = pop(line, filename);
    else if (strcmp(firstWord, "add") == 0) asmCode = add(line);
    else if (strcmp(firstWord, "sub") == 0) asmCode = sub(line);
    else if (strcmp(firstWord, "neg") == 0) asmCode = neg(line);
    else if (strcmp(firstWord, "eg") == 0) asmCode = eg(line);
    else if (strcmp(firstWord, "gt") == 0) asmCode = gt(line);
    else if (strcmp(firstWord, "lt") == 0) asmCode = lt(line);
    else if (strcmp(firstWord, "and") == 0) asmCode = and(line);
    else if (strcmp(firstWord, "or") == 0) asmCode = or(line);
    else if (strcmp(firstWord, "not") == 0) asmCode = not(line);
    else {
        printf("Instruction %s not valid\n", firstWord);
        return 1;
    }
    if (asmCode == NULL) return 1;
    
    fprintf(writeToPtr, "%s", asmCode);
    free(asmCode);
    free(firstWord);
    return 0;
}

// void test_pop() {
//     char *line = "pop static 1";
//     aritmeticHandler(line, "hello");
// }

// void test_eg() {
//     char *line = "eg";
//     aritmeticHandler(line, "hello");
// }

// void test_add() {
//     char *line = "add";
//     aritmeticHandler(line, "hello");

// }

// int main_stackAritmetic() {
//     test_eg();
//     printf("\n");
//     test_add();
//     printf("\n");
//     test_eg();
//     printf("\n");
//     return 0;
// }
