#include <dirent.h> 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../includes/walk_dir.h"

List walk_dir(char dirName[]) {
    DIR *dir;
    struct dirent *file;
    List list = initList();
    dir = opendir(dirName);
    if (dir) {
        while ((file = readdir(dir)) != NULL) {
            addToList(&list, file->d_name);
        }
        closedir(dir);
    }

    return list;
}

List initList() {
    List newNode = (List) malloc(sizeof(List_t));
    newNode->name = NULL;
    newNode->next = NULL;
    return newNode; 
}

void addToList(List *list, char *name) {
    int len = strlen(name);
    List newNode = (List) malloc(sizeof(List_t));
    char *string = (char *) malloc(len + 1);
    strcpy(string, name);
    newNode->name = string;
    newNode->name[len] = '\0';
    newNode->next = *list;

    *list = newNode;
}

void freeList(List *list) {
    List next = *list; 
    do
    {
        *list = next->next;
        free(next->name);
        free(next);
        next = *list;
    } while (next->next != NULL);
    free(next); // nobody has freed the last next!
    return;
}