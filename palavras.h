#ifndef PALAVRA_H
#define PALAVRA_H
#define MAX_PALAVRAS 1000

typedef struct {
    int id;
    char palavra[50];
    char definicao[500];
    char categoria[50];
} Palavra;

#endif