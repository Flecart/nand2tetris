#pragma once

#define bool short

char* strip(char *string);
int strToInt(char *str);
bool strIsNumber(char *str);
char *intToStr15Bin(int n);
bool hasClosingParentesis(char *str);

char *getFirstWord(char *str);
char *getWord(char *str, int nword);

// Precondition: string instruction and char target
// Postcondition: returns the position of the unique char target
// gives negative number in case of error
// -1 = Not FOund
// -2 = Found double or more
int getCharPosition(char *instruction, char target);