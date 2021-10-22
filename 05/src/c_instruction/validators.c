#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "validators.h"
#include "getters.h"
#include "utils.h"

#define ERR_FOUND_DOUBLE -2
#define ERR_NOT_FOUND -1

// boolean stuff
#define false 0
#define true 1
#define bool short


bool isValidCInstruction(char *instruction) {
    bool isValid = false;
    bool hasComp = hasValidComp(instruction);
    bool hasJump = hasValidJump(instruction);
    bool hasDest = hasValidDest(instruction);

    if (hasComp && hasDest) isValid = true;
    else if (hasComp && hasJump) isValid = true;
    
    // printf("Current state of: hasComp: %d, hasJump: %d, hasDest: %d\n", hasComp, hasJump, hasDest);
    return isValid;
}

// TODO: try to make a dinamic function that takes input a array of strings and compares?
bool hasValidDest(char *instruction) {
    char *dest = getDest(instruction);
    if (dest == NULL) return false;

    bool found = false;
    if (isValidDest(dest)) found = true;
    free(dest);

    return found;
}

bool hasValidJump(char *instruction) {
    char *jump = getJump(instruction);
    if (jump == NULL) return false;

    bool found = false;
    if (isValidJump(jump)) found = true;
    free(jump);

    return found;
}

bool hasValidComp(char *instruction) {
    char *comp = getComp(instruction);
    if (comp == NULL) return false;
    bool found = false;
    // printf("Current comp %s\n", comp);
    if (isValidMemoryComp(comp)) found = true;
    else if (isValidAddressComp(comp)) found = true;
    free(comp);
    return found;
}

bool isValidMemoryComp(char *comp) {
    bool isValid = false;
    char *validStrings[] = {"M", "!M", "-M", "M+1", "M-1", "D+M", "M+D", "D-M", "M-D", "D&M", "D|M", "M&D", "M|D"};
    for (int i = 0; i < 13; i++) {
        if (strcmp(comp, validStrings[i]) == 0) isValid = true;
    }
    return isValid;
}

bool isValidAddressComp(char *comp) {
    bool isValid = false;
    char *validStrings[] = {"0", "1", "-1", "D", "A", "!D", "!A", "-D", "-A", "D+1", "A+1", "D-1", "A-1", "D+A", "A+D", "D-A", "A-D", "D&A", "D|A", "A&D", "A|D"};
    for (int i = 0; i < 21; i++) {
        if (strcmp(comp, validStrings[i]) == 0) isValid = true;
    }
    return isValid;
}

bool isValidDest(char *comp) {
    bool isValid = false;
    char *validStrings[] = {"D", "A", "M", "MD", "AM", "AD", "AMD"};
    for (int i = 0; i < 7; i++) {
        if (strcmp(comp, validStrings[i]) == 0) isValid = true;
    }
    return isValid;
}

bool isValidJump(char *comp) {
    bool isValid = false;
    char *validStrings[] = {"JMP", "JLE", "JNE", "JLT", "JGE", "JGT", "JEQ"};
    for (int i = 0; i < 7; i++) {
        if (strcmp(comp, validStrings[i]) == 0) isValid = true;
    }
    return isValid;
}