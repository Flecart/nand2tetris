#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aritTrans.h"
#include "utils.h"

int aritmeticHandler(char *line) {
    char *firstWord = getWord(line, 1);
    if (firstWord == NULL) {
        printf("Invalid read in instruction\n");
        return 1;
    }

    printf("the first word of -%s- is -%s-\n", line, firstWord);

    if (strcmp(firstWord, "push") == 0) {
        push(line);
    } else if (strcmp(firstWord, "pop") == 0) {
        
    } else if (strcmp(firstWord, "add") == 0) {

    } else if (strcmp(firstWord, "sub") == 0) {

    } else if (strcmp(firstWord, "neg") == 0) {
        
    } else if (strcmp(firstWord, "eg") == 0) {
        
    } else if (strcmp(firstWord, "gt") == 0) {
        
    } else if (strcmp(firstWord, "lt") == 0) {
        
    } else if (strcmp(firstWord, "and") == 0) {
        
    } else if (strcmp(firstWord, "or") == 0) {
        
    } else if (strcmp(firstWord, "not") == 0) {
        
    } else {
        printf("Instruction %s not valid\n", firstWord);
        return 1;
    }
    free(firstWord);
    return 0;
}

int main() {
    char *line = "push constant 1";
    aritmeticHandler(line);
}
