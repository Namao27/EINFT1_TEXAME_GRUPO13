#include <stdio.h>
#include <stdlib.h>
#define PALAVRAS_H
#define MAX_PALAVRAS 1000

int main() {



Trie *raiz = criarTrie();

Trie *criarTrie() {
    Trie *novoNo = (Trie *)malloc(sizeof(Trie));
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