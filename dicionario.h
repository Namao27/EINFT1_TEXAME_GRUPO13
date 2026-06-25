#ifndef DICIONARIO_H
#define DICIONARIO_H

#include "tipos.h"

extern Conceito dicionario[MAX];
extern int total;

void inserirPalavra();
void listarPalavras();
void pesquisarPalavra();
void atualizarPalavra();
void removerPalavra();
int indiceValido(int i);

#endif