#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "file_parser.h"


#define false 0
#define true 1
#define bool short

int isValidArg(int argc) {
    if (argc != 2) {
        printf("Error in command\n");
        printf("[Usage]\n");
        printf("./VMTranslator [filename]\n");
        return 1;
    }
    return 0;
}

int isValidName(char *filename) {
    char *validName = ".vm";
    int dotPosition = getCharPosition(filename, '.');
    if (dotPosition < 0) return false;

    bool isValid = true;
    for (int i = 0; i < strlen(validName); i++){
        if (filename[dotPosition + i] != validName[i]) isValid = false;
    }
    return isValid;
}

char* getLine(FILE *filePointer, int strLen) {
    char *currLine = (char *) malloc((strLen + 1) * sizeof(char));
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
char *getFileNameWithExt(char *filename) {
    int dotIndex = getCharPosition(filename, '.');
    if (dotIndex < 0) return NULL;

    // dotIndex = basename, + dot + asm + \0
    char *strToCopy = "asm";
    int toCopySize = strlen(strToCopy);
    char *newFilename = (char *) malloc((dotIndex + 1 + toCopySize + 1) * sizeof(char));
    strcpy(newFilename, filename);
    for (int i = dotIndex + 1; i < dotIndex + 1 + toCopySize; i++) {
        newFilename[i] = strToCopy[i - dotIndex - 1];
    }
    newFilename[dotIndex + 1 + toCopySize] = '\0';
    return newFilename;
}

char *getFilename(char *filename) {
    int dotIndex = getCharPosition(filename, '.');
    if (dotIndex < 0) return NULL;
    
    char *file = (char *) malloc((dotIndex) * sizeof(char));
    file[dotIndex] = '\0';
    for (int i = 0; i < dotIndex; i++) {
        file[i] = filename[i];
    }
    return file;
}