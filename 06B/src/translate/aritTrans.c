// NOTA SULLE FUNZIONI COMP, BIT A BIT
// Tutte le traduzioni delle funzioni contengono molte cose riptetute
// Nella maggior parte cambiano solamente una parola o un segno
// Potresti creare una funzione che cambi questo segno o parola a seconda dell'input
// Dovresti aggiungere altri parametri al printf
// Per lo scope di questo progetto è più semplice tenere traduzioni separate
// Ma fai attenzione allo
#include "aritTrans.h"

// comparison counter: global that counts the 
// eq, lt, gt operations, useful for labels
int COMP_CTR = 0;
int counter_0 = 0;
char *push(char *instr, char *fileName) {
    char *command = getWord(instr, 1);
    char *segment = getWord(instr, 2);
    char *strNumber = getWord(instr, 3);
    if (strcmp(command, "push") != 0 || segment == NULL || strNumber == NULL) {
        free(command);
        free(segment);
        free(strNumber);
        return NULL;
    }

    int number = strToInt(strNumber);
    char formattedStr[MAX_SIZE] = {'\0'};
    char *addToStack = ""
        "@SP\n"
        "M=M+1\n"
        "A=M-1\n"
        "M=D\n";

    // PUSH LCL ARG THIS THAT
    char *segmentTemplate = ""
        "@%s\n"
        "D=M\n"
        "@%d\n"
        "A=D+A\n"
        "D=M\n"
        "%s";
    if (strcmp(segment, "constant") == 0){
        char *format = ""
            "@%d\n"
            "D=A\n"
            "%s";
        sprintf(formattedStr, format, number, addToStack, addToStack);
    } else if (strcmp(segment, "local") == 0) {
        sprintf(formattedStr, segmentTemplate, "LCL", number, addToStack);
    } else if (strcmp(segment, "argument") == 0) {
        sprintf(formattedStr, segmentTemplate, "ARG", number, addToStack);
    } else if (strcmp(segment, "this") == 0) {
        sprintf(formattedStr, segmentTemplate, "THIS", number, addToStack);
    } else if (strcmp(segment, "that") == 0) {
        sprintf(formattedStr, segmentTemplate, "THAT", number, addToStack);
    } else if (strcmp(segment, "static") == 0) {
        char *format = ""
            "@%s.%d\n"
            "D=M\n"
            "%s";

        sprintf(formattedStr, format, fileName, number, addToStack);
    } else if (strcmp(segment, "pointer") == 0) {
        char *format = ""
            "@%s\n"
            "D=M\n"
            "%s";
        char pointer[5];
        if (number == 0) strcpy(pointer, "THIS");
        else strcpy(pointer, "THAT");

        sprintf(formattedStr, format, pointer, addToStack);
    } else if (strcmp(segment, "temp") == 0) {
        char *format = ""
            "@5\n"
            "D=A\n"
            "@%d\n"
            "D=D+A\n"
            "%s";
        sprintf(formattedStr, format, number, addToStack);
    } else {
        printf("Invalid segment %s\n", segment);
        free(command);
        free(segment);
        free(strNumber);
        return NULL;
    }

    free(command);
    free(segment);
    free(strNumber);
    return strInHeap(formattedStr);
}

// 8k solo i segment
// circa 700 pop di segment
char *pop(char *instr, char *fileName) {
    char *command = getWord(instr, 1);
    char *segment = getWord(instr, 2);
    char *strNumber = getWord(instr, 3);
    if (strcmp(command, "pop") != 0 || segment == NULL || strNumber == NULL) {
        free(command);
        free(segment);
        free(strNumber);
        return NULL;
    }
    int number = strToInt(strNumber);

    char formattedStr[MAX_SIZE] = {'\0'};
    // SET THE NEW STACK POINTER AND SAVE THE VALUE TOWRITE TO R13
    char *removeFromStack = ""
        "@SP\n"
        "AM=M-1\n"
        "D=M\n"
        "@R13\n"
        "M=D\n";

    // WRITES *R13 TO THE ADDRESS OF R14
    char *writeSegment = ""
        "@R14\n"
        "M=D\n"
        "@R13\n"
        "D=M\n"
        "@R14\n"
        "A=M\n"
        "M=D\n";

    // PUSH LCL ARG THIS THAT
    char *segmentTemplate = ""
        "%s"
        "@%s\n"
        "D=M\n"
        "@%d\n"
        "D=D+A\n"
        "%s";

    if (strcmp(segment, "local") == 0) {
        sprintf(formattedStr, segmentTemplate, removeFromStack, "LCL", number, writeSegment);
    } else if (strcmp(segment, "argument") == 0) {
        sprintf(formattedStr, segmentTemplate, removeFromStack, "ARG", number, writeSegment);
    } else if (strcmp(segment, "this") == 0) {
        sprintf(formattedStr, segmentTemplate, removeFromStack, "THIS", number, writeSegment);
    } else if (strcmp(segment, "that") == 0) {
        sprintf(formattedStr, segmentTemplate, removeFromStack, "THAT", number, writeSegment);
    } else if (strcmp(segment, "static") == 0) {
        char *format = ""
            "%s"
            "@%s.%d\n"
            "D=A\n"
            "%s";

        sprintf(formattedStr, format, removeFromStack, fileName, number, writeSegment);
    } else if (strcmp(segment, "pointer") == 0) {
        char *format = ""
            "%s"
            "@%s\n"
            "M=D\n";
        char pointer[5];
        if (number == 0) strcpy(pointer, "THIS");
        else strcpy(pointer, "THAT");

        sprintf(formattedStr, format, removeFromStack, pointer);
    } else if (strcmp(segment, "temp") == 0) {
        char *format = ""
            "%s"
            "@5\n"
            "D=A\n"
            "@%d\n"
            "D=D+A\n"
            "%s";
        sprintf(formattedStr, format, removeFromStack, number, writeSegment);
    } else {
        printf("Invalid segment %s\n", segment);
        free(command);
        free(segment);
        free(strNumber);
        return NULL;
    }

    free(command);
    free(segment);
    free(strNumber);

    return strInHeap(formattedStr);
}

char *add(char *instr) {
    char *command = getWord(instr, 1);
    if (strcmp(command, "add") != 0) {
        free(command);
        return NULL;
    }

    char instruction[] = ""
        "@SP\n" //SP -= 1
        "AM=M-1\n" // D= *SP
        "D=M\n"
        "A=A-1\n"  
        "M=M+D\n"; // D += *SP

    free(command);
    return strInHeap(instruction);
}

char *sub(char *instr) {
    char *command = getWord(instr, 1);
    if (strcmp(command, "sub") != 0) {
        free(command);
        return NULL;
    }

    char instruction[] = ""
        "@SP\n" //SP -= 1
        "AM=M-1\n" // D= *SP
        "D=M\n"
        "A=A-1\n"  
        "M=M-D\n"; // D -= *SP

    free(command);
    return strInHeap(instruction);
}

// solo 16 righe con neg
char *neg(char *instr) {
    char *command = getWord(instr, 1);
    if (strcmp(command, "neg") != 0) {
        free(command);
        return NULL;
    }

    char instruction[] = ""
        "@SP\n" //SP -= 1
        "A=M-1\n" // D= *SP
        "M=-M\n"; // *SP = -*SP

    free(command);
    return strInHeap(instruction);
}

// correggi le istruzioni
// Le comparazioni se scritte meglio tolgono circa 3k righe
// BUONO: da ottimizzare
char *eq(char *instr) {
    char *command = getWord(instr, 1);
    if (strcmp(command, "eq") != 0) {
        free(command);
        return NULL;
    }
    char formattedStr[MAX_SIZE] = {'\0'};

    char format[] = ""
        "@SP\n" //SP -= 1
        "AM=M-1\n"
        "D=M\n"
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n" // D = *SP - D
        "D=M-D\n"
        "@COMP_%d\n"
        "D;JNE\n"
        "" // (EQ_%d,\n ma non lo metto perché inutile)
        "@SP\n"
        "A=M\n"
        "M=1\n" // *SP = 1
        "@ENDCOMP_%d\n"
        "0;JMP\n"
        "(COMP_%d)\n" // NOTEQ
        "@SP\n"
        "A=M\n"
        "M=0\n" // *SP = 0
        "(ENDCOMP_%d)\n"
        "@SP\n" //SP += 1
        "M=M+1\n";

    sprintf(formattedStr, format, COMP_CTR, COMP_CTR, COMP_CTR, COMP_CTR);
    COMP_CTR += 1;

    free(command);
    return strInHeap(formattedStr);
}

char *gt(char *instr) {
    char *command = getWord(instr, 1);
    if (strcmp(command, "gt") != 0) {
        free(command);
        return NULL;
    }

    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = ""
        "@SP\n" //SP -= 1
        "AM=M-1\n"
        "D=M\n"
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n" // D = *SP - D
        "D=M-D\n"
        "@COMP_%d\n"
        "D;JLE\n"
        "" // (GT%d,\n ma non lo metto perché inutile)
        "@SP\n"
        "A=M\n"
        "M=1\n" // *SP = 1
        "@ENDCOMP_%d\n"
        "0;JMP\n"
        "(COMP_%d)\n" // NOTJGT = JLE
        "@SP\n"
        "A=M\n"
        "M=0\n" // *SP = 0
        "(ENDCOMP_%d)\n"
        "@SP\n" //SP += 1
        "M=M+1\n";

    sprintf(formattedStr, format, COMP_CTR, COMP_CTR, COMP_CTR, COMP_CTR);
    COMP_CTR += 1;

    free(command);
    return strInHeap(formattedStr);
}

char *lt(char *instr) {
    char *command = getWord(instr, 1);
    if (strcmp(command, "lt") != 0) {
        free(command);
        return NULL;
    }

    char formattedStr[MAX_SIZE] = {'\0'};
    char format[] = ""
        "@SP\n" //SP -= 1
        "AM=M-1\n"
        "D=M\n"
        "@SP\n" //SP -= 1
        "M=M-1\n"
        "A=M\n" // D = *SP - D
        "D=M-D\n"
        "@COMP_%d\n"
        "D;JGE\n"
        "" // (LT_%d,\n ma non lo metto perché inutile)
        "@SP\n"
        "A=M\n"
        "M=1\n" // *SP = 1
        "@ENDCOMP_%d\n"
        "0;JMP\n"
        "(COMP_%d)\n" // NOTLT = JGE
        "@SP\n"
        "A=M\n"
        "M=0\n" // *SP = 0
        "(ENDCOMP_%d)\n"
        "@SP\n" //SP += 1
        "M=M+1\n";

    sprintf(formattedStr, format, COMP_CTR, COMP_CTR, COMP_CTR, COMP_CTR);
    COMP_CTR += 1;

    free(command);
    return strInHeap(formattedStr);
}

char *and(char *instr) {
    char *command = getWord(instr, 1);
    if (strcmp(command, "and") != 0) {
        free(command);
        return NULL;
    }

    char instruction[] = ""
        "@SP\n" //SP -= 1
        "AM=M-1\n" // D= *SP
        "D=M\n"
        "A=A-1\n" // D = D & *SP
        "M=D&M\n";

    free(command);
    return strInHeap(instruction);
}


char *or(char *instr) {
    char *command = getWord(instr, 1);
    if (strcmp(command, "or") != 0) {
        free(command);
        return NULL;
    }

    char instruction[] = ""
        "@SP\n" //SP -= 1
        "AM=M-1\n" // D = *SP
        "D=M\n"
        "A=A-1\n" // D = D | *SP
        "M=D|M\n";  // *SP = D

    free(command);
    return strInHeap(instruction);
}

char *not(char *instr) {
    char *command = getWord(instr, 1);
    if (strcmp(command, "not") != 0) {
        free(command);
        return NULL;
    }

    char instruction[] = ""
        "@SP\n" //SP -= 1
        "A=M-1\n"
        "M=!M\n"; // *SP = *SP

    free(command);
    return strInHeap(instruction);
}