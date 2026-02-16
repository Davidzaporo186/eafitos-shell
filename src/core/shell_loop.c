#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"
#include "parser.h"
#include "commands.h"

#define PROMPT "eafitos$ "
#define HISTORY_SIZE 10

char history[HISTORY_SIZE][256];
int history_count = 0;

void shell_loop(void) {
    char *line = NULL;
    size_t len = 0;

    while (1) {
        printf(PROMPT);
        fflush(stdout);

        if (getline(&line, &len, stdin) == -1) {
            printf("\n");
            break;
        }

        // guardar historial
        if (strlen(line) > 1) {
            strncpy(history[history_count % HISTORY_SIZE], line, 255);
            history[history_count % HISTORY_SIZE][255] = '\0';
            history_count++;
        }

        int argc = 0;
        char **argv = parse_input(line, &argc);

        if (argc == 0) {
            free_args(argv);
            continue;
        }

        int found = 0;
        for (int i = 0; commands[i].name != NULL; i++) {
            if (strcmp(argv[0], commands[i].name) == 0) {
                commands[i].func(argc, argv);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Comando no reconocido: %s\n", argv[0]);
        }

        free_args(argv);
    }

    free(line);
}
