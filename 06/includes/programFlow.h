#pragma once

typedef enum {
    LABEL,
    IF_GOTO,
    GOTO,
    FLOWS_UNKNOWN
} Flows;

Flows getFlows(char *word);

int programFlow(char *line, FILE *writeToPtr);

char *label(char *line);
char *if_goto(char *line);
char *gotoCommand(char *line);