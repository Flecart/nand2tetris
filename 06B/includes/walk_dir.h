#pragma once
typedef struct list_tmp {
    char *name;
    struct list_tmp *next;
} List_t;

typedef List_t *List;


List walk_dir(char dirName[]);
List initList();
void addToList(List *list, char *name);
void freeList(List *list);
