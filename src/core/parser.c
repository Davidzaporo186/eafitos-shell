#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define MAX_TOKENS 64

char **parse_input(char *line, int *argc) {
    char **tokens = malloc(sizeof(char*) * MAX_TOKENS);
    *argc = 0;

    char *token = strtok(line, " \t\n");
    while (token && *argc < MAX_TOKENS - 1) {
        tokens[*argc] = strdup(token);
        (*argc)++;
        token = strtok(NULL, " \t\n");
    }

    tokens[*argc] = NULL;
    return tokens;
}

void free_args(char **args) {
    if (!args) return;

    for (int i = 0; args[i]; i++)
        free(args[i]);

    free(args);
}
