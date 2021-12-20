#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "programFlow.h"
#include "utils.h"

#include "functions.h" // G_scope
#ifndef MAX_SIZE
#define MAX_SIZE 1000
#endif

Flows getFlows(char *word) {
    Flows flows = FLOWS_UNKNOWN;

    if (strcmp(word, "label") == 0) flows = LABEL;
    else if (strcmp(word, "if-goto") == 0) flows = IF_GOTO;
    else if (strcmp(word, "goto") == 0) flows = GOTO;
    return flows;
}

int programFlow(char *line, char* filename, FILE *writeToPtr) {
    char *firstWord = getWord(line, 1);
    if (firstWord == NULL) {
        printf("Invalid read in instruction, CHECK PROGRAM FLOW.C\n");
        return 1;
    }
    char *asmCode = NULL;

    // printf("the first word of -%s- is -%s-\n", line, firstWord);
    Flows flows = getFlows(firstWord);
    switch(flows) {
        case LABEL:     asmCode = label(line, filename);          break;
        case IF_GOTO:   asmCode = if_goto(line, filename);        break;
        case GOTO:      asmCode = gotoCommand(line, filename);    break;
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

char *label(char *instr, char *filename) {
    char *command = getWord(instr, 1);
    char *label = getWord(instr, 2);
    char *G_scope = getScope();
    if (strcmp(command, "label") != 0 || label == NULL) {
        free(command);
        free(label);
        return NULL;
    }

    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = "(%s.%s_VMLABEL_%s)\n";
    sprintf(formattedStr, format, filename, G_scope, label);

    free(command);
    free(label);
    return strInHeap(formattedStr);
}

// 800 righe di pong
char *if_goto(char *instr, char *filename) {
    char *command = getWord(instr, 1);
    char *label = getWord(instr, 2);
    char *G_scope = getScope();
    if (strcmp(command, "if-goto") != 0 || label == NULL) {
        free(command);
        free(label);
        return NULL;
    }

    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = ""
        "@SP\n"
        "AM=M-1\n"
        "D=M\n"
        "@%s.%s_VMLABEL_%s\n"
        "D;JNE\n"; // NON SALTARE SE È UGUALE A 0
    sprintf(formattedStr, format, filename, G_scope, label);

    free(command);
    free(label);
    return strInHeap(formattedStr);
}

char *gotoCommand(char *instr, char *filename) {
    char *command = getWord(instr, 1);
    char *label = getWord(instr, 2);
    char *G_scope = getScope();
    if (strcmp(command, "goto") != 0 || label == NULL) {
        free(command);
        free(label);
        return NULL;
    }

    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = "@%s.%s_VMLABEL_%s\n0;JMP\n";
    sprintf(formattedStr, format, filename, G_scope, label);

    free(command);
    free(label);
    return strInHeap(formattedStr);
}