#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "c_instruction.h"

#define ERR_FOUND_DOUBLE -2
#define ERR_NOT_FOUND -1

// boolean stuff
#define false 0
#define true 1
#define bool short

// TODO: at the end of the project, refactor each region in a stand alone module

// REGION GET INSTRUCTION PARTS


int cInstruction(CMap *map,char *instruction) {
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

    printf("Compiled C: %s\n", compiledCommand);
    return 0;
}

bool isValidCInstruction(char *instruction) {
    bool isValid = false;
    bool hasComp = hasValidComp(instruction);
    bool hasJump = hasValidJump(instruction);
    bool hasDest = hasValidDest(instruction);

    if (hasComp && hasDest) isValid = true;
    else if (hasComp && hasJump) isValid = true;
    
    // printf("Current state of: hasComp: %d, hasJump: %d, hasDest: %d\n", hasComp, hasJump, hasDest);
    return isValid;
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

int getCharPosition(char *instruction, char target) {
    int pos = ERR_NOT_FOUND;
    bool found = false;
    for (int i = 0; i < strlen(instruction); i++) {
        // If there is double ; give error!
        if (found && instruction[i] == target) return ERR_FOUND_DOUBLE;
        if (instruction[i] == target) {
            found = true;
            pos = i;
        }
    }  
    return pos;
}
// ENDREGION
// REGION GET

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
// ENDREGION

// REGION fields compare, many repetitions
// TODO: try to make a dinamic function that takes input a array of strings and compares?
bool hasValidDest(char *instruction) {
    char *dest = getDest(instruction);
    if (dest == NULL) return false;

    bool found = false;
    if (isValidDest(dest)) found = true;
    free(dest);

    return found;
}

bool hasValidJump(char *instruction) {
    char *jump = getJump(instruction);
    if (jump == NULL) return false;

    bool found = false;
    if (isValidJump(jump)) found = true;
    free(jump);

    return found;
}

bool hasValidComp(char *instruction) {
    char *comp = getComp(instruction);
    if (comp == NULL) return false;
    bool found = false;
    if (isValidMemoryComp(comp)) found = true;
    else if (isValidAddressComp(comp)) found = true;
    free(comp);
    return found;
}

bool isValidMemoryComp(char *comp) {
    bool isValid = false;
    char *validStrings[] = {"M", "!M", "-M", "M+1", "M-1", "D+M", "M+D", "D-M", "M-D", "D&M", "D|M", "M&D", "M|D"};
    for (int i = 0; i < 13; i++) {
        if (strcmp(comp, validStrings[i]) == 0) isValid = true;
    }
    return isValid;
}

bool isValidAddressComp(char *comp) {
    bool isValid = false;
    char *validStrings[] = {"0", "1", "-1", "D", "A", "!D", "!A", "-D", "-A", "D+1", "A+1", "D+A", "A+D", "D-A", "A-D", "D&A", "D|A", "A&D", "A|D"};
    for (int i = 0; i < 19; i++) {
        if (strcmp(comp, validStrings[i]) == 0) isValid = true;
    }
    return isValid;
}

bool isValidDest(char *comp) {
    bool isValid = false;
    char *validStrings[] = {"D", "A", "M", "MD", "AM", "AD", "AMD"};
    for (int i = 0; i < 7; i++) {
        if (strcmp(comp, validStrings[i]) == 0) isValid = true;
    }
    return isValid;
}

bool isValidJump(char *comp) {
    bool isValid = false;
    char *validStrings[] = {"JMP", "JLE", "JNE", "JLT", "JGE", "JGT", "JEQ"};
    for (int i = 0; i < 7; i++) {
        if (strcmp(comp, validStrings[i]) == 0) isValid = true;
    }
    return isValid;
}
// ENDREGION

// REGION CMAP
CMap CMap_initMap() {
    CMap newNode = malloc(sizeof(CmapNode_t));
    newNode->value = NULL;
    newNode->key = NULL;
    newNode->type = -1;
    newNode->prev = NULL;
    return newNode; 
}

void CMap_addToMap(CMap *map, char *key, char *value, int type) {
    int lenKey = strlen(key);
    int lenValue = strlen(value);
    char *keyString = malloc(lenKey + 1);
    char *valueString = malloc(lenValue + 1);
    strcpy(keyString, key);
    strcpy(valueString, value);

    CMap newNode = malloc(sizeof(CmapNode_t));
    newNode->key = keyString;
    newNode->value = valueString;

    newNode->key[lenKey] = '\0';
    newNode->value[lenValue] = '\0';
    newNode->type = type;
    newNode->prev = *map;

    // printf("Adding string %s\n Adding value %d\n", newNode->key, newNode->value);
    *map = newNode;
}

void CMap_freeMap(CMap *map) {
    CMap next = *map; 
    do
    {
        *map = next->prev;
        free(next->key);
        free(next->value);
        free(next);
        next = *map;
    } while (next->prev != NULL);

    return;
}


char *CMap_findMapValue(CMap *map, char* key, int type) {
    CMap next = *map;
    bool found = false;
    char *value = NULL;
    do
    {
        if (strcmp(key, next->key) == 0 && type == next->type) {
            found = true;
            value = next->value;
        } 
        next = next->prev;
    } while (next->prev != NULL && !found);
    
    return value;
}


CMap CMap_initAddresses() {
    CMap keyMaps = CMap_initMap();

    // Adding comp a=0 addrs
    char *addresskeys[]   = {"0",       "1",       "-1",      "D",       "A",       "!D",      "!A",      "-D",      "-A",      "D+1",     "A+1",     "D+A",     "A+D",     "D-A",     "A-D",     "D&A",     "D|A",     "A&D",     "A|D"};
    char *addressValues[] = {"0101010", "0111111", "0111010", "0001100", "0110000", "0001101", "0110001", "0001111", "0110011", "0011111", "0110111", "0000010", "0000010", "0010011", "0000111", "0000000", "0010101", "0000000", "0010101"};
    for(int i = 0; i < 19; i++) {
        CMap_addToMap(&keyMaps, addresskeys[i], addressValues[i], 0);
    }

    char *memoryKeys[]   = {"M",       "!M",      "-M",      "M+1",     "M-1",     "D+M",     "M+D",     "D-M",     "M-D",     "D&M",     "D|M",     "M&D",     "M|D"};
    char *memoryValues[] = {"1110000", "1110001", "1110011", "1110111", "1110010", "1000010", "1000010", "1010011", "1000111", "1000000", "1010101", "1000000", "1010101"};
    for(int i = 0; i < 13; i++) {
        CMap_addToMap(&keyMaps, memoryKeys[i], memoryValues[i], 1);
    }

    char *destKeys[]   = {"D",   "A",   "M",   "MD",  "AM",  "AD",  "AMD"};
    char *destValues[] = {"010", "100", "001", "011", "101", "110", "111"};
    for(int i = 0; i < 7; i++) {
        CMap_addToMap(&keyMaps, destKeys[i], destValues[i], 2);
    }

    char *jumpKeys[]   = {"JEQ", "JLT", "JGT", "JGE", "JNE", "JLE", "JMP"};
    char *jumpValues[] = {"010", "100", "001", "011", "101", "110", "111"};
    for(int i = 0; i < 7; i++) {
        CMap_addToMap(&keyMaps, jumpKeys[i], jumpValues[i], 3);
    }

    return keyMaps;
}