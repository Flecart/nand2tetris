#include <stdio.h>
#include <stdlib.h>
#include "file_parser.h"
#include "utils.h"
#include "a_instruction.h"
#include "c_instruction.h"

#define false 0
#define true 1
#define bool short

AMap VARIABLE_MAPS;
CMap COMPILER_MAPS;

// STYLE ISSUE: non sono sicuro se la flag isProcessing è giusta per questa roba
// Credo ci sia una soluzione più lineare per fare quello che sto facendo qui.
int interpret(char *line, int *codeLineNumber, bool isPreprocessing){
    line = strip(line);
    bool isValidInstruction = true;
    bool hasError = false;
    if (line[0] == '@' && !isPreprocessing) {
        aInstruction(line + 1, &VARIABLE_MAPS);
    } else if ((line[1] == '=' || line[1] == ';') && !isPreprocessing){
        cInstruction(&COMPILER_MAPS, line);
    } else if (line[0] == '\0') {
        isValidInstruction = false;
    } else if (line[0] == '(') {
        AMap_setLabels(&VARIABLE_MAPS, line, *codeLineNumber);
        isValidInstruction = false;
    } else if (!isPreprocessing) {
        printf("Istruzione invalida alla riga codice %d\n", *codeLineNumber);
        printf("Valore primo carattere: %d\n", line[0]);
        hasError = true;
    }

    if (isValidInstruction) *codeLineNumber += 1;

    if (hasError) return -1;
    else return 0;
}



int main(int argc, char *argv[]){

    if (isValidArg(argc) == 1) return 0;

    FILE *filePointer;
    filePointer = fopen(argv[1], "r");
    if (filePointer == NULL) {
        printf("File %s not present\n", argv[1]);
        return 0;
    }

    VARIABLE_MAPS = AMap_initAddresses();
    COMPILER_MAPS = CMap_initAddresses();

    // TODO: this part has bad style, its repeated two times
    // but it's nearly identical, should make ti into a func
    // with preprocc boolean, MAYBE PUT IT IN FILE_PARSER
    bool isNewLine = false;
    int lineNumber = 0;
    int strLen = 0;
    char ch;
    do {
        ch = fgetc(filePointer);
        if (ch == '\n') {
            isNewLine = true;
        } else {
            isNewLine = false;
            strLen += 1;
        }

        if (isNewLine) {
            char *line = getLine(filePointer, strLen);
            strLen = 0;
            interpret(line, &lineNumber, true);
            // printf("%s\n", line);
            free(line);
       }
    } while (ch != EOF);

    isNewLine = false;
    lineNumber = 0;
    strLen = 0;
    fseek(filePointer, 0, SEEK_SET);
    do {
        ch = fgetc(filePointer);
        if (ch == '\n') {
            isNewLine = true;
        } else {
            isNewLine = false;
            strLen += 1;
        }

        if (isNewLine) {
            char *line = getLine(filePointer, strLen);
            strLen = 0;
            interpret(line, &lineNumber, false);
            // printf("Ho trovato nuova riga!\n");
            printf("%s\n", line);
            free(line);
       }
    } while (ch != EOF);
    
    AMap_freeMap(&VARIABLE_MAPS);
    CMap_initAddresses(&COMPILER_MAPS);

    return 0;
}
