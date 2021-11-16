#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stackAritmetic.h"
#include "programFlow.h"
#include "functions.h"

#include "file_parser.h"
#include "utils.h"

#define bool short
#define false 0
#define true 1

// Gets filename without extension
void compile(FILE *readFilePointer, FILE *writeFilePointer, char *filename);