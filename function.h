#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>

// --- CONSTANTES ---
// MAX_ORDER define o tamanho fixo da struct no disco.
#define MAX_ORDER 20 

// --- ESTRUTURAS DE DADOS ---

typedef struct {
    int page_id;                    // ID único desta página no arquivo (0, 1, 2...)
    int num_keys;                   // Quantas chaves estão ocupadas no momento
    int is_leaf;                    // 1 se for folha, 0 se não for
    int keys[2 * MAX_ORDER - 1];    // Vetor de chaves
    int children[2 * MAX_ORDER];    // Vetor de IDs dos filhos (links para outras páginas)
} BTreeNode;

// 2. A Árvore (Metadados na RAM)
typedef struct {
    int root_id;    // ID da página onde está a raiz (-1 se a árvore estiver vazia)
    int t;          // O grau mínimo 't' escolhido pelo usuário
} BTree;

// --- PROTÓTIPOS (Funções Disponíveis) ---

// Funções do JOSÉ (Estrutura)
BTree* create_tree(int t);
BTreeNode* create_node(int is_leaf);

// Leitura de linha com INSERT x ou SEARCH x
int ler_comando_insert_search(char* linha, int* valor);

// Identifica comando isolado (modo escrita)
int identificar_comando(char* cmd);

// Escrita no arquivo
void EscreverInsert(FILE* f, int valor);
void EscreverSearch(FILE* f, int valor);


#endif