#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "a_instruction.h"
#include "c_instruction.h"
#include "compiler.h"
#include "file_parser.h"

#define false 0
#define true 1
#define bool short

AMap VARIABLE_MAPS;
CMap COMPILER_MAPS;
FILE *WRITE_FILE;

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
    } else if (getCharPosition(line, '=') > 0 || getCharPosition(line, ';') > 0){
        hasError = cInstruction(&COMPILER_MAPS, line, WRITE_FILE);
    } else if (line[0] == '\0' || line[0] == '(') {
        isValidInstruction = false;
    } else  {
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

void compile(FILE *readFilePointer, FILE *writeFilePointer, bool isPreprocessing) {
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
                printf("Error in compiling line %d: %s\n", lineNumber, line);
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

void initRegisters() {
    AMap_addRegisters(&VARIABLE_MAPS);
}

void clearGlobals() {
    AMap_freeMap(&VARIABLE_MAPS);
    CMap_freeMap(&COMPILER_MAPS);
}