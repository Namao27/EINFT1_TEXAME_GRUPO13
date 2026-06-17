#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palavras.h"
#define MAX_PALAVRAS 1000
#define NOME_ARQUIVO "PalavrasArquivos.txt"

int main() {
    // 1. Inicialização das estruturas de dados
    Trie_Palavras *raiz = criarNo();
    if (raiz == NULL) {
        printf("Erro ao inicializar a arvore Trie.\n");
        return 1;
    }

    Palavra dicionario[MAX_PALAVRAS];
    int totalPalavras = 0;

    // 2. Carregar os dados automaticamente no arranque
    totalPalavras = carregarPalavrasDeArquivo(raiz, dicionario, NOME_ARQUIVO);
    printf("Sistema iniciado. %d palavras carregadas de '%s'.\n", totalPalavras, NOME_ARQUIVO);

    int opcao;
    char buffer_palavra[50];
    char prefixoBuffer[100]; // Usado para a listagem recursiva
    int idAuxiliar;

    do {
        printf("\n===== Dicionario Digital =====\n");
        printf("1. Inserir Palavra\n");
        printf("2. Procurar/Consultar Palavra\n");
        printf("3. Atualizar Palavra\n");
        printf("4. Remover Palavra\n");
        printf("5. Listar Palavras (Ordem Alfabetica)\n");
        printf("6. Sugestoes por Prefixo\n");
        printf("7. Guardar Alteracoes (Ficheiro)\n"); // Boa prática ter uma opção explícita para salvar
        printf("8. Estatisticas\n");
        printf("0. Sair\n");

        printf("\nOpcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Por favor, introduza um numero valido.\n");
            while (getchar() != '\n'); // Limpa buffer
            opcao = -1;
            continue;
        }
        while (getchar() != '\n'); // Limpa o \n do buffer

        switch (opcao) {
            case 1:
                // Exemplo de inserção manual (se quiseres implementar um formulário rápido no main)
                printf("Funcionalidade de insercao manual pode ler novos dados para o vetor aqui.\n");
                break;

            case 2:
                // Chama a tua função de consulta que já faz a busca na Trie e exibe a Struct
                consultarPalavra(dicionario, totalPalavras, raiz);
                break;

            case 3:
                // Atualiza o significado/contexto no vetor mantendo o ID
                atualizarDadosPalavra(raiz, dicionario, totalPalavras);
                break;

            case 4:
                printf("Digite a palavra a remover: ");
                scanf("%s", buffer_palavra);
                while (getchar() != '\n');
                converterParaMaiusculas(buffer_palavra);
                removerPalavra(raiz, buffer_palavra);
                break;

            case 5:
                printf("\n--- Listagem de Palavras ---\n");
                listarPalavras(raiz, prefixoBuffer, 0);
                break;

            case 6:
                printf("Digite o prefixo para busca (ex: AB): ");
                scanf("%s", buffer_palavra);
                while (getchar() != '\n');
                converterParaMaiusculas(buffer_palavra);
                // Nota: Garante que implementas esta funcao 'sugerirPalavrasPorPrefixo' no teu .c
                sugerirPalavrasPorPrefixo(raiz, buffer_palavra);
                break;

            case 7:
                printf("A guardar dados em '%s'...\n", NOME_ARQUIVO);
                guardarPalavrasEmArquivo(dicionario, totalPalavras, NOME_ARQUIVO);
                printf("Dados gravados com sucesso!\n");
                break;

            case 8:
                printf("\n--- Estatisticas ---\n");
                printf("Total de palavras ativas na Trie: %d\n", contarPalavras(raiz));
                printf("Total de registos no vetor: %d\n", totalPalavras);
                break;

            case 0:
                printf("A encerrar o dicionario. Certifique-se de que guardou as alteracoes.\n");
                break;

            default:
                if (opcao != -1) printf("Opcao invalida!\n");
                break;
        }

    } while(opcao != 0);

    // 3. Libertar a memória dinâmica alocada para a Trie antes de fechar
    liberarTrie(raiz);

    return 0;
}