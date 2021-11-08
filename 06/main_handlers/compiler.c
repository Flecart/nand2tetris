#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stackAritmetic.h"
#include "file_parser.h"
#include "utils.h"

#define bool short
#define false 0
#define true 1

int handleInstruction(char *instr, char *filename, FILE *writeFilePointer) {
    instr = strip(instr);
    // TODO recognize instruction and call right function!
    if (strlen(instr) > 0) {
        return aritmeticHandler(instr, filename, writeFilePointer);
    }

    return 0;
}

void compile(FILE *readFilePointer, FILE *writeFilePointer, char *filename) {
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
            int hasError = handleInstruction(line, filename, writeFilePointer);
            if (hasError) {
                printf("Error in compiling line %d: %s\n", lineNumber, line);
                break;
            }
            free(line);
       }
    } while (ch != EOF);

    fprintf(writeFilePointer, "(END)\n@END\n0;JMP");
    return;
}