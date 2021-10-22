#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "validators.h"
#include "CMap.h"
#include "getters.h"
#include "utils.h"

#define ERR_FOUND_DOUBLE -2
#define ERR_NOT_FOUND -1

// boolean stuff
#define false 0
#define true 1
#define bool short

char *getDestBins(CMap *map, char *instruction) {
    // Set this part to be compatible with the jump instruction!
    if (hasValidJump(instruction) && hasValidComp(instruction) && !hasValidDest(instruction)) {
        return "000";
    }

    char *dest = getDest(instruction);
    if (dest == NULL) return NULL;

    char *bins = CMap_findMapValue(map, dest, 2);
    if (bins == NULL) return "000";
    
    free(dest);
    return bins;
}

char *getJumpBins(CMap *map, char *instruction) {
    // Set this part to be compatible with the assignment instruction!
    if (!hasValidJump(instruction) && hasValidComp(instruction) && hasValidDest(instruction)) {
        return "000";
    }

    char *jump = getJump(instruction);
    if (jump == NULL) return NULL;

    char *bins = CMap_findMapValue(map, jump, 3);
    if (bins == NULL) return "000";

    free(jump);
    return bins;
}

char *getCompBins(CMap *map, char *instruction) {
    char *comp = getComp(instruction);
    if (comp == NULL) return NULL;

    // STYLE: this is bad style, repeated 2 times the same thing...
    if (isValidMemoryComp(comp)) {
        char *bins = CMap_findMapValue(map, comp, 1);
        if (bins == NULL) return NULL;
        free(comp);
        return bins;
    } else if (isValidAddressComp(comp)) {
        char *bins = CMap_findMapValue(map, comp, 0);
        if (bins == NULL) return NULL;
        free(comp);
        return bins;
    } else return NULL;
}

char *getDest(char *instruction) {
    int destLength = getCharPosition(instruction, '=');
    if (destLength < 0) return NULL;

    return getSubstr(instruction, 0, destLength);
}

char *getJump(char *instruction) {
    int beginLength = getCharPosition(instruction, ';');    
    if (beginLength < 0) return NULL;

    return getSubstr(instruction, beginLength + 1, strlen(instruction));
}

char *getComp(char *instruction) {
    int begin = getCharPosition(instruction, '=');    
    if (begin == ERR_FOUND_DOUBLE) return NULL;
    else if (begin == ERR_NOT_FOUND) begin = 0;
    else begin += 1; // se è presente = allora sommo 1, se no non lo faccio...

    int end = getCharPosition(instruction, ';');    
    if (end == ERR_FOUND_DOUBLE) return NULL;
    else if (end == ERR_NOT_FOUND) end = strlen(instruction);

    return getSubstr(instruction, begin, end);
}

char *getSubstr(char *str, int begin, int end) {
    // EXAMPLE:
    // D;JMP\0, riceverò "D;JMP\0", begin=2, end=5
    // 012345  io voglio creare un JMP\0, che è lungo 234, se tolgo solo ; ho ancora troppo
    // resta l'ultima cifra
    int length = end - begin;
    char *substr = malloc(length + 1);
    substr[length] = '\0'; 
    for (int i = 0; i < length; i++) {
        substr[i] = str[i + begin]; // +1 sennò inizio da ;
    }
    return substr;
}