#pragma once 
#include <stdio.h>

#define DEFAULT_SCOPE "DEFAULT_SCOPE"
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
char *pushAddress(char *addressName, char mOrA);
char *getGotoAddr(char *addressName);
char *assemblyRestore(char *regName, int offset);
void free_global_fun_cache();

// Allows other programs to access the current scope
// Freed is not needed in the calling program, it's handled by this module
char *getScope();