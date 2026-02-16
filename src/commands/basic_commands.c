#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>

#include "commands.h"

// ===== BASICOS =====
int cmd_salir(int argc, char **argv);
int cmd_ayuda(int argc, char **argv);
int cmd_tiempo(int argc, char **argv);
int cmd_listar(int argc, char **argv);
int cmd_leer(int argc, char **argv);
int cmd_calc(int argc, char **argv);

// ===== SISTEMA =====
int cmd_directorio(int argc, char **argv);
int cmd_historial(int argc, char **argv);

// ===== AVANZADOS =====
int cmd_copiar(int argc, char **argv);
int cmd_mover(int argc, char **argv);
int cmd_wc(int argc, char **argv);

command_t commands[] = {
    // ---- Basicos ----
    {"salir", cmd_salir, "Salir de la shell"},
    {"ayuda", cmd_ayuda, "Lista comandos"},
    {"tiempo", cmd_tiempo, "Fecha y hora"},
    {"listar", cmd_listar, "Lista directorio"},
    {"leer", cmd_leer, "Muestra contenido de un archivo"},
    {"calc", cmd_calc, "Calculadora basica"},

    // ---- Sistema ----
    {"directorio", cmd_directorio, "Muestra ruta actual"},
    {"historial", cmd_historial, "Ultimos 10 comandos"},

    // ---- Avanzados ----
    {"copiar", cmd_copiar, "Copia un archivo"},
    {"mover", cmd_mover, "Mueve un archivo"},
    {"wc", cmd_wc, "Cuenta lineas/palabras/caracteres"},

    {NULL, NULL, NULL}
};


// ==================

int cmd_salir(int argc, char **argv) {
    (void)argc;
    (void)argv;
    exit(0);
}

int cmd_ayuda(int argc, char **argv) {
    (void)argc;
    (void)argv;

    for (int i = 0; commands[i].name; i++)
        printf("%s - %s\n", commands[i].name, commands[i].help);

    return 0;
}

int cmd_tiempo(int argc, char **argv) {
    (void)argc;
    (void)argv;

    time_t t = time(NULL);
    printf("%s", ctime(&t));
    return 0;
}

int cmd_listar(int argc, char **argv) {
    (void)argc;
    (void)argv;

    DIR *d = opendir(".");
    if (!d) {
        perror("opendir");
        return 1;
    }

    struct dirent *ent;
    while ((ent = readdir(d)) != NULL)
        printf("%s  ", ent->d_name);

    printf("\n");
    closedir(d);
    return 0;
}

int cmd_leer(int argc, char **argv) {
    if (argc < 2) {
        printf("Uso: leer <archivo>\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("leer");
        return 1;
    }

    char buffer[512];
    while (fgets(buffer, sizeof(buffer), f))
        fputs(buffer, stdout);

    fclose(f);
    return 0;
}

int cmd_calc(int argc, char **argv) {
    if (argc != 4) {
        printf("Uso: calc <num1> <operador> <num2>\n");
        return 1;
    }

    double a = atof(argv[1]);
    double b = atof(argv[3]);
    char op = argv[2][0];

    double result = 0;

    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/':
            if (b == 0) {
                printf("Error: division por cero\n");
                return 1;
            }
            result = a / b;
            break;
        default:
            printf("Operador invalido: %c\n", op);
            return 1;
    }

    printf("Resultado: %.2f\n", result);
    return 0;
}
