#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "utils.h"

#include "aritTrans.h"
#include "programFlow.h"

#ifndef MAX_SIZE
#define MAX_SIZE 1000
#endif

// THIS GLOBAL COUNTS HOW MANY TIMES I'M CALLING A FUNC
// I USE THIS TO SET FUNC LABELS
int CALL_COUNTER = 0;

Funcs getFuncs(char *word) {
    Funcs funcs = FUNC_UNKNOWN;

    if (strcmp(word, "function") == 0) funcs = FUNCTION;
    else if (strcmp(word, "call") == 0) funcs = CALL;
    else if (strcmp(word, "return") == 0) funcs = RETURN;
    return funcs;
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

char *function(char *instr) {
    char *funcName = getWord(instr, 2);
    char *funcParams = getWord(instr, 3);
    char *pushZero = push("push constant 0", "");
    int funcParamsNum = atoi(funcParams);

    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = ""
        "(%s)\n"
        "@%d\n"     // R13 = K (n parametri)
        "D=A\n"
        "@R13\n"    
        "M=D\n"
        "(%s.%d)\n"
        "@R13\n"    // JUMP TO END IF R13 == 0
        "D=M\n"
        "@VARIABLES_%s.%d\n"
        "D;JEQ\n"
        "%s"      // PUSH CONSTANT 0
        "@R13\n" // R13 --
        "M=M-1\n"
        "(VARIABLES_%s.%d)\n";

    // che brutta cosa....
    sprintf(formattedStr, format, funcName, funcParamsNum, funcName, funcParamsNum, funcName, funcParamsNum, pushZero, funcName, funcParamsNum);

    free(funcName);
    free(funcParams);
    free(pushZero);
    return strInHeap(formattedStr);
}

char *call(char *instr) {
    char *funcName = getWord(instr, 2);
    char *funcParams = getWord(instr, 3);
    int funcParamsNum = atoi(funcParams);
    char *callLabel = getCallLabel(funcName, CALL_COUNTER);
    CALL_COUNTER += 1;
    char *gotoFunc = getGotoAddr(funcName);

    char *pushRet = pushAddress(callLabel, 'A');
    char *pushLCL = pushAddress("LCL", 'M');
    char *pushARG = pushAddress("ARG", 'M');
    char *pushTHIS = pushAddress("THIS", 'M');
    char *pushTHAT = pushAddress("THAT", 'M');

    char *gotoString = gotoCommand(gotoFunc);
    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = ""
        "%s"
        "%s"
        "%s"
        "%s"
        "%s"
        "@SP\n"
        "D=M\n"
        "@LCL\n"
        "M=D\n"
        "@%d\n" // D = SP - N - 5
        "D=D-A\n"
        "@ARG\n"
        "M=D\n"
        "%s"  //GOTO
        "(%s)\n"; // LABEL
    sprintf(formattedStr, format, pushRet, pushLCL, pushARG, pushTHIS, pushTHAT, funcParamsNum + 5, gotoString, callLabel);

    free(funcName);
    free(funcParams);
    free(callLabel);
    free(gotoFunc);
    free(pushRet);
    free(pushLCL);
    free(pushARG);
    free(pushTHIS);
    free(pushTHAT);
    free(gotoString);
    return strInHeap(formattedStr);
}

char *getCallLabel(char *funcName, int counter) {
    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = "CALL_%s.%d";
    sprintf(formattedStr, format, funcName, counter);
    return strInHeap(formattedStr);
}

char *pushAddress(char *addressName, char mOrA) {
    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = ""
        "@%s\n"
        "D=%c\n"
        "@SP\n"
        "A=M\n"
        "M=D\n"
        "@SP\n"
        "M=M+1\n";

    sprintf(formattedStr, format, addressName, mOrA);
    return strInHeap(formattedStr);
}

char *getGotoAddr(char *addressName) {
    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = "goto %s";
    sprintf(formattedStr, format, addressName);
    return strInHeap(formattedStr);
}

char *returnFunction() {
    char *assingRet = assemblyRestore("R14", 5);
    char *restoreTHAT =  assemblyRestore("THAT", 1);
    char *restoreTHIS =  assemblyRestore("THIS", 2);
    char *restoreARG =  assemblyRestore("ARG", 3);
    char *restoreLCL =  assemblyRestore("LCL", 4);

    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = ""
        "@LCL\n" // FRAME = LCL
        "D=M\n"
        "@R13\n"
        "M=D\n"
        "%s"    //  RET = *(FRAME -5)
        "@SP\n"  // D = POP()
        "M=M-1\n"
        "A=M\n"
        "D=M\n"
        "@ARG\n" // *ARG = D
        "A=M\n"
        "M=D\n"
        "@ARG\n" // SP=ARG+1
        "D=M+1\n"
        "@SP\n"
        "M=D\n"
        "%s"    // THAT = *(FRAME - 1)
        "%s"    // THIS = *(FRAME - 2)
        "%s"    // ARG  = *(FRAME - 3)
        "%s"    // LCL  = *(FRAME - 4)
        "@R14\n" // GOTO RET
        "A=M\n"
        "0;JMP\n";

    sprintf(formattedStr, format, assingRet, restoreTHAT, restoreTHIS, restoreARG, restoreLCL);
    
    free(assingRet);
    free(restoreTHAT);
    free(restoreTHIS);
    free(restoreARG);
    free(restoreLCL);

    return strInHeap(formattedStr);
}

char *assemblyRestore(char *regName, int offset) {
    // THIS FUNC DOES regName = *(frame - offset); in ass
    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = ""
        "@R13\n" // D=*(FRAME - OFFSET)
        "D=M\n"
        "@%d\n"
        "D=D-A\n"
        "A=D\n"
        "D=M\n"
        "@%s\n" // REGNAME = D
        "M=D\n";

    sprintf(formattedStr, format, offset, regName);
    return strInHeap(formattedStr);
}
