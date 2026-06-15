#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palavras.h"
#define PALAVRAS_H
#define MAX_PALAVRAS 1000


Trie_Palavras *criarNo() {
   Trie_Palavras *novoNo = malloc(sizeof(Trie_Palavras));

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
void converterParaMaiusculas(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - ('a' - 'A');
        }
    }
}
void converterParaMinusculas(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + ('a' - 'A');
        }
   }
} 

void validarPalavra(char *palavra) {
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (palavra[i] < 'A' || palavra[i] > 'Z') {
            printf("Palavra inválida. Use apenas letras maiúsculas.\n");
            exit(1);
        }
    }
}
void inserirPalavra(Trie_Palavras *raiz,char palavra[],int id){
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
            return 0;
        }
        atual = atual->filhos[indice];
    }
    if (atual->fimPalavra) {
        *idEncontrado = atual->ID_palavra; // Palavra encontrada, retorna o ID
        return 1;
    } else {
        *idEncontrado = -1; // Palavra não encontrada
        return 0;
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

void consultarPalavra(Palavra palavras[], int numPalavras, Trie_Palavras *raiz) {
    char palavra[50];
    printf("Digite a palavra que deseja consultar: ");
    scanf("%s", palavra);

    int idEncontrado;
    pesquisarPalavra(raiz, palavra, &idEncontrado);

    if (idEncontrado != -1) {
        Palavra *palavraEncontrada = buscarPalavraPorID(palavras, numPalavras, idEncontrado);
        if (palavraEncontrada != NULL) {
            printf("Palavra: %s\n", palavraEncontrada->palavra);
            printf("Significado: %s\n", palavraEncontrada->significado);
            printf("Contexto: %s\n", palavraEncontrada->contexto);
            printf("Categoria: %s\n", palavraEncontrada->categoria);
            printf("Palavras Relacionadas:\n");
            for (int i = 0; i < palavraEncontrada->numero_de_relacionadas; i++) {
                printf("- %s\n", palavraEncontrada->relacionadas[i]);
            }
        } else {
            printf("Erro ao buscar a palavra por ID.\n");
        }
    } else {
        printf("Palavra não encontrada.\n");
    }
}
void removerPalavra(Trie_Palavras *raiz, char palavra[]) {
    Trie_Palavras *atual = raiz;
    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'A';
        if (atual->filhos[indice] == NULL) {
            printf("Palavra não encontrada. Não é possível remover.\n");
            return;
        }
        atual = atual->filhos[indice];
    }
    if (atual->fimPalavra) {
        atual->fimPalavra = 0; // Marca a palavra como não existente
        printf("Palavra removida com sucesso.\n");
    } else {
        printf("Palavra não encontrada. Não é possível remover.\n");
    }
}

void liberarTrie(Trie_Palavras *raiz) {
    if (raiz == NULL) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        liberarTrie(raiz->filhos[i]);
    }
    free(raiz);
}
void liberarPalavras(Palavra *palavras, int numPalavras) {
    free(palavras);
}
void liberarMemoria(Trie_Palavras *raiz, Palavra *palavras, int numPalavras) {
    liberarTrie(raiz);
    liberarPalavras(palavras, numPalavras);
}