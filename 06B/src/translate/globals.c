
#include "globals.h"

const char G_addToStack[] = ""
    "("ADD_TO_STACK")\n"
    "@SP\n"
    "A=M\n"
    "M=D\n"
    "@SP\n"
    "M=M+1\n"
    "@"RETURN_LABEL"\n"
    "0;JMP\n";

const char G_return[] = ""
    "("RETURN_LABEL")\n"
    "@R13\n"
    "D=M\n"
    "D;JMP\n";

const char G_segment_push[] = ""
    "("LCL_PUSH")\n"
    "@LCL\n"
    "D=M\n"
    "@"G_SEG_PUSH"\n"
    "0;JMP\n"
    "("ARG_PUSH")\n"
    "@ARG\n"
    "D=M\n"
    "@"G_SEG_PUSH"\n"
    "0;JMP\n"
    "("THIS_PUSH")\n"
    "@THIS\n"
    "D=M\n"
    "@"G_SEG_PUSH"\n"
    "0;JMP\n"
    "("THAT_PUSH")\n"
    "@THAT\n"
    "D=M\n"
    "@"G_SEG_PUSH"\n"
    "0;JMP\n"
    "("G_SEG_PUSH")\n"
    "@R14\n"
    "A=D+M\n"
    "D=M\n"
    "@"ADD_TO_STACK"\n"
    "0;JMP\n";

// used
const char G_funcDeclaration[] = ""
    "("FUNCTION_DECLARATION")\n"
    "@R14\n"     
    "(FUNCTION_DECLARATION_LOOP)\n"
    "@R14\n"    // JUMP TO END IF R14 == 0
    "D=M\n"
    "@"RETURN_LABEL"\n"
    "D;JEQ\n"
    "@0\n" // PUSH CONSTANT 0
    "D=A\n"
    "@SP\n"
    "A=M\n"
    "M=D\n"
    "@SP\n"
    "M=M+1\n" 
    "@R14\n" // R14 --
    "M=M-1\n"
    "@FUNCTION_DECLARATION_LOOP\n"
    "0;JMP\n";

// used
const char G_funcReturn[] = ""
    "("RETURN_FUNCTION")\n"
    "@LCL\n" // FRAME = LCL
    "D=M\n"
    "@R13\n"
    "M=D\n"
    //  RET = *(FRAME -5)
    "@R13\n" // D=*(FRAME - 5)
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
    "@R13\n" // D=*(FRAME - 5)
    "D=M\n"
    "@1\n"
    "AD=D-A\n"
    "D=M\n"
    "@THAT\n" // REGNAME = D
    "M=D\n"
     // THIS = *(FRAME - 2)
    "@R13\n" // D=*(FRAME - 5)
    "D=M\n"
    "@2\n"
    "AD=D-A\n"
    "D=M\n"
    "@THIS\n" // REGNAME = D
    "M=D\n"
    // ARG  = *(FRAME - 3)
    "@R13\n" // D=*(FRAME - 5)
    "D=M\n"
    "@3\n"
    "AD=D-A\n"
    "D=M\n"
    "@ARG\n" // REGNAME = D
    "M=D\n"
    // LCL  = *(FRAME - 4)
    "@R13\n" // D=*(FRAME - 5)
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

const char G_funcCall[] = ""
    "("FUNCTION_CALL")\n"
    "@R13\n"
    "M=D\n"

    "@R14\n"
    "D=M\n"
    "@SP\n" // add to stack
    "M=M+1\n"
    "A=M-1\n"
    "M=D\n"

    "@LCL\n"
    "D=M\n"
    "@SP\n" // add to stack
    "M=M+1\n"
    "A=M-1\n"
    "M=D\n"
    
    "@ARG\n"
    "D=M\n"
    "@SP\n" // add to stack
    "M=M+1\n"
    "A=M-1\n"
    "M=D\n"
    
    "@THIS\n"
    "D=M\n"
    "@SP\n" // add to stack
    "M=M+1\n"
    "A=M-1\n"
    "M=D\n"
    
    "@THAT\n"
    "D=M\n"
    "@SP\n" // add to stack
    "M=M+1\n"
    "A=M-1\n"
    "M=D\n"

    "@SP\n"
    "D=M\n"
    "@LCL\n"
    "M=D\n"
    "@"RETURN_LABEL"\n"
    "0;JMP\n";