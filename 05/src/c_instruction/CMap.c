#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "CMap.h"
#include "utils.h"

#define ERR_FOUND_DOUBLE -2
#define ERR_NOT_FOUND -1

// boolean stuff
#define false 0
#define true 1
#define bool short


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
    free(next); // nobody has freed the last next!
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
    char *addresskeys[]   = {"0",       "1",       "-1",      "D",       "A",       "!D",      "!A",      "-D",      "-A",      "D+1",     "A+1",     "D-1",     "A-1",     "D+A",     "A+D",     "D-A",     "A-D",     "D&A",     "D|A",     "A&D",     "A|D"};
    char *addressValues[] = {"0101010", "0111111", "0111010", "0001100", "0110000", "0001101", "0110001", "0001111", "0110011", "0011111", "0110111", "0001110", "0110010", "0000010", "0000010", "0010011", "0000111", "0000000", "0010101", "0000000", "0010101"};
    for(int i = 0; i < 21; i++) {
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