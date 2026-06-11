#ifndef PALAVRA_H
#define PALAVRA_H
#define MAX_PALAVRAS 1000

typedef struct {
    int id;
    char palavra[50];
    char significado[500];
    char contexto[500];
    char relacionadas[10][50];
    int numero_de_relacionadas;
    char categoria[50];
} Palavra;

typedef struct {
    struct Trie*filhos[26];
    int fimPalavra;
    int ID_palavra;
} Triee;

#endif