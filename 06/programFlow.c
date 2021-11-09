#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "programFlow.h"
#include "utils.h"

#ifndef MAX_SIZE
#define MAX_SIZE 500
#endif

Flows getFlows(char *word) {
    Flows flows = FLOWS_UNKNOWN;

    if (strcmp(word, "label") == 0) flows = LABEL;
    else if (strcmp(word, "if-goto") == 0) flows = IF_GOTO;
    else if (strcmp(word, "goto") == 0) flows = GOTO;
    return flows;
}

int programFlow(char *line, FILE *writeToPtr) {
    char *firstWord = getWord(line, 1);
    if (firstWord == NULL) {
        printf("Invalid read in instruction, CHECK PROGRAM FLOW.C\n");
        return 1;
    }
    char *asmCode = NULL;

    // printf("the first word of -%s- is -%s-\n", line, firstWord);
    Flows flows = getFlows(firstWord);
    switch(flows) {
        case LABEL:     asmCode = label(line);          break;
        case IF_GOTO:   asmCode = if_goto(line);        break;
        case GOTO:      asmCode = gotoCommand(line);    break;
        default:
            printf("Instruction %s not valid\n", firstWord);
            return 1;
    }
    if (asmCode == NULL) return 1;
    
    fprintf(writeToPtr, "%s", asmCode);
    free(asmCode);
    free(firstWord);
    return 0;
}

char *label(char *instr) {
    char *command = getWord(instr, 1);
    char *label = getWord(instr, 2);
    if (strcmp(command, "label") != 0 || label == NULL) return NULL;

    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = "(%s)\n";
    sprintf(formattedStr, format, label);

    free(command);
    free(label);
    return strInHeap(formattedStr);
}

char *if_goto(char *instr) {
    char *command = getWord(instr, 1);
    char *label = getWord(instr, 2);
    if (strcmp(command, "if-goto") != 0 || label == NULL) return NULL;

    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = ""
        "@SP\n"
        "M=M-1\n"
        "A=M\n"
        "D=M\n"
        "@%s\n"
        "D;JNE\n"; // NON SALTARE SE È UGUALE A 0
    sprintf(formattedStr, format, label);

    free(command);
    free(label);
    return strInHeap(formattedStr);
}

char *gotoCommand(char *instr) {
    char *command = getWord(instr, 1);
    char *label = getWord(instr, 2);
    if (strcmp(command, "goto") != 0 || label == NULL) return NULL;

    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = "@%s\n0;JMP\n";
    sprintf(formattedStr, format, label);

    free(command);
    free(label);
    return strInHeap(formattedStr);
}