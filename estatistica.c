#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "estatistica.h"

// =========================
// HORA DO SISTEMA
// =========================
void mostrarHora()
{
    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);

    printf("%02d:%02d:%02d\n",
           t->tm_hour,
           t->tm_min,
           t->tm_sec);
}

// =========================
// TOTAL DE PALAVRAS
// =========================
void totalPalavras(Palavra vetor[], int n)
{
    printf("Total de palavras: %d\n", n);
}

// =========================
// TOTAL PESQUISAS 
// =========================
void totalPesquisas(Palavra vetor[], int n)
{
    int total = 0;

    for(int i=0;i<n;i++)
        total += vetor[i].pesquisas;

    printf("Total de pesquisas: %d\n", total);
}

// =========================
// CATEGORIAS (STRING CORRIGIDO)
// =========================
void totalCategorias(Palavra vetor[], int n)
{
    int prog = 0, mat = 0, red = 0, outros = 0;

    for(int i = 0; i < n; i++)
    {
        if(strcmp(vetor[i].categoria, "Programacao") == 0)
            prog++;
        else if(strcmp(vetor[i].categoria, "Matematica") == 0)
            mat++;
        else if(strcmp(vetor[i].categoria, "Redes") == 0)
            red++;
        else
            outros++;
    }

    printf("\nCategorias:\n");
    printf("Programacao: %d\n", prog);
    printf("Matematica : %d\n", mat);
    printf("Redes      : %d\n", red);
    printf("Outros      : %d\n", outros);
}

// =========================
// PALAVRA MAIS LONGA
// =========================
void palavraMaisLonga(Palavra vetor[], int n)
{
    if(n == 0) return;

    int idx = 0;

    for(int i = 1; i < n; i++)
        if(strlen(vetor[i].palavra) > strlen(vetor[idx].palavra))
            idx = i;

    printf("Mais longa: %s\n", vetor[idx].palavra);
}

// =========================
// PALAVRA MAIS CURTA
// =========================
void palavraMaisCurta(Palavra vetor[], int n)
{
    if(n <= 0)
    {
        printf("Mais curta: nenhuma\n");
        return;
    }

    int indice = 0;

    for(int i = 1; i < n; i++)
    {
        if(strlen(vetor[i].palavra) < strlen(vetor[indice].palavra))
        {
            indice = i;
        }
    }

    printf("Mais curta: %s\n", vetor[indice].palavra);
}
// =========================
// PLACEHOLDERS (SEM PESQUISAS)
// =========================
void palavraMaisPesquisada(Palavra vetor[], int n)
{
    if(n==0)
        return;

    int maior=0;

    for(int i=1;i<n;i++)
        if(vetor[i].pesquisas > vetor[maior].pesquisas)
            maior=i;

    printf("Mais pesquisada: %s (%d pesquisas)\n",
           vetor[maior].palavra,
           vetor[maior].pesquisas);
}

void palavrasPoucoPesquisadas(Palavra vetor[], int n)
{
    printf("\nPalavras pouco pesquisadas (1 vez):\n");

    int encontrou = 0;

    for(int i = 0; i < n; i++)
    {
        if(vetor[i].pesquisas == 1)
        {
            printf("- %s (1 pesquisa)\n", vetor[i].palavra);
            encontrou = 1;
        }
    }

    if(!encontrou)
    {
        printf("Nenhuma palavra foi pesquisada apenas 1 vez.\n");
    }
}

void palavraMenosPesquisada(Palavra vetor[], int n)
{
    if(vetor == NULL || n <= 0)
    {
        printf("Menos pesquisada: nenhuma\n");
        return;
    }

    int indice = 0;

    for(int i = 1; i < n; i++)
    {
        if(vetor[i].pesquisas < vetor[indice].pesquisas)
        {
            indice = i;
        }
    }

    printf("Menos pesquisada: %s (%d pesquisas)\n",
           vetor[indice].palavra,
           vetor[indice].pesquisas);
}

void mediaPesquisas(Palavra vetor[], int n)
{
    if(n==0)
        return;

    int total=0;

    for(int i=0;i<n;i++)
        total+=vetor[i].pesquisas;

    printf("Media de pesquisas: %.2f\n",
           (float)total/n);
}

void palavrasNuncaPesquisadas(Palavra vetor[], int n)
{
    printf("\nNunca pesquisadas:\n");

    int encontrou=0;

    for(int i=0;i<n;i++)
    {
        if(vetor[i].pesquisas==0)
        {
            printf("- %s\n",vetor[i].palavra);
            encontrou=1;
        }
    }

    if(!encontrou)
        printf("Nenhuma.\n");
}
void taxaUtilizacao(Palavra vetor[], int n)
{
    if(n==0)
        return;

    int usadas=0;

    for(int i=0;i<n;i++)
        if(vetor[i].pesquisas>0)
            usadas++;

    printf("Taxa de utilizacao: %.2f%%\n",
           (float)usadas*100/n);
}

void top5Palavras(Palavra vetor[], int n)
{
    if(vetor == NULL || n <= 0)
    {
        printf("\nTOP 5: sem dados.\n");
        return;
    }

    Palavra *copia = malloc(n * sizeof(Palavra));

    if(copia == NULL)
    {
        printf("Erro de memoria.\n");
        return;
    }


    for(int i = 0; i < n; i++)
    {
        copia[i] = vetor[i];
    }


    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(copia[j].pesquisas < copia[j+1].pesquisas)
            {
                Palavra temp = copia[j];
                copia[j] = copia[j+1];
                copia[j+1] = temp;
            }
        }
    }


    printf("\nTOP 5 PALAVRAS MAIS PESQUISADAS:\n");

    int limite;

    if(n < 5)
        limite = n;
    else
        limite = 5;


    for(int i = 0; i < limite; i++)
    {
        printf("%dº %s - %d pesquisas\n",
               i+1,
               copia[i].palavra,
               copia[i].pesquisas);
    }


    free(copia);
}

// =========================
// RELATORIO FINAL
// =========================
// =========================
// RELATORIO FINAL
// =========================
void mostrarEstatisticas(Palavra vetor[], int n)
{
    printf("\n========================\n");
    printf("   RELATORIO ESTATISTICO\n");
    printf("========================\n");


    printf("Hora: ");
    mostrarHora();


    printf("\n----------- GERAL -----------\n");

    totalPalavras(vetor, n);

    totalPesquisas(vetor, n);


    printf("\n--------- CATEGORIAS --------\n");

    totalCategorias(vetor, n);


    printf("\n--------- PALAVRAS ----------\n");

    palavraMaisLonga(vetor, n);

    palavraMaisCurta(vetor, n);


    printf("\n--------- PESQUISAS ---------\n");

    palavraMaisPesquisada(vetor, n);

    mediaPesquisas(vetor, n);

    taxaUtilizacao(vetor, n);


    printf("\n------ DESEMPENHO USO -------\n");

    palavrasPoucoPesquisadas(vetor, n);

    palavrasNuncaPesquisadas(vetor, n);


    printf("\n----------- TOP 5 -----------\n");

    top5Palavras(vetor, n);


    printf("========================\n");
}