#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palavras.h"
#define PALAVRAS_H
#define MAX_PALAVRAS 1000


    Trie_Palavras *criarNo() {
    Trie_Palavras *novoNo;
        (Trie_Palavras *) malloc(sizeof(Trie_Palavras));

    if (novoNo == NULL) {
        return NULL;
    }

    for (int i = 0; i < 26; i++) {
        novoNo->filhos[i] = NULL;
    }
    novoNo->fimPalavra = 0;
    novoNo->ID_palavra = -1;
    return novoNo;
}

void inserirPalavra(Trie_Palavras *raiz,char palavra[],int id)
{
    Trie_Palavras *atual = raiz;
    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'A';
        if (atual->filhos[indice] == NULL) {
            atual->filhos[indice] = criarNo();
        }
        atual = atual->filhos[indice];
    }
    atual->fimPalavra = 1;
    atual->ID_palavra = id;
}

int pesquisarPalavra(Trie_Palavras *raiz, char palavra[], int *idEncontrado) {
    Trie_Palavras *atual = raiz;
    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'A';
        if (atual->filhos[indice] == NULL) {
            *idEncontrado = -1; // Palavra não encontrada
            return;
        }
        atual = atual->filhos[indice];
    }
    if (atual->fimPalavra) {
        *idEncontrado = atual->ID_palavra; // Palavra encontrada, retorna o ID
    } else {
        *idEncontrado = -1; // Palavra não encontrada
    }
}

Palavra* buscarPalavraPorID(Palavra palavras[], int numPalavras, int id) {
    for (int i = 0; i < numPalavras; i++) {
        if (palavras[i].id == id) {
            return &palavras[i]; // Retorna o ponteiro para a palavra encontrada
        }
    }
    return NULL; // Palavra não encontrada
}