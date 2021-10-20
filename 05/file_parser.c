#include <stdio.h>
#include <stdlib.h>
#include "a_instruction.h"
#include "utils.h"
#include "file_parser.h"

#define false 0
#define true 1
#define bool short

int isValidArg(int argc) {
    if (argc != 2) {
        printf("Error in command\n");
        printf("[Usage]\n");
        printf("./assembler [filename]\n");
        return 1;
    }
    return 0;
}

char* getLine(FILE *filePointer, int strLen) {
    char *currLine = malloc(strLen + 1);
    char ch;

    // Copying filepointer so that i can get currLine to heap
    fseek(filePointer, -(strLen + 1), SEEK_CUR); // tiro indietro di + 1
    int comment = 0, endLineIndex;
    bool isComment = false;
    int i = 0;
    while ( (ch = fgetc(filePointer)) != '\n') {
        currLine[i] = ch;
        i += 1;
        
        // Se ci sono due  // di seguito ignora la riga
        if (ch == '/') comment += 1;
        else comment = 0;

        if (comment == 2) {
            isComment = true; // metto endline dopo prima / dei due
            endLineIndex = i - 2;
        }
    }

    // se non ho mai settato endLineIndex la metto per essere la fine. 
    if (!isComment) endLineIndex = i;
    currLine[endLineIndex] = '\0';

    return currLine;
}

// TODO: you have to add these line parsers into assembler.c
// // TODO: make line struct to pass fewer parameters and better code.
// int processLine(Map *map, char *line, int *codeLineNumber, bool isPreprocessing) {
//     line = strip(line);
//     if (isPreprocessing) return preprocessLine(map, line, codeLineNumber);
//     else return compileLine(map, line, codeLineNumber);
// }

// int compileLine(Map *map, char *line, int *codeLineNumber) {
//     bool isValidInstruction = true;
//     bool hasError = false;
//     if (line[0] == '@') {
//         aInstruction(line + 1, map);
//     } else if (line[1] == '=' || line[1] == ';'){
//         cInstruction(line);
//     } else if (line[0] == '\0' || line[0] == '(') {
//         isValidInstruction = false;
//     } else  {
//         printf("Istruzione invalida alla riga codice %d\n", *codeLineNumber);
//         printf("Valore primo carattere: %d\n", line[0]);
//         hasError = true;
//     }

//     if (isValidInstruction) *codeLineNumber += 1;

//     if (hasError) return 1;
//     else return 0;
// }

// int preprocessLine(Map *map, char *line, int *codeLineNumber) {
//     bool isValidInstruction = true;
//     int labelHasError = 0;

//     // \0 parses comment and empty lines
//     if (line[0] == '\0') {
//         isValidInstruction = false;
//     } else if (line[0] == '(') {
//         labelHasError = setLabels(map, line, *codeLineNumber);
//         isValidInstruction = false;
//     }

//     if (isValidInstruction) *codeLineNumber += 1;

//     if (labelHasError) return 1;
//     else return 0;
// }

// int preprocess(Map *map, char *filename) {

// }