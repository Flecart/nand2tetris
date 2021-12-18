#pragma once

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define bool short
#define false 0
#define true 1

typedef struct cache_tmp {
    char *name;
    int n_var;
    struct cache_tmp *next;
} Cache_t;

typedef Cache_t *Cache;

void freeCache(Cache cache);
Cache updateCache(Cache g_cache, char funcName[], int numArgs);
Cache searchCache(Cache cache, char funcName[], int numArgs);