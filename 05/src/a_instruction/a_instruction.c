#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "a_instruction.h"
#include "AMap.h"

#define false 0
#define true 1
#define bool short

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


// A_INSTRUCTION VALIDATORS
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
