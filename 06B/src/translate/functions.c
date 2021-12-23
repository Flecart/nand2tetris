#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "utils.h"

#include "aritTrans.h"
#include "cacheFunc.h"

#ifndef MAX_SIZE
#define MAX_SIZE 1000
#endif

// THIS GLOBAL COUNTS HOW MANY TIMES I'M CALLING A FUNC
// I USE THIS TO SET FUNC LABELS
int G_call_counter = 0;

// This global tries to optimize the function call
Cache G_cache = NULL;

// This global is used in program flow to take into account the scope of the single label
char *G_scope = DEFAULT_SCOPE;

Funcs getFuncs(char *word) {
    Funcs funcs = FUNC_UNKNOWN;

    if (strcmp(word, "function") == 0) funcs = FUNCTION;
    else if (strcmp(word, "call") == 0) funcs = CALL;
    else if (strcmp(word, "return") == 0) funcs = RETURN;
    return funcs;
}

char *getScope() {
    return G_scope;
}

void free_global_fun_cache() {
    freeCache(G_cache);
    G_cache = NULL;
}

int functions(char *line, FILE *writeToPtr) {
    char *firstWord = getWord(line, 1);
    if (firstWord == NULL) {
        printf("Invalid read in instruction, CHECK functions.C\n");
        return 1;
    }
    char *asmCode = NULL;

    Funcs funcs = getFuncs(firstWord);
    switch(funcs) {
        case FUNCTION:    asmCode = function(line);         break;
        case CALL:        asmCode = call(line);             break;
        case RETURN:      asmCode = returnFunction();       break;
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

// 2k righe
char *function(char *instr) {
    char *funcName = getWord(instr, 2);
    char *funcParams = getWord(instr, 3);
    int funcParamsNum = strToInt(funcParams);

    char formattedStr[MAX_SIZE] = {'\0'};
    char moveSP[MAX_SIZE] = {'\0'};
    // Optimize the instructions for moving the SP
    // TODO: se hai bisogno di altro spazio ancora
    // Puoi fare il caso in cui il n di argomenti è 0
    // Allora puoi proprio non far niente per moveSP
    if (funcParamsNum == 1) {
        strcpy(moveSP, ""
            "@SP\n"
            "M=M+1\n"
            "A=M-1\n");
    } else {
        char small_format[] = ""
            "@%d\n"
            "D=A\n"
            "@SP\n"
            "M=M+D\n"
            "A=M-D\n";
        sprintf(moveSP, small_format, funcParamsNum);
    }

    for (int i = 0; i < funcParamsNum; i++) {
        strcat(moveSP, ""
            "M=0; // setting value of function\n"
            "A=A+1\n");
    }
    char format[] = ""
        "(%s)\n"
        "%s";

    sprintf(formattedStr, format, funcName, moveSP);

    // Set scope of the function with his name:
    // This variable is freed when returning the function
    G_scope = funcName;
    free(funcParams);
    return strInHeap(formattedStr);
}

// Le call prendono circa 6k righe di pong
char *call(char *instr) {
    char *funcName = getWord(instr, 2);
    char *funcParams = getWord(instr, 3);
    int funcParamsNum = strToInt(funcParams);
    char *callLabel = getCallLabel(funcName, G_call_counter);
    G_call_counter += 1;
    char formattedStr[MAX_SIZE] = {'\0'};
    char *pushRet = pushAddress(callLabel, 'A');
    
    // Attempt to cache (the values from 0-6 seems frequent) 
    if (funcParamsNum <= FUNCTION_RANGE) {
        G_cache = updateCache(G_cache, funcName, funcParamsNum);
        char format[] = ""
            "%s" // push ret_addr
            "(%s__%d)  // begin hardcoded f call\n"
            "@%s\n" //GOTO, coded before
            "D=A\n"
            "@R13\n"
            "M=D\n"
            "@"FUNCTION_CALL"$%d\n"
            "0;JMP\n"
            "(%s)\n"; // ret_addr
        sprintf(formattedStr, format, pushRet, funcName, funcParamsNum, funcName, funcParamsNum, callLabel);
    } else if (searchCache(G_cache, funcName, funcParamsNum) == NULL) {
        G_cache = updateCache(G_cache, funcName, funcParamsNum);
        char *pushLCL = pushAddress("LCL", 'M');
        char *pushARG = pushAddress("ARG", 'M');
        char *pushTHIS = pushAddress("THIS", 'M');
        char *pushTHAT = pushAddress("THAT", 'M');

        char format[] = ""
            "%s" // push ret_addr
            "(%s__%d)  // begin function call\n"
            "%s" // push LCL
            "%s" // push arg
            "%s" // push this
            "%s" // push that
            "@SP\n"
            "D=M\n"
            "@LCL\n"
            "M=D\n"
            "@%d\n" // D = SP - N - 5
            "D=D-A\n"
            "@ARG\n"
            "M=D\n"
            "@%s\n" //GOTO
            "0;JMP\n"
            "(%s)\n"; // ret_addr
        sprintf(formattedStr, format, pushRet, funcName, funcParamsNum, pushLCL, pushARG, pushTHIS, pushTHAT, funcParamsNum + 5, funcName, callLabel);
        free(pushLCL);
        free(pushARG);
        free(pushTHIS);
        free(pushTHAT);
    } else {
        char format[] = ""
            "%s" // push ret_addr
            "@%s__%d\n"
            "0;JMP\n"
            "(%s)\n"; // ret_addr
        sprintf(formattedStr, format, pushRet, funcName, funcParamsNum, callLabel);
    }

    free(pushRet);
    free(funcName);
    free(funcParams);
    free(callLabel);
    return strInHeap(formattedStr);
}

char *getCallLabel(char *funcName, int counter) {
    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = "CALL_%s$%d";
    sprintf(formattedStr, format, funcName, counter);
    return strInHeap(formattedStr);
}

char *pushAddress(char *addressName, char mOrA) {
    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = ""
        "@%s\n"
        "D=%c\n"
        "@SP\n"
        "M=M+1\n"
        "A=M-1\n"
        "M=D\n";

    sprintf(formattedStr, format, addressName, mOrA);
    return strInHeap(formattedStr);
}

char *returnFunction() {
    char formattedStr[] = ""
        "@"RETURN_FUNCTION" // RETURN\n"
        "0;JMP\n";

    if (strcmp(G_scope, DEFAULT_SCOPE) != 0) {
        free(G_scope);
    }
    G_scope = DEFAULT_SCOPE;
    return strInHeap(formattedStr);
}