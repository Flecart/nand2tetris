#pragma once
#define bool short
// returns 1 if not valid, else 0;
int isValidArg(int argc);

char* getLine(FILE *filePointer, int strLen);
char *getFileName(char *filename);

int compile(FILE *readFilePointer, FILE *writeFilePointer, bool isPreprocessing);
int preprocessLine(char *line, int *codeLineNumber);
int compileLine(char *line, int *codeLineNumber);
int processLine(char *line, int *codeLineNumber, bool isPreprocessing);

void initGlobals();
void initRegisters();
void clearGlobals();

