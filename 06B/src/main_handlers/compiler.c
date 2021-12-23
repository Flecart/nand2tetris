#include "compiler.h"

int handleInstruction(char *instr, char *filename, FILE *writeFilePointer) {
    instr = strip(instr);
    char *firstWord = getWord(instr, 1);
    Arits arits = getArits(firstWord);
    Flows flows = getFlows(firstWord);
    Funcs funcs = getFuncs(firstWord);

    int retCode;
    if      (arits != ARITS_UNKNOWN) retCode = aritmeticHandler(instr, filename, writeFilePointer);
    else if (flows != FLOWS_UNKNOWN) retCode = programFlow(instr, filename, writeFilePointer);
    else if (funcs != FUNC_UNKNOWN)  retCode = functions(instr, writeFilePointer);
    else if (strlen(instr) <= 0) retCode = 0;
    else {
        printf("This line -%s- is unknown\n", instr);
        retCode = 1;
    }
    free(firstWord);
    return retCode;
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

void writeProgramBegin(FILE *writeFilePtr, bool has_syscall) {
    fprintf(writeFilePtr, ""
        "@256\n"
        "D=A\n"
        "@SP\n"
        "M=D\n");
    if (has_syscall) {
        char *sys_init = call("call Sys.init 0");
        fprintf(writeFilePtr, sys_init, "");
        free(sys_init);
    }
}