#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stackAritmetic.h"
#include "programFlow.h"
#include "functions.h"
#include "file_parser.h"
#include "utils.h"
#include "walk_dir.h"

#define bool short
#define false 0
#define true 1

int handleInstruction(char *instr, char *filename, FILE *writeFilePointer) {
    instr = strip(instr);
    char *firstWord = getWord(instr, 1);
    Arits arits = getArits(firstWord);
    Flows flows = getFlows(firstWord);
    Funcs funcs = getFuncs(firstWord);

    int retCode;
    if      (arits != ARITS_UNKNOWN) retCode = aritmeticHandler(instr, filename, writeFilePointer);
    else if (flows != FLOWS_UNKNOWN) retCode = programFlow(instr, writeFilePointer);
    else if (funcs != FUNC_UNKNOWN)  retCode = functions(instr, writeFilePointer);
    else if (strlen(instr) <= 0) retCode = 0;
    else {
        printf("This line -%s- is unknown\n", instr);
        retCode = 1;
    }
    free(firstWord);
    return retCode;
}

void compileDir(List dirs, char *dir) {
    List next = dirs;
    bool hasError = false;
    char *writeFilename = strCat(dir, "Main.vm");
    FILE *out = fopen(writeFilename, 'w');
    while (next->next != NULL && !hasError) {
        if (isValidName(next->name)) {
            char *name = strCat(dir, next->name);
            char *noExtensionName = getFilename(next->name);
            FILE *in;
            if ((in = fopen(in, "r")) == NULL) {
                printf("Could not open %s\n", next->name);
                hasError = true;
            }
            compile(in, out, noExtensionName);
            free(name);
            free(noExtensionName);
        }
        next = next->next;
    }

    free(writeFilename);
    freeList(dirs);
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
                free(line);
                break;
            }
            free(line);
       }
    } while (ch != EOF);
    return;
}