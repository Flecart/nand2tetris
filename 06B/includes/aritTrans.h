#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "globals.h"

#ifndef MAX_SIZE
#define MAX_SIZE 1000
#endif

char *push(char *instr, char *fileName);
char *pop(char *instr, char *fileName);

char *add(char *instr);
char *sub(char *instr);
char *neg(char *instr);
char *add(char *instr);
char *or(char *instr);
char *not(char *instr);
char *and(char *instr);
char *eq(char *instr);
char *lt(char *instr);
char *gt(char *instr);

// Used for optimization.
// Returns the offset instruction on the heap
char *offsetBuilder(char MorA, int number_offset);