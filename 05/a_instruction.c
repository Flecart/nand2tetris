#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "a_instruction.h"

#define false 0
#define true 1
#define bool short

Map initMap() {
    Map newNode = malloc(sizeof(mapNode_t));
    newNode->value = 0;
    newNode->key = NULL;
    newNode->prev = NULL;
    return newNode; 
}

void addToMap(Map *map, char *key, int value) {
    Map newNode = malloc(sizeof(mapNode_t));
    char *string = malloc(strlen(key));
    strcpy(string, key);
    newNode->key = string;
    newNode->value = value;
    newNode->prev = *map;

    // printf("Adding string %s\n Adding value %d\n", newNode->key, newNode->value);
    *map = newNode;
}

void freeMap(Map *map) {
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

    Map next = *map; 
    do
    {
        *map = next->prev;
        free(next->key);
        free(next);
        next = *map;
    } while (next->prev != NULL);

    return;
}

int findMapValue(Map *map, char* key) {
    Map next = *map;
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


Map initAddresses() {
    char* keys[] = {"R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15", "SCREEN", "KBD"};
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16384, 24576};
    Map keyMaps = initMap();
    for(int i = 0; i < 18; i++) {
        addToMap(&keyMaps, keys[i], values[i]);
    }
    return keyMaps;
}

int getAddress(char *address, Map *map) {
    // TODO: ritorna errore se va oltre al numero di memoria consentito
    bool isNumber = strIsNumber(address);
    if (isNumber) return strToInt(address);

    int value = findMapValue(map, address);
    if (value > -1) return value;
    else return -1; // TODO: create new value in the map
}

int aInstruction(char *address) {
    // TODO: don't want to init and free the maps everysingle time, should
    // be called by main func in the assembler

    Map keysMappings = initAddresses();
    int addrValue = getAddress(address, &keysMappings);
    if (addrValue >= 0){
        printf("got a address: %d\n", addrValue);
    } else {
        printf("Not a address \n");
    }
    freeMap(&keysMappings);
    return 0;
}