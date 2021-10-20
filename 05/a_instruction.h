#pragma once

#define bool short
typedef struct AmapNode {
    char *key;
    int value;
    struct AmapNode *prev;
} AmapNode_t;

typedef AmapNode_t *AMap;

AMap AMap_initMap();
void AMap_addToMap(AMap *map, char *key, int value);
void AMap_nullifyMap(AMap *map);
int AMap_findMapValue(AMap *map, char* key);
AMap AMap_initAddresses();
void AMap_freeMap(AMap *map);
int AMap_setLabels(AMap *map, char *key, int lineNumber);



int aInstruction(char *address, AMap *keysMappings);

// String stuff
bool isValidChar(char c);
bool isValidString(char *str);