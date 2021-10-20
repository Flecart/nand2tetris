#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a_instruction.h"
#include "c_instruction.h"
#include "utils.h"
#include "file_parser.h"

#define false 0
#define true 1
#define bool short


AMap VARIABLE_MAPS;
CMap COMPILER_MAPS;
FILE *WRITE_FILE;

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

// TODO test if this works even with relative paths, absolute pats etc
char *getFileName(char *filename) {
    int dotIndex = 0;
    for (int i = 0; i < strlen(filename); i++) {
        if (filename[i] == '.') {
            dotIndex = i;
            break;
        }
    }

    // dotIndex = basename, + dot + hack + \0
    char *newFilename = malloc(dotIndex + 1 + 4 + 1);
    strcpy(newFilename, filename);
    char *strToCopy = "hacc";
    for (int i = dotIndex + 1; i < dotIndex + 1 + 4; i++) {
        newFilename[i] = strToCopy[i - dotIndex - 1];
    }
    newFilename[dotIndex + 5] = '\0';
    return newFilename;
}

// TODO: this file is called file parser, i'm compiling here, so i should move some funcs around
// Maybe move into the main handler, or something like that
int processLine(char *line, int *codeLineNumber, bool isPreprocessing) {
    line = strip(line);
    if (isPreprocessing) return preprocessLine(line, codeLineNumber);
    else return compileLine(line, codeLineNumber);
}

int compileLine(char *line, int *codeLineNumber) {
    bool isValidInstruction = true;
    bool hasError = false;
    if (line[0] == '@') {
        hasError = aInstruction(line + 1, &VARIABLE_MAPS, WRITE_FILE);
    } else if (strlen(line) > 1 && (line[1] == '=' || line[1] == ';')){
        hasError = cInstruction(&COMPILER_MAPS, line, WRITE_FILE);
    } else if (line[0] == '\0' || line[0] == '(') {
        isValidInstruction = false;
    } else  {
        printf("Istruzione invalida alla riga codice %d\n", *codeLineNumber);
        printf("Valore primo carattere: %d\n", line[0]);
        hasError = true;
    }

    if (isValidInstruction) *codeLineNumber += 1;

    if (hasError) return 1;
    else return 0;
}

int preprocessLine(char *line, int *codeLineNumber) {
    bool isValidInstruction = true;
    int labelHasError = 0;

    // \0 parses comment and empty lines
    if (line[0] == '\0') {
        isValidInstruction = false;
    } else if (line[0] == '(') {
        labelHasError = AMap_setLabels(&VARIABLE_MAPS, line, *codeLineNumber);
        isValidInstruction = false;
    }

    if (isValidInstruction) *codeLineNumber += 1;

    if (labelHasError) return 1;
    else return 0;
}

int compile(FILE *readFilePointer, FILE *writeFilePointer, bool isPreprocessing) {
    WRITE_FILE = writeFilePointer;
    fseek(readFilePointer, 0, SEEK_SET);

    bool isNewLine = false;
    int lineNumber = 0;
    int strLen = 0;
    char ch;
    do {
        ch = fgetc(readFilePointer);
        if (ch == '\n') {
            isNewLine = true;
        } else {
            isNewLine = false;
            strLen += 1;
        }

        if (isNewLine) {
            char *line = getLine(readFilePointer, strLen);
            strLen = 0;
            int hasError = processLine(line, &lineNumber, isPreprocessing);
            if (hasError) {
                printf("Error in compiling codeline %d\n", lineNumber);
                break;
            }
            free(line);
       }
    } while (ch != EOF);
}

// Style issue, i made write file pointer a global, but should be initialized here... D:
void initGlobals() {
    VARIABLE_MAPS = AMap_initAddresses();
    COMPILER_MAPS = CMap_initAddresses();
}

void clearGlobals() {
    AMap_freeMap(&VARIABLE_MAPS);
    CMap_freeMap(&COMPILER_MAPS);
}