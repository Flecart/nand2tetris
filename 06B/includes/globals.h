#pragma once 
#include <string.h>

// All constant in this filewill be named with G_
// so they can be read by other files and I know where they came from

// In this section of the program we will write some lines of code that are called many times
// So i don 't have to write them everysingle time
// And thus being more efficient.


// R13 for return address
#define RETURN_LABEL "RETURN_LABEL"

// D has the value to add to the stack
// R13 the return
#define ADD_TO_STACK "ADD_TO_STACK"

// R14 offset, R13 return addr
// Call these to push to standard registers
#define LCL_PUSH "LCL_PUSH"
#define ARG_PUSH "ARG_PUSH"
#define THIS_PUSH "THIS_PUSH"
#define THAT_PUSH "THAT_PUSH"

// Pushes to the address pointed by
// D + R14
// Helper for the register push
#define G_SEG_PUSH "G_SEG_PUSH"

// r14 has number of 0 to push
// r13 the return address
#define FUNCTION_DECLARATION "FUNTION_DECLARATION"

// D return address
// r14 address to push
#define FUNCTION_CALL "FUNCTION_CALL"

// The return of the function is always the same code
#define RETURN_FUNCTION "RETURN_FUNCTION"
