#include <stdlib.h>
#include <string.h>
#include "AMap.h"

// import hasClosingParentesis
#include "utils.h"

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
    char* keys[] = {"SP", "LCL", "ARG", "THIS", "THAT", "SCREEN", "KBD"};
    int values[] = {0,     1,     2,     3,      4,     16384,    24576};
    AMap keyMaps = AMap_initMap();
    for(int i = 0; i < 7; i++) {
        AMap_addToMap(&keyMaps, keys[i], values[i]);
    }
    return keyMaps;
}
void AMap_addRegisters(AMap *map) {
    char* keys[] = {"R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15"};
    int values[] = {0,    1,    2,    3,    4,    5,    6,    7,    8,    9,    10,    11,    12,     13,    14,   15};
    for(int i = 0; i < 16; i++) {
        AMap_addToMap(map, keys[i], values[i]);
    }
}

int AMap_setLabels(AMap *map, char *key, int lineNumber) {
    if (!hasClosingParentesis(key)) return 1;
    // Togliendo parentesi;
    key++;
    key[strlen(key) - 1] = '\0';
    AMap_addToMap(map, key, lineNumber);
    return 0;
}

