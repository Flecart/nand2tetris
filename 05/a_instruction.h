#pragma once

typedef struct mapNode {
    char *key;
    int value;
    struct mapNode *prev;
} mapNode_t;

typedef mapNode_t *Map;

Map initMap();
void addToMap(Map *map, char *key, int value);
void nullifyMap(Map *map);
int findMapValue(Map *map, char* key);
Map initAddresses();
void freeMap(Map *map);
int setLabels(Map *map, char *key, int lineNumber);

int aInstruction(char *address, Map *keysMappings);

// String stuff
bool isValidChar(char c);
bool isValidString(char *str);