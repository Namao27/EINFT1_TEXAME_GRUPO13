#include <stdio.h>
#include <stdlib.h>


int main() {

    int opcao;

    do {

        printf("\n===== Dicionario Digital =====\n");
        printf("1. Inserir Palavra\n");
        printf("2. Procurar Palavra\n");
        printf("3. Atualizar Palavra\n");
        printf("4. Remover Palavra\n");
        printf("5. Listar Palavras\n");
        printf("6. Sugestoes por Prefixo\n");
        printf("7. Conceitos Relacionados\n");
        printf("8. Estatisticas\n");
        printf("0. Sair\n");

        printf("\nOpcao: ");
        scanf("%d", &opcao);

    } while(opcao != 0);

    return 0;
}