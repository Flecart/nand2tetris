#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "c_instruction.h"
#include "validators.h"
#include "getters.h"
#include "utils.h"

#define ERR_FOUND_DOUBLE -2
#define ERR_NOT_FOUND -1

// boolean stuff
#define false 0
#define true 1
#define bool short

int cInstruction(CMap *map, char *instruction, FILE *writePtr) {
    if (!isValidCInstruction(instruction)) {
        printf("Error at %s\n", instruction);
        return 1;
    }
    char *compiledCommand = malloc(17);
    compiledCommand[16] = '\0';

    int i = 0;
    for (; i < 3; i++) {
        compiledCommand[i] = '1';
    }

    char *comp = getCompBins(map, instruction);
    if (comp == NULL) {
        printf("Invalid Comp field (the part after the = and before ;) \n");
        free(compiledCommand);
        return 1;
    }
    for (int j = 0; j < 7; i++, j++) {
        compiledCommand[i] = comp[j];
    }

    char *dest = getDestBins(map, instruction);
    if (dest == NULL) {
        printf("Invalid destination field (the part before the =) \n");
        free(compiledCommand);
        return 1;
    }
    for (int j = 0; j < 3; i++, j++) {
        compiledCommand[i] = dest[j];
    }

    char *jump = getJumpBins(map, instruction);
    if (jump == NULL) {
        printf("Invalid jump field (the part after the ;) \n");
        free(compiledCommand);
        return 1;
    }
    for (int j = 0; j < 3; i++, j++) {
        compiledCommand[i] = jump[j];
    }

    fprintf(writePtr, "%s\n", compiledCommand);
    free(compiledCommand);
    return 0;
}