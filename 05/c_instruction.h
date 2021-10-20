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

bool isValidCInstruction(char *instruction);
char *getSubstr(char *str, int begin, int end);
int getCharPosition(char *instruction, char target);

// Returns dinamically allocated C string, gets the wanted part of the instruction
char *getDest(char *instruction);
char *getJump(char *instruction);
char *getComp(char *instruction);

char *getDestBins(CMap *map, char *instruction);
char *getJumpBins(CMap *map, char *instruction);
char *getCompBins(CMap *map, char *instruction);

// Looks if there is a valid Dest, jump or comp part
bool hasValidDest(char *instruction);
bool hasValidJump(char *instruction);
bool hasValidComp(char *instruction);

// Gets the single part and returns if its valid
bool isValidMemoryComp(char *comp);
bool isValidAddressComp(char *comp);
bool isValidDest(char *comp);
bool isValidJump(char *comp);


int cInstruction(CMap *map, char *instruction, FILE *writePtr);