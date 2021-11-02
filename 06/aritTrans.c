#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

char *getSegment(char *instr) {
    char *segment = getWord(instr, 2);
    if (segment == NULL) return NULL;

    char *segmentToReturn;
    if (strcmp(segment, "constant") == 0){
        segmentToReturn = "SP";
    } else if (strcmp(segment, "local") == 0) {
        segmentToReturn = "LCL";
    } else if (strcmp(segment, "argument") == 0) {
        segmentToReturn = "ARG";
    }
}

int push(char *instr) {
    char *command = getWord(instr, 1);
    char *segment = getWord(instr, 2);
    char *strNumber = getWord(instr, 3);
    if (strcmp(command, "push") != 0 || segment == NULL || strNumber == NULL) return NULL;

    int number = strToInt(strNumber);
    // BAD FORMAT, try to repeat less.
    if (strcmp(segment, "constant") == 0){
        char *format = ""
            "@%d\n"
            "D=A\n"
            "@SP\n"
            "A=M\n"
            "M=D\n"
            "@SP\n"
            "M=M+1\n";
        printf(format, number);
    } else if (strcmp(segment, "local") == 0) {
        char *format = ""
            "@LCL\n"
            "D=A\n"
            "@%d\n"
            "A=D+A\n"
            "D=M\n"
            "@SP\n"
            "A=M\n"
            "M=D\n"
            "@SP\n"
            "M=M+1\n";
        printf(format, number);
    } else if (strcmp(segment, "argument") == 0) {
        char *format = ""
            "@ARG\n"
            "D=A\n"
            "@%d\n"
            "A=D+A\n"
            "D=M\n"
            "@SP\n"
            "A=M\n"
            "M=D\n"
            "@SP\n"
            "M=M+1\n";
        printf(format, number);
    } else if (strcmp(segment, "static") == 0) {
        // bo
    } else {
        printf("Invalid segment %s\n", segment);
        return 1;
    }


    free(command);
    free(segment);
    free(strNumber);
    return 0;
}
