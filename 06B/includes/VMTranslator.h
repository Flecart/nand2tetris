#pragma once 
#include <stdio.h>
#include <stdlib.h>

#include "walk_dir.h"
#include "file_parser.h"
#include "utils.h"
#include "compiler.h"

#include "globals.h"
#define false 0
#define true 1

void handleFile(char *argv[]);
void handleDirectory(List dirs, char *dir);