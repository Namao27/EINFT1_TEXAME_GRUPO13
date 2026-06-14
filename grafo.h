#ifndef GRAFO_H
#define GRAFO_H

#define MAX 100

typedef struct No {
    int destino;
    struct No *prox;
} No;

typedef struct {
    No *lista[MAX];
    int numVertices;
} Grafo;

void inicializarGrafo(Grafo *g, int vertices);

void adicionarRelacao(Grafo *g, int origem, int destino);
void mostrarRelacoes(Grafo *g, int indice);
void removerRelacao(Grafo *g, int origem, int destino);

#endif