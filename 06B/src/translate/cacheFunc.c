#include "cacheFunc.h"

Cache updateCache(Cache g_cache, char funcName[], int numArgs) {
    Cache cache = (Cache) malloc(sizeof(Cache_t));
    cache->n_var = numArgs;
    char *name = (char *) malloc(sizeof(char) * (strlen(funcName) + 1));
    strcpy(name, funcName);
    cache->name = name;
    cache->next = g_cache;
    return cache;
}

Cache searchCache(Cache cache, char funcName[], int numArgs) {
    if (cache == NULL) return NULL;
    bool found = false;
    Cache foundCache = NULL;
    while (!found && cache != NULL) {
        if(strcmp(funcName, cache->name) == 0 && cache->n_var == numArgs) {
            found = true;
            foundCache = cache;
        }
        cache = cache->next;
    }
    return foundCache;
}

void freeCache(Cache cache) {
    if (cache == NULL) return;
    Cache next = cache; 
    do
    {
        cache = next->next;
        free(next->name);
        free(next);
        next = cache;
    } while (next->next != NULL);
    free(next); // nobody has freed the last next!
    return;
}