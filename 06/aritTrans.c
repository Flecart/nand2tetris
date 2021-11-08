// NOTA SULLE FUNZIONI COMP, BIT A BIT
// Tutte le traduzioni delle funzioni contengono molte cose riptetute
// Nella maggior parte cambiano solamente una parola o un segno
// Potresti creare una funzione che cambi questo segno o parola a seconda dell'input
// Dovresti aggiungere altri parametri al printf
// Per lo scope di questo progetto è più semplice tenere traduzioni separate
// Ma fai attenzione allo

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

#define MAX_SIZE 500

// comparison counter: global that counts the 
// eq, lt, gt operations, useful for labels
int COMP_CTR = 0;

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
    char *finalString = malloc((formattedLen + 1) * sizeof(char));
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
    char *finalString = malloc((formattedLen + 1) * sizeof(char));
    strncpy(finalString, formattedStr, formattedLen);
    finalString[formattedLen] = '\0';
    return finalString;
}

char *add(char *instr) {
    char *command = getWord(instr, 1);
    if (strcmp(command, "add") != 0) return NULL;

    char instruction[] = ""
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n" // D= *SP
        "D=M\n"
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n" // D += *SP
        "D=D+M\n"
        "M=D\n" // *SP = D
        "@SP\n" //SP += 1
        "M=M+1\n";

    int len = strlen(instruction);
    char *returnString = malloc((len + 1) * sizeof(char));
    if (returnString == NULL) return NULL;


    strncpy(returnString, instruction, len);
    returnString[len] = '\0';
    return returnString;
}

char *sub(char *instr) {
    char *command = getWord(instr, 1);
    if (strcmp(command, "sub") != 0) return NULL;

    char instruction[] = ""
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n" // D= *SP
        "D=M\n"
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n" // D -= *SP
        "D=D-M\n"
        "M=D\n" // *SP = D
        "@SP\n" //SP += 1
        "M=M+1\n";

    int len = strlen(instruction);
    char *returnString = malloc((len + 1) * sizeof(char));
    if (returnString == NULL) return NULL;

    strncpy(returnString, instruction, len);
    returnString[len] = '\0';
    return returnString;
}

char *neg(char *instr) {
    char *command = getWord(instr, 1);
    if (strcmp(command, "neg") != 0) return NULL;

    char instruction[] = ""
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n" // D= *SP
        "M=-M\n" // *SP = -*SP
        "@SP\n" //SP += 1
        "M=M+1\n";

    int len = strlen(instruction);
    char *returnString = malloc((len + 1) * sizeof(char));
    if (returnString == NULL) return NULL;


    strncpy(returnString, instruction, len);
    returnString[len] = '\0';
    return returnString;
}

// correggi le istruzioni
char *eg(char *instr) {
    char *command = getWord(instr, 1);
    if (strcmp(command, "eg") != 0) return NULL;
    char formattedStr[MAX_SIZE] = {'\0'};

    char format[] = ""
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n" // D= *SP
        "D=M\n"
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n" // D -= *SP
        "D=D-M\n"
        "@COMP_%d\n"
        "D;JNE\n"
        "" // (EQ_%d,\n ma non lo metto perché inutile)
        "@SP\n"
        "M=1\n" // *SP = 1
        "@ENDCOMP_%d\n"
        "0;JMP"
        "(COMP_%d)\n" // NOTEQ
        "@SP\n"
        "M=0\n" // *SP = 0
        "(ENDCOMP_%d)\n"
        "@SP\n" //SP += 1
        "M=M+1\n";

    sprintf(formattedStr, format, COMP_CTR, COMP_CTR, COMP_CTR, COMP_CTR);
    COMP_CTR += 1;

    int len = strlen(formattedStr);
    char *returnString = malloc((len + 1) * sizeof(char));
    if (returnString == NULL) return NULL;


    strncpy(returnString, formattedStr, len);
    returnString[len] = '\0';
    return returnString;
}

char *gt(char *instr) {
    char *command = getWord(instr, 1);
    if (strcmp(command, "gt") != 0) return NULL;

    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = ""
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n" // D= *SP
        "D=M\n"
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n" // D -= *SP
        "D=D-M\n"
        "@COMP_%d\n"
        "D;JLE\n"
        "" // (GT%d,\n ma non lo metto perché inutile)
        "@SP\n"
        "M=1\n" // *SP = 1
        "@ENDCOMP_%d\n"
        "0;JMP"
        "(COMP_%d)\n" // NOTJGT = JLE
        "@SP\n"
        "M=0\n" // *SP = 0
        "(ENDCOMP_%d)\n"
        "@SP\n" //SP += 1
        "M=M+1\n";

    sprintf(formattedStr, format, COMP_CTR, COMP_CTR, COMP_CTR, COMP_CTR);
    COMP_CTR += 1;

    int len = strlen(formattedStr);
    char *returnString = malloc((len + 1) * sizeof(char));
    if (returnString == NULL) return NULL;


    strncpy(returnString, formattedStr, len);
    returnString[len] = '\0';
    return returnString;
}

char *lt(char *instr) {
    char *command = getWord(instr, 1);
    if (strcmp(command, "lt") != 0) return NULL;

    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = ""
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n" // D= *SP
        "D=M\n"
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n" // D -= *SP
        "D=D-M\n"
        "@COMP_%d\n"
        "D;JGE\n"
        "" // (LT_%d,\n ma non lo metto perché inutile)
        "@SP\n"
        "M=1\n" // *SP = 1
        "@ENDCOMP_%d\n"
        "0;JMP"
        "(COMP_%d)\n" // NOTLT = JGE
        "@SP\n"
        "M=0\n" // *SP = 0
        "(ENDCOMP_%d)\n"
        "@SP\n" //SP += 1
        "M=M+1\n";

    sprintf(formattedStr, format, COMP_CTR, COMP_CTR, COMP_CTR, COMP_CTR);
    COMP_CTR += 1;

    int len = strlen(formattedStr);
    char *returnString = malloc((len + 1) * sizeof(char));
    if (returnString == NULL) return NULL;


    strncpy(returnString, formattedStr, len);
    returnString[len] = '\0';
    return returnString;
}

char *and(char *instr) {
    char *command = getWord(instr, 1);
    if (strcmp(command, "and") != 0) return NULL;

    char instruction[] = ""
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n" // D= *SP
        "D=M\n"
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n" // D = D & *SP
        "D=D&M\n"
        "M=D\n" // *SP = D
        "@SP\n" //SP += 1
        "M=M+1\n";

    int len = strlen(instruction);
    char *returnString = malloc((len + 1) * sizeof(char));
    if (returnString == NULL) return NULL;


    strncpy(returnString, instruction, len);
    returnString[len] = '\0';
    return returnString;
}


char *or(char *instr) {
    char *command = getWord(instr, 1);
    if (strcmp(command, "or") != 0) return NULL;

    char instruction[] = ""
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n" // D = *SP
        "D=M\n"
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n" // D = D | *SP
        "D=D|M\n"
        "M=D\n" // *SP = D
        "@SP\n" //SP += 1
        "M=M+1\n";

    int len = strlen(instruction);
    char *returnString = malloc((len + 1) * sizeof(char));
    if (returnString == NULL) return NULL;


    strncpy(returnString, instruction, len);
    returnString[len] = '\0';
    return returnString;
}

char *not(char *instr) {
    char *command = getWord(instr, 1);
    if (strcmp(command, "not") != 0) return NULL;

    char instruction[] = ""
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n"
        "M=!M\n" // *SP = *SP
        "@SP\n" //SP += 1
        "M=M+1\n";

    int len = strlen(instruction);
    char *returnString = malloc((len + 1) * sizeof(char));
    if (returnString == NULL) return NULL;


    strncpy(returnString, instruction, len);
    returnString[len] = '\0';
    return returnString;
}