#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

#define MAX_SIZE 200

char *push(char *instr, char *fileName) {
    char *command = getWord(instr, 1);
    char *segment = getWord(instr, 2);
    char *strNumber = getWord(instr, 3);
    if (strcmp(command, "push") != 0 || segment == NULL || strNumber == NULL) return NULL;

    int number = strToInt(strNumber);
    char formattedStr[MAX_SIZE] = {'\0'};
    char *addToStack = ""
        "@SP\n"
        "A=M\n"
        "M=D\n"
        "@SP\n"
        "M=M+1\n";

    if (strcmp(segment, "constant") == 0){
        char *format = ""
            "@%d\n"
            "D=A\n"
            "%s";

        sprintf(formattedStr, format, number, addToStack, addToStack);
    } else if (strcmp(segment, "local") == 0) {
        char *format = ""
            "@LCL\n"
            "D=A\n"
            "@%d\n"
            "A=D+A\n"
            "D=M\n"
            "%s";

        sprintf(formattedStr, format, number, addToStack);
    } else if (strcmp(segment, "argument") == 0) {
        char *format = ""
            "@ARG\n"
            "D=A\n"
            "@%d\n"
            "A=D+A\n"
            "D=M\n"
            "%s";

        sprintf(formattedStr, format, number, addToStack);
    } else if (strcmp(segment, "static") == 0) {
        char *format = ""
            "@%s.%d\n"
            "D=M\n"
            "%s";

        sprintf(formattedStr, format, fileName, number, addToStack);
    } else {
        printf("Invalid segment %s\n", segment);
        return NULL;
    }


    free(command);
    free(segment);
    free(strNumber);

    int formattedLen = strlen(formattedStr);
    char *finalString = malloc(formattedLen + 1);
    strncpy(finalString, formattedStr, formattedLen);
    finalString[formattedLen] = '\0';
    return finalString;
}


char *pop(char *instr, char *fileName) {
    char *command = getWord(instr, 1);
    char *segment = getWord(instr, 2);
    char *strNumber = getWord(instr, 3);
    if (strcmp(command, "pop") != 0 || segment == NULL || strNumber == NULL) return NULL;
    int number = strToInt(strNumber);

    char formattedStr[MAX_SIZE] = {'\0'};
    // SET THE NEW STACK POINTER AND SAVE THE VALUE TOWRITE TO R13
    char *removeFromStack = ""
        "@SP\n"
        "M=M-1\n"
        "A=M\n"
        "D=M\n"
        "@R13\n"
        "M=D\n";

    // WRITES R13 TO THE ADDRESS OF R14
    char *writeSegment = ""
        "@R14\n"
        "M=D\n"
        "@R13\n"
        "D=M\n"
        "@R14\n"
        "A=M\n"
        "M=D\n";

    if (strcmp(segment, "local") == 0) {
        char *format = ""
            "%s"
            "@LCL\n"
            "D=A\n"
            "@%d\n"
            "D=D+A\n"
            "%s";

        sprintf(formattedStr, format, removeFromStack, number, writeSegment);
    } else if (strcmp(segment, "argument") == 0) {
        char *format = ""
            "%s"
            "@ARG\n"
            "D=A\n"
            "@%d\n"
            "D=D+A\n"
            "%s";

        sprintf(formattedStr, format, removeFromStack, number, writeSegment);
    } else if (strcmp(segment, "static") == 0) {
        char *format = ""
            "%s"
            "@%s.%d\n"
            "D=A\n"
            "%s";

        sprintf(formattedStr, format, removeFromStack, fileName, number, writeSegment);
    } else {
        printf("Invalid segment %s\n", segment);
        return NULL;
    }

    free(command);
    free(segment);
    free(strNumber);

    int formattedLen = strlen(formattedStr);
    char *finalString = malloc(formattedLen + 1);
    strncpy(finalString, formattedStr, formattedLen);
    finalString[formattedLen] = '\0';
    return finalString;
}