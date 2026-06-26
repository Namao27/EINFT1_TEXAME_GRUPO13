#ifndef GRAFO_H
#define GRAFO_H

#include "palavras.h"

// nó da lista de adjacência
typedef struct No {
    int destino;
    struct No *prox;
} No;

// grafo
typedef struct {
    int numVertices;
    No *lista[1000];
} Grafo;

// funções
void inicializarGrafo(Grafo *g, int vertices);
void adicionarRelacao(Grafo *g, int origem, int destino);
void mostrarRelacoes(Grafo *g, int indice, Palavra palavras[], int numPalavras);
void removerRelacao(Grafo *g, int origem, int destino);

int indiceValido(int i, int max);

#endif
