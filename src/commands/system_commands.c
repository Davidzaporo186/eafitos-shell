#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#include "commands.h"

// ===== DIRECTORIO =====
int cmd_directorio(int argc, char **argv) {
    (void)argc;
    (void)argv;

    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
        return 0;
    }

    perror("directorio");
    return 1;
}

// ===== HISTORIAL =====
extern char history[10][256];
extern int history_count;

int cmd_historial(int argc, char **argv) {
    (void)argc;
    (void)argv;

    int start = history_count > 10 ? history_count - 10 : 0;

    for (int i = start; i < history_count; i++) {
        printf("%d: %s", i + 1, history[i % 10]);
    }

    return 0;
}
