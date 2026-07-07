#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALFABETO 26

// ── Estrutura do nó ──────────────────────────────────────────────────────────
typedef struct NoTrie {
    struct NoTrie *filhos[ALFABETO];
    int fimDePalavra;
} NoTrie;

// ── Raiz global ──────────────────────────────────────────────────────────────
static NoTrie *raiz = NULL;

// ── Funções internas (privadas) ──────────────────────────────────────────────

// Cria um novo nó inicializado
static NoTrie *criarNo() {
    NoTrie *no = (NoTrie *)malloc(sizeof(NoTrie));
    if (no == NULL) {
        printf("Erro: memoria insuficiente.\n");
        return NULL;
    }
    no->fimDePalavra = 0;
    for (int i = 0; i < ALFABETO; i++) {
        no->filhos[i] = NULL;
    }
    return no;
}

// Converte letra para índice 0-25
static int letraParaIndice(char c) {
    return tolower(c) - 'a';
}

// DFS — percorre a trie a partir de um nó e imprime as palavras
static void dfs(NoTrie *no, char buffer[], int nivel) {
    if (no == NULL) return;

    if (no->fimDePalavra) {
        buffer[nivel] = '\0';
        printf("  → %s\n", buffer);
    }

    for (int i = 0; i < ALFABETO; i++) {
        if (no->filhos[i] != NULL) {
            buffer[nivel] = 'a' + i;
            dfs(no->filhos[i], buffer, nivel + 1);
        }
    }
}

// ── Funções públicas ─────────────────────────────────────────────────────────

// Inicializa a raiz (chamar no início do programa)
void inicializarTrie() {
    raiz = criarNo();
}

// Insere uma palavra na Trie
void inserirTrie(char palavra[]) {
    if (raiz == NULL) inicializarTrie();

    NoTrie *atual = raiz;

    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = letraParaIndice(palavra[i]);

        // Se o caminho não existe, cria
        if (atual->filhos[indice] == NULL) {
            atual->filhos[indice] = criarNo();
        }
        atual = atual->filhos[indice];
    }

    atual->fimDePalavra = 1;  // marca o fim da palavra
}

// Pesquisa por prefixo e guarda o nó onde o prefixo termina
static NoTrie *navegarPrefixo(char prefixo[]) {
    NoTrie *atual = raiz;

    for (int i = 0; prefixo[i] != '\0'; i++) {
        int indice = letraParaIndice(prefixo[i]);

        if (atual->filhos[indice] == NULL) {
            return NULL;  // prefixo não existe
        }
        atual = atual->filhos[indice];
    }

    return atual;  // retorna o nó onde o prefixo termina
}

// Mostra sugestões com base no último prefixo pesquisado
void listarSugestoes() {
    // Chamada internamente por pesquisarPrefixo
    // Pode também ser chamada isoladamente se necessário
    printf("(use pesquisarPrefixo para ver sugestoes)\n");
}

// Pesquisa por prefixo e lista todas as sugestões
void pesquisarPrefixo(char prefixo[]) {
    if (raiz == NULL) {
        printf("Trie vazia.\n");
        return;
    }

    NoTrie *noPrefixo = navegarPrefixo(prefixo);

    if (noPrefixo == NULL) {
        printf("Nenhuma sugestao encontrada para \"%s\".\n", prefixo);
        return;
    }

    printf("Sugestoes para \"%s\":\n", prefixo);

    // Buffer para construir as palavras durante o DFS
    char buffer[100];

    // Copia o prefixo para o buffer
    strcpy(buffer, prefixo);
    int nivel = strlen(prefixo);

    // Se o próprio prefixo é uma palavra
    if (noPrefixo->fimDePalavra) {
        printf("  → %s\n", prefixo);
    }

    // Percorre a partir do nó do prefixo
    dfs(noPrefixo, buffer, nivel);
}

// Liberta toda a memória da Trie
/*void liberarTrie(NoTrie *no) {
    if (no == NULL) return;
    for (int i = 0; i < ALFABETO; i++) {
        liberarTrie(no->filhos[i]);
    }
    free(no);
}*/