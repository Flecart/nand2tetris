#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stackAritmetic.h"
#include "aritTrans.h"
#include "utils.h"

Arits getArits(char *word) {
    Arits arits = ARITS_UNKNOWN;
    
    if (strcmp(word, "push") == 0) arits = PUSH;
    else if (strcmp(word, "pop") == 0) arits = POP;
    else if (strcmp(word, "add") == 0) arits = ADD;
    else if (strcmp(word, "sub") == 0) arits = SUB;
    else if (strcmp(word, "neg") == 0) arits = NEG;
    else if (strcmp(word, "eq") == 0) arits = EQ;
    else if (strcmp(word, "gt") == 0) arits = GT;
    else if (strcmp(word, "lt") == 0) arits = LT;
    else if (strcmp(word, "and") == 0) arits = AND;
    else if (strcmp(word, "or") == 0) arits = OR;
    else if (strcmp(word, "not") == 0) arits = NOT;
    return arits;
}

int aritmeticHandler(char *line, char *filename, FILE *writeToPtr) {
    char *firstWord = getWord(line, 1);
    if (firstWord == NULL) {
        printf("Invalid read in instruction\n");
        free(firstWord);
        return 1;
    }
    char *asmCode = NULL;

    // printf("the first word of -%s- is -%s-\n", line, firstWord);
    Arits arits = getArits(firstWord);
    switch(arits) {
        case PUSH:  asmCode = push(line, filename); break;
        case POP:   asmCode = pop(line, filename);  break;
        case ADD:   asmCode = add(line);            break;
        case SUB:   asmCode = sub(line);            break;
        case NEG:   asmCode = neg(line);            break;
        case EQ:    asmCode = eq(line);             break;
        case GT:    asmCode = gt(line);             break;
        case LT:    asmCode = lt(line);             break;
        case AND:   asmCode = and(line);            break;
        case OR:    asmCode = or(line);             break;
        case NOT:   asmCode = not(line);            break;
        default:
            printf("Instruction %s not valid\n", firstWord);
            free(firstWord);
            return 1;
    }
    if (asmCode == NULL) {
        free(firstWord);
        return 1;
    }
    
    fprintf(writeToPtr, "%s", asmCode);
    free(asmCode);
    free(firstWord);
    return 0;
}
