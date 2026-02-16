#ifndef COMMANDS_H
#define COMMANDS_H

typedef int (*cmd_func)(int argc, char **argv);

typedef struct {
    const char *name;
    cmd_func func;
    const char *help;
} command_t;

extern command_t commands[];

#endif
