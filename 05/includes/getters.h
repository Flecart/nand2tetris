#pragma once 
#include "CMap.h"

// Returns dinamically allocated C string, gets the wanted part of the instruction
char *getDest(char *instruction);
char *getJump(char *instruction);
char *getComp(char *instruction);

char *getDestBins(CMap *map, char *instruction);
char *getJumpBins(CMap *map, char *instruction);
char *getCompBins(CMap *map, char *instruction);

char *getSubstr(char *str, int begin, int end);