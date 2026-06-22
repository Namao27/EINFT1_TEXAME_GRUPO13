#include <stdio.h>
#include <string.h>
#include "dicionario.h"

Conceito dicionario[MAX];
int total = 0;


#define MAX 100

void inserirPalavra()
{
    printf("\nPalavra: ");
    scanf("%s", dicionario[total].palavra);

    printf("Definicao: ");
    getchar();
    fgets(dicionario[total].definicao, 500, stdin);

    dicionario[total].pesquisas = 0;
    dicionario[total].categoria = 0;

    total++;

    printf("Palavra inserida com sucesso!\n");
}

void listarPalavras()
{
    printf("\n=== DICIONARIO ===\n");

    for(int i = 0; i < total; i++)
    {
        printf("%d. %s\n", i + 1, dicionario[i].palavra);
    }
}

void pesquisarPalavra()
{
    char palavra[50];

    printf("\nPalavra a pesquisar: ");
    scanf("%s", palavra);

    for(int i = 0; i < total; i++)
    {
        if(strcmp(dicionario[i].palavra, palavra) == 0)
        {
            printf("\nEncontrado: %s\n", dicionario[i].palavra);
            printf("Definicao: %s\n", dicionario[i].definicao);

            dicionario[i].pesquisas++;

            return;
        }
    }

    printf("Palavra nao encontrada!\n");
}

void atualizarPalavra()
{
    char palavra[50];

    printf("\nPalavra a atualizar: ");
    scanf("%s", palavra);

    for(int i = 0; i < total; i++)
    {
        if(strcmp(dicionario[i].palavra, palavra) == 0)
        {
            printf("Nova definicao: ");
            getchar();
            fgets(dicionario[i].definicao, 500, stdin);

            printf("Atualizado com sucesso!\n");
            return;
        }
    }

    printf("Palavra nao encontrada!\n");
}

void removerPalavra()
{
    char palavra[50];

    printf("\nPalavra a remover: ");
    scanf("%s", palavra);

    for(int i = 0; i < total; i++)
    {
        if(strcmp(dicionario[i].palavra, palavra) == 0)
        {
            for(int j = i; j < total - 1; j++)
            {
                dicionario[j] = dicionario[j + 1];
            }

            total--;

            printf("Removido com sucesso!\n");
            return;
        }
    }

    printf("Palavra nao encontrada!\n");
}

int indiceValido(int i)
{
    return (i >= 0 && i < total);
}