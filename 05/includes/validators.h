#pragma once
#define bool short

bool isValidCInstruction(char *instruction);


// Looks if there is a valid Dest, jump or comp part
bool hasValidDest(char *instruction);
bool hasValidJump(char *instruction);
bool hasValidComp(char *instruction);

// Gets the single part and returns if its valid
bool isValidMemoryComp(char *comp);
bool isValidAddressComp(char *comp);
bool isValidDest(char *comp);
bool isValidJump(char *comp);
