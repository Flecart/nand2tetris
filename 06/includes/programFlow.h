#pragma once

typedef enum {
    LABEL,
    IF_GOTO,
    GOTO,
    FLOWS_UNKNOWN
} Flows;

Flows getFlows(char *word);

int programFlow(char *line, FILE *writeToPtr);

char *label(char *instruction);
char *if_goto(char *instruction);
char *gotoCommand(char *instruction);