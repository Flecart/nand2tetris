#include <string.h>
#include <stdlib.h>
#include "utils.h"

#define false 0
#define true 1
#define bool short

char* strip(char *string) {
    char *ans = string;
    int i = 0;
    int len = strlen(string);
    // left strip
    while (string[i] <= 32 && i < len){
        ans++;
        i += 1;
    }

    // right strip
    i = strlen(string) - 1;
    while(string[i] <= 32 && i >= 0){
        string[i] = '\0';
        i -= 1;
    }
    return ans;
}

int strToInt(char *str) {
    int len = strlen(str);
    int ans = 0, base = 1;
    for(int i = len - 1; i >= 0; i--) {
        int numero = str[i] - '0';
        ans += base * numero;
        base = base * 10;
    }
    return ans;
}

bool strIsNumber(char *str) {
    bool isNumber = true;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        int n = str[i] - '0';
        if (n < 0 || n > 9) {
            isNumber = false;
            break;
        }
    }
    return isNumber;
}

char *intToStr15Bin(int n) {
    char *and = malloc(16);
    and[15] = '\0';
    for (int i = 14; i >= 0; i--) {
        int bin = n & 1;
        n = n >> 1;
        and[i] = bin + '0';
    }
    return and;
}

bool hasClosingParentesis(char *str) {
    bool hasFirstParentesis = false;
    bool hasSecondParentesis = false;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '(') hasFirstParentesis = true;
        if (str[i] == ')') hasSecondParentesis = true;
    }

    return hasSecondParentesis && hasSecondParentesis;
} 