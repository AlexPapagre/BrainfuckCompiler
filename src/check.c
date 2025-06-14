#include "check.h"
#include <stdio.h>
#include <stdlib.h>

#define BF_SIZE 30000
#define BRACKET_MAX 100

static void greater_than(size_t *index) {
    if (*index >= BF_SIZE - 1) {
        fprintf(stderr, "Compilation error: Range error.\n");
        exit(EXIT_FAILURE);
    }

    (*index)++;
}

static void less_than(size_t *index) {
    if (*index <= 0) {
        fprintf(stderr, "Compilation error: Range error.\n");
        exit(EXIT_FAILURE);
    }

    (*index)--;
}

static void open_bracket(int *brackets) {
    if (*brackets >= BRACKET_MAX - 1) {
        fprintf(stderr, "Compilation error: Bracket stack overflow.\n");
        exit(EXIT_FAILURE);
    }

    (*brackets)++;
}

static void close_bracket(int *brackets) {
    if (*brackets <= 0) {
        fprintf(stderr, "Compilation error: Unbalanced brackets.\n");
        exit(EXIT_FAILURE);
    }

    (*brackets)--;
}

static void check_command(char c, int *brackets) {
    static size_t index = 0;

    switch (c) {
        case '>': greater_than(&index); break;
        case '<': less_than(&index); break;
        case '[': open_bracket(brackets); break;
        case ']': close_bracket(brackets); break;
    }
}

void check_bf_code(const char *code) {
    int brackets = 0;

    for (size_t i = 0; code[i] != '\0'; i++) {
        check_command(code[i], &brackets);
    }

    if (brackets != 0) {
        fprintf(stderr, "Compilation error: Unbalanced brackets - %d unmatched '['.\n", brackets);
        exit(EXIT_FAILURE);
    }
}
