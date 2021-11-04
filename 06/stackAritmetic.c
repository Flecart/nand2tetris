#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aritTrans.h"
#include "utils.h"

void nullf(char *line, char *filananme() {};

int aritmeticHandler(char *line, char *filename) {
    char *firstWord = getWord(line, 1);
    if (firstWord == NULL) {
        printf("Invalid read in instruction\n");
        return 1;
    }

    printf("the first word of -%s- is -%s-\n", line, firstWord);

    if (strcmp(firstWord, "push") == 0) {
        char *asmCode = push(line, filename);
        printf("%s\n", asmCode);
        free(asmCode);
    } else if (strcmp(firstWord, "pop") == 0) {
        char *asmCode = pop(line, filename);
        printf("%s\n", asmCode);
        free(asmCode);
    } else if (strcmp(firstWord, "add") == 0) {
        char *asmCode = add(line, filename);
        printf("%s\n", asmCode);
        free(asmCode);
    } else if (strcmp(firstWord, "sub") == 0) {
        char *asmCode = nullf(line, filename);
        printf("%s\n", asmCode);
        free(asmCode);
    } else if (strcmp(firstWord, "neg") == 0) {
        char *asmCode = nullf(line, filename);
        printf("%s\n", asmCode);
        free(asmCode);
    } else if (strcmp(firstWord, "eg") == 0) {
        char *asmCode = nullf(line, filename);
        printf("%s\n", asmCode);
        free(asmCode);
    } else if (strcmp(firstWord, "gt") == 0) {
        char *asmCode = nullf(line, filename);
        printf("%s\n", asmCode);
        free(asmCode);
    } else if (strcmp(firstWord, "lt") == 0) {
        char *asmCode = nullf(line, filename);
        printf("%s\n", asmCode);
        free(asmCode);
    } else if (strcmp(firstWord, "and") == 0) {
        char *asmCode = nullf(line, filename);
        printf("%s\n", asmCode);
        free(asmCode);
    } else if (strcmp(firstWord, "or") == 0) {
        char *asmCode = nullf(line, filename);
        printf("%s\n", asmCode);
        free(asmCode);
    } else if (strcmp(firstWord, "not") == 0) {
        char *asmCode = nullf(line, filename);
        printf("%s\n", asmCode);
        free(asmCode);
    } else {
        printf("Instruction %s not valid\n", firstWord);
        return 1;
    }
    free(firstWord);
    return 0;
}

int main() {
    
    char *line = "pop static 1";
    aritmeticHandler(line, "hello");
}
