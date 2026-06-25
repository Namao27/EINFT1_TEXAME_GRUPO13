#include <stdio.h>
#include "estatistica.h"

void totalPalavras(Conceito vetor[], int n)
{
    printf("Total de palavras: %d\n", n);
}

void totalCategorias(Conceito vetor[], int n)
{
    int i;
    int programacao = 0, matematica = 0, redes = 0;

    for(i = 0; i < n; i++)
    {
        if(vetor[i].categoria == 1)
            programacao++;
        else if(vetor[i].categoria == 2)
            matematica++;
        else if(vetor[i].categoria == 3)
            redes++;
    }

    printf("\nCategorias:\n");
    printf("Programacao: %d\n", programacao);
    printf("Matematica: %d\n", matematica);
    printf("Redes: %d\n", redes);
}

void categoriaMaisUsada(Conceito vetor[], int n)
{
    int i;
    int prog = 0, mat = 0, red = 0;

    for(i = 0; i < n; i++)
    {
        if(vetor[i].categoria == 1) prog++;
        else if(vetor[i].categoria == 2) mat++;
        else if(vetor[i].categoria == 3) red++;
    }

    printf("\nCategoria mais usada: ");

    if(prog >= mat && prog >= red)
        printf("Programacao\n");
    else if(mat >= prog && mat >= red)
        printf("Matematica\n");
    else
        printf("Redes\n");
}

void mostrarEstatisticas(Conceito vetor[], int n)
{
    int i;

    int maisPesquisada = 0;

    for(i = 1; i < n; i++)
    {
        if(vetor[i].pesquisas > vetor[maisPesquisada].pesquisas)
            maisPesquisada = i;
    }

    printf("\n=== ESTATISTICAS ===\n");
    totalPalavras(vetor, n);
    categoriaMaisUsada(vetor, n);

    printf("Mais pesquisada: %s (%d)\n",
           vetor[maisPesquisada].palavra,
           vetor[maisPesquisada].pesquisas);
}