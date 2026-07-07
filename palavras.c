#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palavras.h"
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
Palavra* buscarPalavraPorID(Palavra palavras[], int numPalavras, int id) {
    for (int i = 0; i < numPalavras; i++) {
        if (palavras[i].id == id) {
            return &palavras[i];
        }
    }
    return NULL;
}
// OPÇÃO 1: Inserir Palavra
void inserirPalavra(Trie_Palavras *raiz, char palavra[], int id) {
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
// OPÇÃO 2: Procurar / Consultar Palavra
int pesquisarPalavra(Trie_Palavras *raiz, char palavra[], int *idEncontrado)
{
    Trie_Palavras *atual = raiz;

    for (int i = 0; palavra[i] != '\0'; i++)
    {
        char letra = palavra[i];

        /* Normalização:
           se estiver em minúscula,
           converte para maiúscula */
        if (letra >= 'a' && letra <= 'z')
        {
            letra = letra - ('a' - 'A');
        }

        /* Validação:
           apenas letras A-Z são aceites */
        if (letra < 'A' || letra > 'Z')
        {
            *idEncontrado = -1;
            return 0;
        }

        int indice = letra - 'A';

        if (atual->filhos[indice] == NULL)
        {
            *idEncontrado = -1;
            return 0;
        }

        atual = atual->filhos[indice];
    }

    if (atual->fimPalavra)
    {
        *idEncontrado = atual->ID_palavra;
        return 1;
    }

    *idEncontrado = -1;
    return 0;
}
void consultarPalavra(Palavra palavras[], int numPalavras, Trie_Palavras *raiz) {
    char palavra[50];

    scanf("%s", palavra);

    int idEncontrado;
    pesquisarPalavra(raiz, palavra, &idEncontrado);

    if (idEncontrado != -1) {

        Palavra *palavraEncontrada = buscarPalavraPorID(palavras, numPalavras, idEncontrado);

        if (palavraEncontrada != NULL) {

            // Conta mais uma pesquisa
            palavraEncontrada->pesquisas++;

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
        printf("Palavra nao encontrada. Nao e Chave.\n");
    }
}
// OPÇÃO 3: Atualizar Palavra
void atualizarDadosPalavra(Trie_Palavras *raiz, Palavra palavras[], int numPalavras) {
    char palavra[50];
    printf("Digite a palavra que deseja atualizar: ");
    scanf("%s", palavra);

    char palavra_maiuscula[50];
    strcpy(palavra_maiuscula, palavra);
    converterParaMaiusculas(palavra_maiuscula);

    int idEncontrado;
    if (pesquisarPalavra(raiz, palavra_maiuscula, &idEncontrado) && idEncontrado != -1) {
        Palavra *p = buscarPalavraPorID(palavras, numPalavras, idEncontrado);
        
        if (p != NULL) {
            printf("\nPalavra encontrada: %s\n", p->palavra);
            printf("Significado atual: %s\n", p->significado);
            
            while (getchar() != '\n'); 

            printf("Digite o NOVO significado: ");
            fgets(p->significado, sizeof(p->significado), stdin);
            p->significado[strcspn(p->significado, "\n")] = '\0';

            printf("Digite o NOVO contexto: ");
            fgets(p->contexto, sizeof(p->contexto), stdin);
            p->contexto[strcspn(p->contexto, "\n")] = '\0';

            printf("Dados Atualidados com sucesso em memoria!\n");
            printf("Nota: Lembre-se de guardar as alteracoes no arquivo antes de sair.\n");
        } else {
            printf("Erro interno: ID da Trie nao corresponde a nenhuma palavra no vetor.\n");
        }
    } else {
        printf("Palavra nao encontrada na Trie. Impossivel atualizar.\n");
    }
}
// OPÇÃO 4: Remover Palavra
void removerPalavra(Trie_Palavras *raiz, char palavra[]) {
    Trie_Palavras *atual = raiz;
    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'A';
        if (atual->filhos[indice] == NULL) {
            printf("Palavra não encontrada. \n Não é possível remover.\n");
            return;
        }
        atual = atual->filhos[indice];
    }
    if (atual->fimPalavra) {
        atual->fimPalavra = 0;
        printf("Palavra  %s removida com sucesso.\n", palavra);
    } else {
        printf("Palavra %s não encontrada. Não é possível remover.\n", palavra);
    }
}
// OPÇÃO 5: Listar Palavras
void listarPalavras(Trie_Palavras *raiz, char prefixo[], int nivel) {
    if (raiz == NULL) {
        return;
    }
    if (raiz->fimPalavra) {
        prefixo[nivel] = '\0';
        printf("%s\n", prefixo);
    }
    for (int i = 0; i < 26; i++) {
        if (raiz->filhos[i] != NULL) {
            prefixo[nivel] = 'A' + i;
            listarPalavras(raiz->filhos[i], prefixo, nivel + 1);
        }
    }
}
// OPÇÃO 6: Sugestões por Prefixo
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

void sugerirPalavrasPorPrefixo(Trie_Palavras *raiz, char prefixo[]) {
    Trie_Palavras *atual = raiz;
    char buffer[100];
    int i;
    
    for (i = 0; prefixo[i] != '\0'; i++) {
        int indice = prefixo[i] - 'A';
        if (atual->filhos[indice] == NULL) {
            printf("\nNao foram encontradas sugestoes para o prefixo '%s'.\n", prefixo);
            return;
        }
        buffer[i] = prefixo[i];
        atual = atual->filhos[indice];
    }
    
    printf("\n--- Sugestoes a partir de '%s' ---\n", prefixo);
    listarSubArvore(atual, buffer, i);
}

// OPÇÃO 7: Guardar Alterações (Ficheiro)
void guardarPalavrasEmArquivo(Palavra palavras[], int numPalavras, const char *inseridas) {
    FILE *arquivo = fopen(inseridas, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    for (int i = 0; i < numPalavras; i++) {
        fprintf(arquivo, "%d|%s|%s|%s|%s|", palavras[i].id, palavras[i].palavra, palavras[i].significado, palavras[i].contexto, palavras[i].categoria);
        
        for (int j = 0; j < palavras[i].numero_de_relacionadas; j++) {
            fprintf(arquivo, "%s", palavras[i].relacionadas[j]);
            if (j < palavras[i].numero_de_relacionadas - 1) {
                fprintf(arquivo, ",");
            }
        }
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);
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


// 3. FLUXO AUTOMÁTICO E DESALOCAÇÃO DE MEMÓRIA


int carregarPalavrasDeArquivo(Trie_Palavras *raiz, Palavra palavras[], const char *PalavrasArquivos) {
    FILE *arquivo = fopen(PalavrasArquivos, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 0;
    }
    int numPalavras = 0;
    char linha[1200]; 

    while (fgets(linha, sizeof(linha), arquivo) != NULL && numPalavras < MAX_PALAVRAS) {
        linha[strcspn(linha, "\n")] = '\0';

        Palavra p;
        p.numero_de_relacionadas = 0;
        char rel_brutas[500] = "";

        int campos_lidos = sscanf(linha, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\0]", &p.id, p.palavra, p.significado, p.contexto, p.categoria, rel_brutas);

        if (campos_lidos >= 5) {
            int idx = 0;
            int palavra_relacionadaAtual = 0; 
            int indece_doCaractereNaPalavra = 0; 

            while (rel_brutas[idx] != '\0' && palavra_relacionadaAtual < 10) {
                if (rel_brutas[idx] == ',') {
                    p.relacionadas[palavra_relacionadaAtual][indece_doCaractereNaPalavra] = '\0';
                    palavra_relacionadaAtual++; 
                    indece_doCaractereNaPalavra = 0; 
                } else {
                    p.relacionadas[palavra_relacionadaAtual][indece_doCaractereNaPalavra] = rel_brutas[idx];
                    indece_doCaractereNaPalavra++;
                }
                idx++;
            }
            if (indece_doCaractereNaPalavra > 0) { 
                p.relacionadas[palavra_relacionadaAtual][indece_doCaractereNaPalavra] = '\0';
                palavra_relacionadaAtual++;
            }
            p.numero_de_relacionadas = palavra_relacionadaAtual;

            palavras[numPalavras] = p;

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
void removerDoVetor(Palavra vetor[], int *n, char palavra[])
{
    char palavraBusca[50];

    strcpy(palavraBusca, palavra);
    converterParaMinusculas(palavraBusca);


    for(int i = 0; i < *n; i++)
    {
        char atual[50];

        strcpy(atual, vetor[i].palavra);
        converterParaMinusculas(atual);


        if(strcmp(atual, palavraBusca) == 0)
        {
            for(int j = i; j < *n - 1; j++)
            {
                vetor[j] = vetor[j + 1];
            }

            (*n)--;

            printf("Palavra removida do vetor.\n");
            return;
        }
    }


    printf("Palavra nao encontrada no vetor.\n");
}


void liberarPalavras(Palavra *palavras, int numPalavras) {
}
void liberarMemoria(Trie_Palavras *raiz, Palavra *palavras, int numPalavras) {
    liberarTrie(raiz);
    liberarPalavras(palavras, numPalavras);
}
