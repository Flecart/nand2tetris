#pragma once
#define bool short

// gets the number of the arguments
// returns 1 if its a wrong number
// else 0
int isValidArg(int argc);

// Questa è difficile da descrivere, guarda il codice
// Per dirlo in modo spiccio vado indietro di strLen
// e comincio a leggere finché non vedo un \n e ti ritorno questa stringa
char* getLine(FILE *filePointer, int strLen);

// Precondition: get filename to open
// Post condition: returns the name of the name to write
// REMEMBER TO FREE
char *getFileNameWithExt(char *filename);
char *getFilename(char *filename);

// Gets the filename to open and checks if the first extension
// terminates with .asm
int isValidName(char *filename);