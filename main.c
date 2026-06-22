#include <stdio.h>
#include "grafo.h"
#include "dicionario.h"
#include "estatistica.h"

int main()
{
    Grafo g;
    inicializarGrafo(&g, MAX);

    int opcao;
    int origem, destino;

    do
    {
        printf("\n====== DICIONARIO DIGITAL ======\n");

        printf("1. Inserir palavra\n");
        printf("2. Listar palavras\n");
        printf("3. Pesquisar palavra\n");
        printf("4. Atualizar palavra\n");
        printf("5. Remover palavra\n");

        printf("\n====== GRAFO ======\n");
        printf("6. Adicionar relacao(Em ordem númerica se não será hackeado:)\n");
        printf("7. Mostrar relacoes\n");
        printf("8. Remover relacao\n");

        printf("\n====== ESTATISTICA ======\n");
        printf("9. Total palavras\n");
        printf("10. Estatisticas\n");

        printf("\n0. Sair\n");

        printf("\nOpcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1: inserirPalavra(); break;
            case 2: listarPalavras(); break;
            case 3: pesquisarPalavra(); break;
            case 4: atualizarPalavra(); break;
            case 5: removerPalavra(); break;

            case 6:
                listarPalavras();
                printf("Origem: ");
                scanf("%d", &origem);
                printf("Destino: ");
                scanf("%d", &destino);

                adicionarRelacao(&g, origem - 1, destino - 1);
                break;

            case 7:
                listarPalavras();
                printf("Indice: ");
                scanf("%d", &origem);

                mostrarRelacoes(&g, origem - 1);
                break;

            case 8:
                printf("Origem: ");
                scanf("%d", &origem);
                printf("Destino: ");
                scanf("%d", &destino);

                removerRelacao(&g, origem - 1, destino - 1);
                break;

            case 9:
                totalPalavras(dicionario, total);
                break;

            case 10:
                mostrarEstatisticas(dicionario, total);
                break;

            case 0:
                printf("A sair...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}