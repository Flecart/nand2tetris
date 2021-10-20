#include <stdio.h>
#include <stdlib.h>
#include "file_parser.h"
#include "utils.h"
#include "a_instruction.h"
#include "c_instruction.h"

#define false 0
#define true 1

int main(int argc, char *argv[]){

    if (isValidArg(argc) == 1) return 0;
    char *writeFilename = getFileName(argv[1]);
    printf("New filename: %s\n", writeFilename);

    FILE *readFilePtr, *writeFilePtr;
    readFilePtr = fopen(argv[1], "r");
    if (readFilePtr == NULL) {
        printf("File %s not present\n", argv[1]);
        return 0;
    }

    writeFilePtr = fopen(writeFilename, "w");
    if (writeFilePtr == NULL) {
        printf("File %s could not be written\n", writeFilename);
        return 0;
    }

    initGlobals();

    compile(readFilePtr, writeFilePtr, true);
    compile(readFilePtr, writeFilePtr, false);

    clearGlobals();
    fclose(readFilePtr);
    fclose(writeFilePtr);
    free(writeFilename);

    return 0;
}
