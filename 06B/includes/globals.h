#pragma once 
#include <string.h>
#include <stdio.h>
// All constant in this filewill be named with G_
// so they can be read by other files and I know where they came from

// In this section of the program we will write some lines of code that are called many times
// So i don 't have to write them everysingle time
// And thus being more efficient.


// R13 for return address
#define RETURN_LABEL "RETURN_LABEL"

// D return address
// r14 address to push
#define FUNCTION_CALL "FUNCTION_CALL"
// The range of the calls that are hardcoded
// e.g. 0-FUNCTION_RANGE
#define FUNCTION_RANGE 6

// The return of the function is always the same code
#define RETURN_FUNCTION "RETURN_FUNCTION"


// ALL JUMPS HAVE RETURN ADDRESS IN R13
#define JUMP_EQUAL "JUMP_EQUAL"
#define JUMP_GREATER "JUMP_GREATER"
#define JUMP_LESS "JUMP_LESS"

// Writes the hardcoded global stuff into the file
void write_globals(FILE *writeFilePtr);