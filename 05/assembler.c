#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define false 0
#define true 1
#define bool short

int strToInt(char *str){
    int len = strlen(str);
    int ans = 0, base = 1;
    for(int i = len - 1; i >= 0; i--) {
        int numero = str[i] - '0';
        ans += base * numero;
        base = base * 10;
    }
    return ans;
}

bool strIsNumber(char *str){
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

void aInstruction(char *number) {
    //    printf("%s hello a instruction!\n", number);
    if (strIsNumber(number)){
        printf("got a number\n");
    } else {
        printf("Not a number \n");
    }
    return;
}

void cInstruction(char *cmd) {
    printf("%s hello c instruction!\n", cmd);
    return;
}

char *strip(char *string) {
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

void label(char *line){};

void jump(char *line){};

void interpret(char *line, int lineNumber){
    line = strip(line);
    if (line[0] == '@') {
        aInstruction(line + 1);
    } else if (line[1] == '='){
        cInstruction(line);
    } else if (line[1] == ';') {
        jump(line);
    } else if (line[0] == '('){
        label(line);
    } else if (line[0] == '\0') {
        // DO nothing, empty line
    } else {
        printf("Istruzione invalida alla riga %d\n", lineNumber);
        printf("Valore primo carattere: %d\n", line[0]);
    }

    return;
}

char* getLine(FILE *filePointer, int strLen){
    char *currLine = malloc(strLen + 1);
    char ch;

    // Copying filepointer so that i can get currLine to heap
    fseek(filePointer, -(strLen + 1), SEEK_CUR); // tiro indietro di + 1
    int comment = 0, endLineIndex;
    bool isComment = false;
    int i = 0;
    while ( (ch = fgetc(filePointer)) != '\n') {
        currLine[i] = ch;
        i += 1;
        
        // Se ci sono due  // di seguito ignora la riga
        if (ch == '/') comment += 1;
        else comment = 0;

        if (comment == 2) {
            isComment = true; // metto endline dopo prima / dei due
            endLineIndex = i - 2;
        }
    }

    // se non ho mai settato endLineIndex la metto per essere la fine. 
    if (!isComment) endLineIndex = i;
    currLine[endLineIndex] = '\0';

    return currLine;
}

int main(int argc, char *argv[]){
    if (argc != 2) {
        printf("Error in command\n");
        printf("[Usage]\n");
        printf("./assembler [filename]\n");
        return 0;
    }

    FILE *filePointer;
    char ch;
    filePointer = fopen(argv[1], "r");
    if (filePointer == NULL) {
        printf("File %s not present\n", argv[1]);
        return 0;
    }

    bool isNewLine = false;
    int lineNumber = 0;
    int strLen = 0;
    while ((ch = fgetc(filePointer)) != EOF){

        if (ch == '\n') {
            isNewLine = true;
            lineNumber += 1;
        } else {
            isNewLine = false;
            strLen += 1;
        }

        if (isNewLine) {
            char *line = getLine(filePointer, strLen);
            strLen = 0;
            interpret(line, lineNumber);
            // printf("Ho trovato nuova riga!\n");
            printf("Stringa di questa riga: %s\n", line);
            free(line);
       }
    }
    return 0;
}
