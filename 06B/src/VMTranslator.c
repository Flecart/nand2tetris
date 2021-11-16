#include "VMTranslator.h"

int main(int argc, char *argv[]){
    int retValue = 0;
    if (isValidArg(argc) == 1) return 1;
    if (!isValidName(argv[1])) {
        printf("Looking at directory %s\n", argv[1]);
        List dir = walk_dir(argv[1]);
        if (dir->next == NULL) {
            printf("%s is not a valid directory\n", argv[1]);
            retValue = 1;
        }
        else handleDirectory(dir, argv[1]);

        freeList(&dir);
    } else {
        printf("Looking at File %s\n", argv[1]);
        handleFile(argv);
    }
    return retValue;
}

void handleFile(char *argv[]) {
    char *writeFilename = getFileNameWithExt(argv[1]);
    char *filename = getFilename(argv[1]);
    // printf("New filename: %s\n", writeFilename);

    FILE *readFilePtr, *writeFilePtr;
    readFilePtr = fopen(argv[1], "r");
    if (readFilePtr == NULL) {
        printf("File %s not present\n", argv[1]);
        return;
    }

    writeFilePtr = fopen(writeFilename, "w");
    if (writeFilePtr == NULL) {
        printf("File %s could not be written\n", writeFilename);
        return;
    }
    fprintf(writeFilePtr, "@256\nD=A\n@R0\nM=D\n"); // SET STANDARD SP POINTER
    compile(readFilePtr, writeFilePtr, filename);
    fclose(readFilePtr);
    fclose(writeFilePtr);
    free(writeFilename);
    free(filename);

    return;
}

void handleDirectory(List dirs, char *dir) {
    List next = dirs;
    int dirLen = strlen(dir);
    char *writeFilename;
    char *rightDirname;
    if (dir[dirLen - 1] == '/') rightDirname = strCat(dir, "");
    else rightDirname = strCat(dir, "/");

    writeFilename = strCat(rightDirname, "Main.asm");

    bool hasError = false;
    FILE *out = fopen(writeFilename, "w");
    while (next->next != NULL && !hasError) {
        if (isValidName(next->name)) {
            char *name = strCat(rightDirname, next->name);
            printf("Trying to compile %s\n", name);
            char *noExtensionName = getFilename(next->name);
            FILE *in;
            if ((in = fopen(name, "r")) == NULL) {
                printf("Could not open %s\n", name);
                hasError = true;
            }
            compile(in, out, noExtensionName);
            free(name);
            free(noExtensionName);
            fclose(in);
        }
        next = next->next;
    }
    fclose(out);
    free(writeFilename);
    free(rightDirname);
}