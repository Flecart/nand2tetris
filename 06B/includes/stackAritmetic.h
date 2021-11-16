#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aritTrans.h"
#include "utils.h"
typedef enum {
    PUSH,
    POP,
    ADD,
    SUB,
    NEG,
    EQ, 
    GT, 
    LT, 
    AND, 
    OR,
    NOT,
    ARITS_UNKNOWN
} Arits;

Arits getArits(char *word);

int aritmeticHandler(char *line, char *filename, FILE *writeToPtr);