#pragma once
#include <stdio.h>

#define bool short

void compile(FILE *readFilePointer, FILE *writeFilePointer, bool isPreprocessing);
int preprocessLine(char *line, int *codeLineNumber);
int compileLine(char *line, int *codeLineNumber);
int processLine(char *line, int *codeLineNumber, bool isPreprocessing);

void initGlobals();
void initRegisters();
void clearGlobals();
