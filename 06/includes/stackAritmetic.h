#pragma once

typedef enum {
    PUSH,
    POP,
    ADD,
    SUB,
    NEG,
    EG, 
    GT, 
    LT, 
    AND, 
    OR,
    NOT,
    ARITS_UNKNOWN
} Arits;

Arits getArits(char *word);

int aritmeticHandler(char *line, char *filename, FILE *writeToPtr);