#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void inicializarGrafo(Grafo *g, int vertices)
{
    g->numVertices = vertices;

    for (int i = 0; i < vertices; i++)
        g->lista[i] = NULL;
}

int indiceValido(int i, int max)
{
    return (i >= 0 && i < max);
}

void adicionarRelacao(Grafo *g, int origem, int destino)
{
    if (!indiceValido(origem, g->numVertices) ||
        !indiceValido(destino, g->numVertices))
    {
        printf("Erro: indice invalido!\n");
        return;
    }

    No *novo = malloc(sizeof(No));
    if (!novo)
    {
        printf("Erro de memoria!\n");
        return;
    }

    novo->destino = destino;
    novo->prox = g->lista[origem];
    g->lista[origem] = novo;
}



void mostrarRelacoes(Grafo *g, int indice, Palavra palavras[], int numPalavras)
{
    if (!indiceValido(indice, g->numVertices))

    {
        printf("Erro: indice invalido!\n");
        return;
    }



    printf("\nRelacoes de: %s\n", palavras[indice].palavra);

    No *aux = g->lista[indice];

    if (aux == NULL)

    {
        printf("Sem relacoes.\n");
        return;
    }

    while (aux != NULL)
    {
        printf("- %s\n", palavras[aux->destino].palavra);
        aux = aux->prox;
    }
}

void removerRelacao(Grafo *g, int origem, int destino)
{
    if (!indiceValido(origem, g->numVertices) ||
        !indiceValido(destino, g->numVertices))
    {
        printf("Erro: indice invalido!\n");
        return;
    }

    No *atual = g->lista[origem];
    No *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->destino == destino)
        {
            if (anterior == NULL)
                g->lista[origem] = atual->prox;
            else
                anterior->prox = atual->prox;

            free(atual);
            printf("Relacao removida!\n");
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("Relacao nao encontrada!\n");
}
