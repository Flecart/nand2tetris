#pragma once
#define bool short

// CmapNode types
// 0 = comp no a
// 1 = comp with a
// 2 = Mnemonic
// 3 = jump
typedef struct CmapNode {
    char *key;
    char *value;
    int type;
    struct CmapNode *prev;
} CmapNode_t;

typedef CmapNode_t *CMap;

// CMap functions, similiar to AMap
CMap CMap_initMap();
void CMap_addToMap(CMap *map, char *key, char *value, int type);
void CMap_freeMap(CMap *map);
char *CMap_findMapValue(CMap *map, char* key, int type);
CMap CMap_initAddresses();