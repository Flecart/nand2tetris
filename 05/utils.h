#pragma once

#define bool short

char* strip(char *string);
int strToInt(char *str);
bool strIsNumber(char *str);
char *intToStr15Bin(int n);
bool hasClosingParentesis(char *str);
int getCharPosition(char *instruction, char target);