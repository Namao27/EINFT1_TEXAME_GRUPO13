#ifndef PALAVRA_H
#define PALAVRA_H

#define MAX_PALAVRAS 1000

// 1. Definição da estrutura de dados das palavras (Sincronizada com o arquivo)
typedef struct {
    int id;
    char palavra[50];
    char significado[500];
    char contexto[500];
    char categoria[50];               // Movido para cima para seguir o fluxo do sscanf/fprintf
    char relacionadas[10][50];
    int numero_de_relacionadas;
} Palavra;

// 2. Definição do nó da árvore Trie
typedef struct Trie_Palavras {
    struct Trie_Palavras *filhos[26];
    int fimPalavra;
    int ID_palavra;
} Trie_Palavras;

// 3. Protótipos das Funções Utilitárias e Validação
Trie_Palavras *criarNo();
void converterParaMaiusculas(char *str);
void converterParaMinusculas(char *str);
void validarPalavra(char *palavra); // Se alterares para retornar int no .c, muda aqui para: int validarPalavra(char *palavra);

// 4. Protótipos de Manipulação da Trie e Dados
void inserirPalavra(Trie_Palavras *raiz, char palavra[], int id);
int pesquisarPalavra(Trie_Palavras *raiz, char palavra[], int *idEncontrado); // CORRIGIDO: de void para int
void removerPalavra(Trie_Palavras *raiz, char palavra[]);
void atualizarDadosPalavra(Trie_Palavras *raiz, Palavra palavras[], int numPalavras);

// 5. Protótipos de Consulta e Exibição
void listarPalavras(Trie_Palavras *raiz, char prefixo[], int nivel);
int contarPalavras(Trie_Palavras *raiz);
void sugerirPalavrasPorPrefixo(Trie_Palavras *raiz, char prefixo[]);    
Palavra* buscarPalavraPorID(Palavra palavras[], int numPalavras, int id);
void consultarPalavra(Palavra palavras[], int numPalavras, Trie_Palavras *raiz);

// 6. Protótipos de Gestão de Memória e Persistência
void guardarPalavrasEmArquivo(Palavra palavras[], int numPalavras, const char *inseridas);
int carregarPalavrasDeArquivo(Trie_Palavras *raiz, Palavra palavras[], const char *PalavrasArquivos);
void liberarTrie(Trie_Palavras *raiz);
void liberarPalavras(Palavra *palavras, int numPalavras);
void liberarMemoria(Trie_Palavras *raiz, Palavra *palavras, int numPalavras);

#endif // PALAVRA_H