#include <stdio.h>
#include <stdlib.h>
#include "file_parser.h"
#include "utils.h"
#include "a_instruction.h"

#define false 0
#define true 1
#define bool short


void cInstruction(char *cmd) {
    printf("%s hello c instruction!\n", cmd);
    return;
}


void label(char *line){};

void jump(char *line){};

void interpret(char *line, int lineNumber){
    line = strip(line);
    if (line[0] == '@') {
        aInstruction(line + 1);
    } else if (line[1] == '='){
        cInstruction(line);
    } else if (line[1] == ';') {
        jump(line);
    } else if (line[0] == '('){
        label(line);
    } else if (line[0] == '\0') {
        // DO nothing, empty line
    } else {
        printf("Istruzione invalida alla riga %d\n", lineNumber);
        printf("Valore primo carattere: %d\n", line[0]);
    }

    return;
}



int main(int argc, char *argv[]){

    if (isValidArg(argc) == 1) return 0;

    FILE *filePointer;
    filePointer = fopen(argv[1], "r");
    if (filePointer == NULL) {
        printf("File %s not present\n", argv[1]);
        return 0;
    }

    bool isNewLine = false;
    int lineNumber = 0;
    int strLen = 0;
    char ch;
    do {
        ch = fgetc(filePointer);
        if (ch == '\n') {
            isNewLine = true;
            lineNumber += 1;
        } else {
            isNewLine = false;
            strLen += 1;
        }

        if (isNewLine) {
            char *line = getLine(filePointer, strLen);
            strLen = 0;
            interpret(line, lineNumber);
            // printf("Ho trovato nuova riga!\n");
            printf("%s\n", line);
            free(line);
       }
    } while (ch != EOF);
    
    return 0;
}
