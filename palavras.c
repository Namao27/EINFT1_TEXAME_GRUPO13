#include <stdio.h>
#include <stdlib.h>
#define PALAVRAS_H
#define MAX_PALAVRAS 1000

int main() {



Triee *raiz = criarTrie();

Triee *criarTrie() {
    Triee *novoNo = (Triee *)malloc(sizeof(Triee));
   if (novoNo == NULL) {
        return NULL; // Falha na alocação de memória
    }
    for (int i = 0; i < 26; i++) {
        novoNo->filhos[i] = NULL;
    }           
    novoNo->fimPalavra = 0;
    novoNo->ID_palavra = -1;
    return novoNo;

}}

void inserirPalavra(Triee *raiz, char palavra[], int id) {
    Triee *atual = raiz;
    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'a';
        if (atual->filhos[indice] == NULL) {
            atual->filhos[indice] = criarTrie();
        }
        atual = atual->filhos[indice];
    }
    atual->fimPalavra = 1;
    atual->ID_palavra = id;
}