#pragma once 
#include <stdio.h>

typedef enum {
    FUNCTION,
    RETURN,
    CALL,
    FUNC_UNKNOWN
} Funcs;
Funcs getFuncs(char *word);
int functions(char *line, FILE *writeToPtr);

// Precondition for every function here
// instr is a valid instr for that type
char *function(char *instr);
char *call(char *instr);
char *returnFunction();

// some utils
char *getCallLabel(char *funcName, int nparams);
char *pushAddress(char *addressName);
char *getGotoAddr(char *addressName);
char *assemblyRestore(char *regName, int offset);