#ifndef ESTATISTICA_H
#define ESTATISTICA_H

#include "palavras.h"

void mostrarHora();

void totalPalavras(Palavra vetor[], int n);
void totalPesquisas(Palavra vetor[], int n);
void totalCategorias(Palavra vetor[], int n);

void palavraMaisLonga(Palavra vetor[], int n);
void palavraMaisCurta(Palavra vetor[], int n);

void palavraMaisPesquisada(Palavra vetor[], int n);
void palavraMenosPesquisada(Palavra vetor[], int n);
void palavrasPoucoPesquisadas(Palavra vetor[], int n);

void mediaPesquisas(Palavra vetor[], int n);
void top5Palavras(Palavra vetor[], int n);

void palavrasNuncaPesquisadas(Palavra vetor[], int n);
void taxaUtilizacao(Palavra vetor[], int n);

void barrasCategorias(Palavra vetor[], int n);

void mostrarEstatisticas(Palavra vetor[], int n);


#endif