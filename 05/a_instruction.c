#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "file_parser.h"
#include "a_instruction.h"

#define false 0
#define true 1
#define bool short

AMap AMap_initMap() {
    AMap newNode = malloc(sizeof(AmapNode_t));
    newNode->value = 0;
    newNode->key = NULL;
    newNode->prev = NULL;
    return newNode; 
}

void AMap_addToMap(AMap *map, char *key, int value) {
    int len = strlen(key);
    AMap newNode = malloc(sizeof(AmapNode_t));
    char *string = malloc(len + 1);
    strcpy(string, key);
    newNode->key = string;
    newNode->key[len] = '\0';
    newNode->value = value;
    newNode->prev = *map;

    // printf("Adding string %s\n Adding value %d\n", newNode->key, newNode->value);
    *map = newNode;
}

void AMap_freeMap(AMap *map) {
    // Ci ho messo un ora a scrivere questo free, quindi ora devo passare la mia acquisita saggezza a chi legge
    // questa roba che ho scritto (quindi potrei essere io del futuro, dai)
    // Allora, il parametro che ho (cioè map) sarà sempre un pointer, perché devo passare pointer in giro 
    // per cambiare con efficacia, quindi io prima dereferenzio quello la cosa a cui è puntata map, cioè la struct originale
    // così è più carina.
    // Questa struct originale la libero, facendo attenzione a liberare anche la stringa a cui è puntata, e facendo attenzione
    // a memorizzare la prossima map prima di farlo, così poi posso riassegnare a next nello stesso modo della prima istruzione
    // perché ricorda che map->prev contiene un pointer al prossimo, quindi la devo prima deferenziare
    // Inoltre sto guardando next->prev perché da come ho dichiarato il map, ho inizializzato il primo nodo 
    // in questo modo, quindi devo checkare il prev prima

    AMap next = *map; 
    do
    {
        *map = next->prev;
        free(next->key);
        free(next);
        next = *map;
    } while (next->prev != NULL);
    free(next); // nobody has freed the last next!

    return;
}

int AMap_findMapValue(AMap *map, char* key) {
    AMap next = *map;
    bool found = false;
    int value = -1;
    do
    {
        if (strcmp(key, next->key) == 0) {
            found = true;
            value = next->value;
        } 
        next = next->prev;
    } while (next->prev != NULL && !found);
    
    return value;
}


AMap AMap_initAddresses() {
    char* keys[] = {"SP", "LCL", "ARG", "THIS", "THAT", "SCREEN", "KBD", "R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15"};
    int values[] = {0,     1,     2,     3,      4,     16384,    24576,  0,    1,    2,    3,    4,    5,    6,    7,    8,    9,    10,    11,    12,     13,    14,   15};
    AMap keyMaps = AMap_initMap();
    for(int i = 0; i < 18; i++) {
        AMap_addToMap(&keyMaps, keys[i], values[i]);
    }
    return keyMaps;
}

int AMap_setLabels(AMap *map, char *key, int lineNumber) {
    if (!hasClosingParentesis(key)) return 1;
    // Togliendo parentesi;
    key++;
    key[strlen(key) - 1] = '\0';
    AMap_addToMap(map, key, lineNumber);
    return 0;
}

bool isValidChar(char c) {
    bool minuscolo = false;
    bool maiuscolo = false;
    bool numerico = false;
    bool speciale = false;
    if (c >= 'a' && c <= 'z') minuscolo = true;
    else if (c >= 'A' && c <= 'Z') maiuscolo = true;
    else if (c >= '0' && c <= '9') numerico = true;
    else if (c == '_' || c == '.' || c == '$') speciale = true;

    return minuscolo || maiuscolo || numerico || speciale;
}

bool isValidString(char *str) {
    bool isValid = true;
    if (str[0] >= '0' && str[0] <= '9') isValid = false;

    for(int i = 0; i < strlen(str) && isValid; i++) {
        if (!isValidChar(str[i])) isValid = false;
    }

    return isValid;
}

int getAddress(char *address, AMap *map) {
    bool isNumber = strIsNumber(address);
    if (isNumber) return strToInt(address);

    int value = AMap_findMapValue(map, address);
    if (value > -1) return value;
    
    if (isValidString(address)) {
        AMap_addToMap(map, address, (*map)->value + 1);
        return (*map)->value;
    }

    printf("Error: variabile invalida: %s\n", address);
    // errore
    return -1;
}

int aInstruction(char *address, AMap *keysMappings, FILE *writePtr) {

    int addrValue = getAddress(address, keysMappings);
    if (addrValue >= 0){
        char *binaryAddress = intToStr15Bin(addrValue);

        // USE THESE TO DEBUG A_INSTRUCTIONS!
        // printf("got a address: %d\n", addrValue);
        fprintf(writePtr, "0%s\n", binaryAddress);
        free(binaryAddress);
    } else {
        // This should never be run in theory
        // but i'm keeping this here, just in case...
        printf("Not a address \n");
        return 1;
    }
    return 0;
}