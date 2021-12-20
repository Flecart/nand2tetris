
#include "globals.h"

const char G_return[] = ""
    "("RETURN_LABEL")\n"
    "@R13\n"
    "A=M\n"
    "0;JMP\n";

// used
const char G_funcReturn[] = ""
    "("RETURN_FUNCTION")\n"
    "@LCL\n" // FRAME = LCL
    "D=M\n"
    "@R13\n"
    "M=D\n"
    //  RET = *(FRAME -5)
    "@R13\n" 
    "D=M\n"
    "@5\n"
    "AD=D-A\n"
    "D=M\n"
    "@R14\n" // REGNAME = D
    "M=D\n"
    
    "@SP\n"  // D = POP()
    "AM=M-1\n"
    "D=M\n"
    "@ARG\n" // *ARG = D
    "A=M\n"
    "M=D\n"
    "@ARG\n" // SP=ARG+1
    "D=M+1\n"
    "@SP\n"
    "M=D\n"
    // THAT = *(FRAME - 1)
    "@R13\n" 
    "D=M\n"
    "@1\n"
    "AD=D-A\n"
    "D=M\n"
    "@THAT\n" // REGNAME = D
    "M=D\n"
     // THIS = *(FRAME - 2)
    "@R13\n" 
    "D=M\n"
    "@2\n"
    "AD=D-A\n"
    "D=M\n"
    "@THIS\n" // REGNAME = D
    "M=D\n"
    // ARG  = *(FRAME - 3)
    "@R13\n" 
    "D=M\n"
    "@3\n"
    "AD=D-A\n"
    "D=M\n"
    "@ARG\n" // REGNAME = D
    "M=D\n"
    // LCL  = *(FRAME - 4)
    "@R13\n" 
    "D=M\n"
    "@4\n"
    "AD=D-A\n"
    "D=M\n"
    "@LCL\n" // REGNAME = D
    "M=D\n"
     // GOTO RET
    "@R14\n"
    "A=M\n"
    "0;JMP\n";

// USED ALL JUMPS
const char G_jumpEq[] = ""
    "("JUMP_EQUAL")\n"
    "@SP\n"
    "AM=M-1\n"
    "D=M\n"
    "A=A-1\n"
    "MD=M-D\n"
    "@$JUMP_EQUAL\n"
    "D;JEQ\n"
    "@$EQUAL_EXIT\n"
    "D=0;JMP\n"
    "($JUMP_EQUAL)\n"
    "D=-1\n"
    "($EQUAL_EXIT)\n"
    "@SP\n"
    "A=M-1\n"
    "M=D\n"
    "@"RETURN_LABEL"\n"
    "0;JMP\n";

const char G_jumpGreater[] = ""
    "("JUMP_GREATER")\n"
    "@SP\n"
    "AM=M-1\n"
    "D=M\n"
    "A=A-1\n"
    "MD=M-D\n"
    "@$JUMP_GREATER\n"
    "D;JGT\n"
    "@$GREATER_EXIT\n"
    "D=0;JMP\n"
    "($JUMP_GREATER)\n"
    "D=-1\n"
    "($GREATER_EXIT)\n"
    "@SP\n"
    "A=M-1\n"
    "M=D\n"
    "@"RETURN_LABEL"\n"
    "0;JMP\n";

const char G_jumpLess[] = ""
    "("JUMP_LESS")\n"
    "@SP\n"
    "AM=M-1\n"
    "D=M\n"
    "A=A-1\n"
    "MD=M-D\n"
    "@$JUMP_LESS\n"
    "D;JLT\n"
    "@$LESS_EXIT\n"
    "D=0;JMP\n"
    "($JUMP_LESS)\n"
    "D=-1\n"
    "($LESS_EXIT)\n"
    "@SP\n"
    "A=M-1\n"
    "M=D\n"
    "@"RETURN_LABEL"\n"
    "0;JMP\n";

// USED
const char G_funcCall[] = ""
    "("FUNCTION_CALL"$%d)\n"
    "@LCL\n"
    "D=M\n"
    "@SP\n"
    "M=M+1\n"
    "A=M-1\n"
    "M=D\n"
    "@ARG\n"
    "D=M\n"
    "@SP\n"
    "M=M+1\n"
    "A=M-1\n"
    "M=D\n"
    "@THIS\n"
    "D=M\n"
    "@SP\n"
    "M=M+1\n"
    "A=M-1\n"
    "M=D\n"
    "@THAT\n"
    "D=M\n"
    "@SP\n"
    "M=M+1\n"
    "A=M-1\n"
    "M=D\n"
    "@SP\n"
    "D=M\n"
    "@LCL\n"
    "M=D\n"
    "@%d\n"
    "D=D-A\n"
    "@ARG\n"
    "M=D\n"
    "@"RETURN_LABEL"\n"
    "0;JMP\n";

void write_globals(FILE *writeFilePtr) {
    fprintf(writeFilePtr, "// START GLOBAL SECTION\n");
    for (int i = 0; i < FUNCTION_RANGE; i++) {
        fprintf(writeFilePtr, G_funcCall, i, i + 5);
    }
    const char *others[] = {G_jumpLess, G_jumpGreater, G_jumpEq, G_funcReturn, G_return};
    for (int i = 0; i < 5; i++) {
        fprintf(writeFilePtr, others[i], ""); // "" per ovviare a questo: warning: format not a string literal and no format arguments
    }
}