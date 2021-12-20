#pragma once

typedef enum {
    LABEL,
    IF_GOTO,
    GOTO,
    FLOWS_UNKNOWN
} Flows;

Flows getFlows(char *word);

int programFlow(char *line, char *filename, FILE *writeToPtr);

char *label(char *instruction, char *filename);
char *if_goto(char *instruction, char *filename);
char *gotoCommand(char *instruction, char *filename);