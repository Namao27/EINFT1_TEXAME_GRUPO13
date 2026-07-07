#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "busca.h"
#include "grafo.h"
#include "ordenacao.h"
#include "estatistica.h"
#include "palavras.h"

#define MAX_PALAVRAS 1000
#define MAX_RELACIONADA 5
#define NOME_ARQUIVO "PalavrasArquivos.txt"
void lerString(char *buffer, int tamanho)
{
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

void pausar(){
    printf("\n");
    printf("Pressione ENTER para continuar...");
    getchar();
}
int main() {
    // 1. Inicialização das estruturas de dados
    Trie_Palavras *raiz = criarNo();
    if (raiz == NULL) {
        printf("Erro ao inicializar a arvore Trie.\n");
        return 1;
    }

    Palavra dicionario[MAX_PALAVRAS];
    int totalPalavras = 0;


    totalPalavras = carregarPalavrasDeArquivo(raiz, dicionario, NOME_ARQUIVO);
    //printf("Sistema iniciado. %d palavras carregadas de '%s'.\n", totalPalavras, NOME_ARQUIVO);

    int opcao;
    char buffer_palavra[50];
    char prefixoBuffer[100]; 
    int idAuxiliar;

    do {
        
        printf("\n===== Dicionario Digital =====\n");
        printf("1. Inserir Palavra\n");
        printf("2. Procurar/Consultar Palavra\n");
        printf("3. Atualizar Palavra\n");
        printf("4. Remover Palavra\n");
        printf("5. Listar Palavras (Ordem Alfabetica)\n");
        printf("6. Sugestoes De Pesquisa por Prefixo\n");
        printf("7. Guardar Alteracoes (Ficheiro)\n"); 
        printf("8. Estatisticas\n");
        printf("0. Sair\n");

        printf("\nOpcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Escolha uma opcao valida.\n");
            while (getchar() != '\n');
            opcao = -1;
            continue;
        }
        while (getchar() != '\n'); 

        switch (opcao) {
            case 1:
                if (totalPalavras >= MAX_PALAVRAS) {
                    printf("Erro: O dicionario atingiu o limite maximo de %d palavras.\n", MAX_PALAVRAS);
                    break;
                }

                printf("\n--- INSERIR NOVA PALAVRA ---\n");
                
                // 1. Criar e inicializar uma nova struct Palavra
                Palavra nova;
                nova.id = totalPalavras + 1;
                nova.numero_de_relacionadas = 0;
                nova.pesquisas = 0;
                printf("Palavra: ");
                scanf("%49s", nova.palavra);
                
                while (getchar() != '\n');

                // Criar uma cópia em maiúsculas para indexar na Trie com segurança
                char chave_trie[50];
                strcpy(chave_trie, nova.palavra);
                converterParaMaiusculas(chave_trie);

                char chave_trie_minuscula[50];
                strcpy(chave_trie_minuscula, nova.palavra);
                converterParaMinusculas(chave_trie_minuscula);

                // Verificar se a palavra já existe para evitar duplicados
                int idExistente;
                if (pesquisarPalavra(raiz, chave_trie, &idExistente)) {
                    printf("Erro: A palavra '%s' ja existe no dicionario!\n", nova.palavra);
                    break;
                }

                // 3. Ler o Significado (permite espaços)
               printf("Significado: ");
                fgets(nova.significado,sizeof(nova.significado),stdin);
                nova.significado[strcspn(nova.significado,"\n")]='\0';

                if(strlen(nova.significado)==0){
                    printf("Significado obrigatorio.\n");
                    break;
                }

                // 4. Ler o Contexto (permite espaços)
                printf("Contexto: ");
                fgets(nova.contexto, sizeof(nova.contexto), stdin);
                nova.contexto[strcspn(nova.contexto, "\n")] = '\0';

                // 5. Ler a Categoria
                printf("Categoria: ");
                fgets(nova.categoria, sizeof(nova.categoria), stdin);
                nova.categoria[strcspn(nova.categoria, "\n")] = '\0';

                if(strlen(nova.categoria) == 0) {
                    printf("Categoria obrigatoria.\n");
                    break;
                }
                // 6. Ler Palavras Relacionadas (Opcional - Lê até o utilizador digitar Enter vazio)
                printf("\nPalavras Relacionadas (Pressione Enter vazio para terminar):\n");
                while (nova.numero_de_relacionadas < 5) {
                    char rel_buffer[50];
                    printf(" - Relacionada %d: ", nova.numero_de_relacionadas + 1);
                    fgets(rel_buffer,sizeof(rel_buffer), stdin);
                    rel_buffer[strcspn(rel_buffer, "\n")] = '\0';

                    if (strlen(rel_buffer) == 0) {
                        break;
                    }
                    strcpy(nova.relacionadas[nova.numero_de_relacionadas], rel_buffer);
                    nova.numero_de_relacionadas++;
                }
                // 7. Salvar na Base de Dados Híbrida (Vetor + Trie)
                dicionario[totalPalavras] = nova; 
                inserirPalavra(raiz, chave_trie, nova.id);
                
                totalPalavras++;
                
                printf("\nSucesso! Palavra '%s' inserida e indexada com o ID %d.\n", nova.palavra, nova.id);
                printf("Nota:Gravar no arquivo antes de sair (7-Opcao).\n");
                break;

            case 2:
                printf("Digite a palavra que deseja consultar:\n");
                consultarPalavra(dicionario,totalPalavras,raiz);
//printf("Digite a palavra: ");
//scanf("%49s", palavra);
                
break;

            case 3:
                atualizarDadosPalavra(raiz, dicionario, totalPalavras);
                pausar();     
                break;

            case 4:
                    printf("Digite a palavra a remover: ");
                    scanf("%49s", buffer_palavra);
                    while(getchar()!='\n');
                  removerPalavra(
    &raiz,
    dicionario,
    &totalPalavras,
    buffer_palavra,
    NOME_ARQUIVO
);

                        pausar();
                                            
                        break;

            case 5:
                printf("\n--- Listagem de Palavras ---\n");
                listarPalavras(raiz, prefixoBuffer, 0);
                
                
                pausar();
                break;

            case 6:
                printf("Digite o prefixo para busca (ex: AB): ");
                scanf("%s", buffer_palavra);
                while (getchar() != '\n');
                converterParaMaiusculas(buffer_palavra);
                // Nota: Garante que implementas esta funcao 'sugerirPalavrasPorPrefixo' no teu .c
                sugerirPalavrasPorPrefixo(raiz, buffer_palavra);
                
                
                pausar();
      
                break;

            case 7:
                printf("A guardar dados em '%s'...\n", NOME_ARQUIVO);
                guardarPalavrasEmArquivo(dicionario, totalPalavras, NOME_ARQUIVO);
                printf("Dados gravados com sucesso!\n");
                
                
                pausar();
                                break;

            case 8:
                mostrarEstatisticas(dicionario, totalPalavras);
                printf("\nPressione ENTER para voltar ao menu...");
                pausar();
                
                    
                break;

            case 0:
                printf("A encerrar o dicionario. Certifique-se de que guardou as alteracoes.\n");
                break;

            default:
                if (opcao != -1) 
                printf("Opcao invalida!\n");
                break;
        }

    } while(opcao != 0);

    // 3. Libertar a memória dinâmica alocada para a Trie antes de fechar
    liberarTrie(raiz);

    return 0;
}