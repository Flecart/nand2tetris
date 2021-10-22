#pragma once

#include "AMap.h"
#define bool short

int aInstruction(char *address, AMap *keysMappings, FILE *writePtr);
int getAddress(char *address, AMap *map);

// A_INSTRUCTION VALIDATORS
bool isValidChar(char c);
bool isValidString(char *str);