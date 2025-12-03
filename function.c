#include "function.h"
#include <string.h>

// Cria a estrutura principal da árvore
BTree* create_tree(int t) {
    if (t > MAX_ORDER) {
        printf("Erro: O grau t (%d) excede o limite (%d).\n", t, MAX_ORDER);
        return NULL;
    }
    if (t < 2) {
        printf("Erro: O grau t deve ser no mínimo 2.\n");
        return NULL;
    }

    BTree* tree = (BTree*)malloc(sizeof(BTree));
    tree->t = t;
    tree->root_id = -1;

    return tree;
}

// Cria um nó vazio
BTreeNode* create_node(int is_leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));

    node->is_leaf = is_leaf;
    node->num_keys = 0;
    node->page_id = -1;

    for (int i = 0; i < 2 * MAX_ORDER - 1; i++)
        node->keys[i] = -1;

    for (int i = 0; i < 2 * MAX_ORDER; i++)
        node->children[i] = -1;

    return node;
}

// Lê linha completa: "INSERT 10" ou "SEARCH 5"
int ler_comando_insert_search(char* linha, int* valor) {
    char comando[20];

    if (sscanf(linha, "%19s %d", comando, valor) == 2) {
        if (strcmp(comando, "INSERT") == 0) return 1;
        if (strcmp(comando, "SEARCH") == 0) return 2;
    }
    return -1;
}

// Identifica comando isolado
int identificar_comando(char* cmd) {
    if (strcmp(cmd, "INSERT") == 0) return 1;
    if (strcmp(cmd, "SEARCH") == 0) return 2;
    return 0;
}

// Escrita no arquivo
void EscreverInsert(FILE* f, int valor) {
    fprintf(f, "\nINSERT %d", valor);
}

void EscreverSearch(FILE* f, int valor) {
    fprintf(f, "\nSEARCH %d", valor);
}
