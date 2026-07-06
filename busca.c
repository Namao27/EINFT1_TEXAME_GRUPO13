gi#include "busca.h"
#include <string.h>

int buscaBinaria(Palavra vetor[], int tamanho, char palavra[]) {
    int inicio = 0;
    int fim    = tamanho - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        int cmp = strcmp(vetor[meio].palavra, palavra);

        if (cmp == 0) {
            return meio;   // encontrou — retorna o índice
        } else if (cmp < 0) {
            inicio = meio + 1;  // palavra está na metade direita
        } else {
            fim = meio - 1;     // palavra está na metade esquerda
        }
    }

    return -1;  // não encontrou
}