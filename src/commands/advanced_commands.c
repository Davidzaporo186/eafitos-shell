#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commands.h"

// ===============================
// PROTOTIPOS
// ===============================
int cmd_copiar(int argc, char **argv);
int cmd_mover(int argc, char **argv);
int cmd_wc(int argc, char **argv);

// ===============================
// COPIAR ARCHIVO
// ===============================
int cmd_copiar(int argc, char **argv) {
    if (argc != 3) {
        printf("Uso: copiar <origen> <destino>\n");
        return 1;
    }

    FILE *src = fopen(argv[1], "rb");
    if (!src) {
        perror("copiar");
        return 1;
    }

    FILE *dst = fopen(argv[2], "wb");
    if (!dst) {
        perror("copiar");
        fclose(src);
        return 1;
    }

    char buffer[4096];
    size_t n;

    while ((n = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, n, dst);
    }

    fclose(src);
    fclose(dst);

    printf("Archivo copiado correctamente.\n");
    return 0;
}

// ===============================
// MOVER ARCHIVO
// ===============================
int cmd_mover(int argc, char **argv) {
    if (argc != 3) {
        printf("Uso: mover <origen> <destino>\n");
        return 1;
    }

    if (rename(argv[1], argv[2]) != 0) {
        perror("mover");
        return 1;
    }

    printf("Archivo movido correctamente.\n");
    return 0;
}

// ===============================
// WC BASICO
// ===============================
int cmd_wc(int argc, char **argv) {
    if (argc != 2) {
        printf("Uso: wc <archivo>\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("wc");
        return 1;
    }

    int c;
    int lines = 0;
    int words = 0;
    int chars = 0;
    int in_word = 0;

    while ((c = fgetc(f)) != EOF) {
        chars++;

        if (c == '\n')
            lines++;

        if (c == ' ' || c == '\n' || c == '\t')
            in_word = 0;
        else if (!in_word) {
            in_word = 1;
            words++;
        }
    }

    fclose(f);

    printf("Lineas: %d  Palabras: %d  Caracteres: %d\n",
           lines, words, chars);

    return 0;
}
