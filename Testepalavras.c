#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palavras.h"
#define PALAVRAS_H


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

void sugerirPalavrasPorPrefixo(Trie_Palavras *raiz, char prefixo[]) {
    printf("\n[Sugestoes para '%s']:\n", prefixo);
    printf("Funcionalidade de sugestao por prefixo ainda em desenvolvimento.\n");
}

// Função auxiliar para fazer o "print" recursivo a partir de um nó da Trie
void listarSubArvore(Trie_Palavras *no, char prefixo[], int nivel) {
    if (no == NULL) return;
    
    if (no->fimPalavra) {
        prefixo[nivel] = '\0';
        printf("- %s\n", prefixo);
    }
    
    for (int i = 0; i < 26; i++) {
        if (no->filhos[i] != NULL) {
            prefixo[nivel] = 'A' + i;
            listarSubArvore(no->filhos[i], prefixo, nivel + 1);
        }
    }
}

// A função principal que o main chama
void sugerirPalavrasPorPrefixo(Trie_Palavras *raiz, char prefixo[]) {
    Trie_Palavras *atual = raiz;
    char buffer[100];
    int i;
    
    // 1. Navega na Trie até ao fim do prefixo digitado pelo utilizador
    for (i = 0; prefixo[i] != '\0'; i++) {
        int indice = prefixo[i] - 'A';
        if (atual->filhos[indice] == NULL) {
            printf("\nNao foram encontradas sugestoes para o prefixo '%s'.\n", prefixo);
            return;
        }
        buffer[i] = prefixo[i];
        atual = atual->filhos[indice];
    }
    
    // 2. A partir desse nó, lista recursivamente todas as palavras que continuam dali
    printf("\n--- Sugestoes a partir de '%s' ---\n", prefixo);
    listarSubArvore(atual, buffer, i);
}
void atualizarDadosPalavra(Trie_Palavras *raiz, Palavra palavras[], int numPalavras) {
    char palavra[50];
    printf("Digite a palavra que deseja atualizar: ");
    scanf("%s", palavra);

    // Garante que a busca na Trie funciona convertendo para Maiúsculas
    char palavra_maiuscula[50];
    strcpy(palavra_maiuscula, palavra);
    converterParaMaiusculas(palavra_maiuscula);

    int idEncontrado;
    if (pesquisarPalavra(raiz, palavra_maiuscula, &idEncontrado) && idEncontrado != -1) {
        // Encontra o ponteiro da struct no vetor usando o ID encontrado
        Palavra *p = buscarPalavraPorID(palavras, numPalavras, idEncontrado);
        
        if (p != NULL) {
            printf("\nPalavra encontrada: %s\n", p->palavra);
            printf("Significado atual: %s\n", p->significado);
            
            // Limpar o buffer do teclado antes de ler strings longas
            while (getchar() != '\n'); 

            printf("Digite o NOVO significado: ");
            fgets(p->significado, sizeof(p->significado), stdin);
            p->significado[strcspn(p->significado, "\n")] = '\0'; // Remove o \n

            printf("Digite o NOVO contexto: ");
            fgets(p->contexto, sizeof(p->contexto), stdin);
            p->contexto[strcspn(p->contexto, "\n")] = '\0';

            printf("Dados atualizados com sucesso em memoria!\n");
            printf("Nota: Lembre-se de guardar as alteracoes no arquivo antes de sair.\n");
        } else {
            printf("Erro interno: ID da Trie nao corresponde a nenhuma palavra no vetor.\n");
        }
    } else {
        printf("Palavra nao encontrada na Trie. Impossivel atualizar.\n");
    }
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

void listarPalavras(Trie_Palavras *raiz, char prefixo[], int nivel) {
    if (raiz == NULL) {
        return;
    }
    if (raiz->fimPalavra) {
        prefixo[nivel] = '\0'; // Termina a string do prefixo
        printf("%s\n", prefixo);
    }
    for (int i = 0; i < 26; i++) {
        if (raiz->filhos[i] != NULL) {
            prefixo[nivel] = 'A' + i; // Adiciona a letra ao prefixo
            listarPalavras(raiz->filhos[i], prefixo, nivel + 1);
        }
    }
}

int contarPalavras(Trie_Palavras *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    int contador = 0;
    if (raiz->fimPalavra) {
        contador++;
    }
    for (int i = 0; i < 26; i++) {
        contador += contarPalavras(raiz->filhos[i]);
    }
    return contador;
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

void guardarPalavrasEmArquivo(Palavra palavras[], int numPalavras, const char *inseridas) {
    FILE *arquivo = fopen(inseridas, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    for (int i = 0; i < numPalavras; i++) {
        // Escreve os dados estruturados na mesma linha separados por '|'
        fprintf(arquivo, "%d|%s|%s|%s|%s|", palavras[i].id, palavras[i].palavra, palavras[i].significado, palavras[i].contexto, palavras[i].categoria);
        
        // Escreve as relacionadas separadas por vírgula no final da MESMA linha
        for (int j = 0; j < palavras[i].numero_de_relacionadas; j++) {
            fprintf(arquivo, "%s", palavras[i].relacionadas[j]);
            if (j < palavras[i].numero_de_relacionadas - 1) {
                fprintf(arquivo, ",");
            }
        }
        fprintf(arquivo, "\n"); // Só quebra a linha no fim de TUDO
    }
    fclose(arquivo);
}

int carregarPalavrasDeArquivo(Trie_Palavras *raiz, Palavra palavras[], const char *PalavrasArquivos) {
    FILE *arquivo = fopen(PalavrasArquivos, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 0;
    }
    int numPalavras = 0;
    char linha[1200]; 

    while (fgets(linha, sizeof(linha), arquivo) != NULL && numPalavras < MAX_PALAVRAS) {
        linha[strcspn(linha, "\n")] = '\0'; // Remove o \n do fim

        Palavra p;
        p.numero_de_relacionadas = 0;
        char rel_brutas[500] = "";

        // %d| -> Lê o ID numérico e consome o '|'
        // %[^|]| -> Lê texto até ao '|' e depois consome o '|'
        // %[^\0] -> Na última parte, lê tudo até ao fim da string
        int campos_lidos = sscanf(linha, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\0]",&p.id,p.palavra, p.significado, p.contexto, p.categoria, rel_brutas);

        // Se conseguiu ler pelo menos os 5 campos básicos essenciais
        if (campos_lidos >= 5) {
            
            // --- SEPARAR AS RELACIONADAS (Sem strtok) ---
            // Usamos um varrimento manual simples com um ciclo 'for'
            int idx = 0;
            int palavra_relacionadaAtual = 0; // Índice da palavra relacionada atual
            int indece_doCaractereNaPalavra = 0; // Índice do caractere dentro da palavra relacionada

            while (rel_brutas[idx] != '\0' && palavra_relacionadaAtual < 10) {
                if (rel_brutas[idx] == ',') {
                    p.relacionadas[palavra_relacionadaAtual][indece_doCaractereNaPalavra] = '\0'; // Termina a palavra atual
                    palavra_relacionadaAtual++;                             // Avança para a próxima palavra
                    indece_doCaractereNaPalavra = 0;                           // Reinicia o índice do caractere
                } else {
                    p.relacionadas[palavra_relacionadaAtual][indece_doCaractereNaPalavra] = rel_brutas[idx];
                    indece_doCaractereNaPalavra++;
                }
                idx++;
            }
            if (indece_doCaractereNaPalavra > 0) { 
                p.relacionadas[palavra_relacionadaAtual][indece_doCaractereNaPalavra] = '\0'; // Termina a última palavra relacionada
                palavra_relacionadaAtual++;
            }
            p.numero_de_relacionadas = palavra_relacionadaAtual;

            // Guarda a struct preenchida no teu vetor
            palavras[numPalavras] = p;

            // --- INTEGRAÇÃO COM A TRIE ---
            char chave_trie[50];
            strncpy(chave_trie, p.palavra, 50);
            converterParaMaiusculas(chave_trie);
            
            inserirPalavra(raiz, chave_trie, p.id);

            numPalavras++;
        }
    }
    fclose(arquivo);
    return numPalavras;
}