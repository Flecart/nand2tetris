#include <stdio.h>
#include <stdlib.h>
#include "file_parser.h"
#include "utils.h"
#include "compiler.h"

#define false 0
#define true 1

int main(int argc, char *argv[]){

    if (isValidArg(argc) == 1) return 1;
    if (!isValidName(argv[1])) {
        printf("The name %s is not valid. Either it doesn't have an extension or hasn't got .vm\n", argv[1]);
        return 1;
    }

    char *writeFilename = getFileNameWithExt(argv[1]);
    // printf("New filename: %s\n", writeFilename);

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

    compile(readFilePtr, writeFilePtr, getFilename(argv[1]));

    printf("Compiled successfully: \n");
    fclose(readFilePtr);
    fclose(writeFilePtr);
    free(writeFilename);

    return 0;
}
