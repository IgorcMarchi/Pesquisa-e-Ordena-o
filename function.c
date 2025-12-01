#include "function.h"

// Cria a estrutura principal da árvore
BTree* create_tree(int t) {
    // Validação básica
    if (t > MAX_ORDER) {
        printf("Erro: O grau t (%d) excede o limite fisico suportado (%d).\n", t, MAX_ORDER);
        return NULL;
    }
    if (t < 2) {
        printf("Erro: O grau t deve ser no minimo 2.\n");
        return NULL;
    }

    BTree* tree = (BTree*)malloc(sizeof(BTree));
    tree->t = t;
    tree->root_id = -1; // -1 indica que ainda não existe raiz gravada no disco
    
    return tree;
}

// Cria um nó vazio na memória (pronto para ser preenchido e salvo)
BTreeNode* create_node(int is_leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    node->page_id = -1; // -1 indica que ainda não tem endereço no disco

    // Inicializa os arrays com -1 para evitar "lixo" de memória
    for (int i = 0; i < 2 * MAX_ORDER - 1; i++) {
        node->keys[i] = -1;
    }
    for (int i = 0; i < 2 * MAX_ORDER; i++) {
        node->children[i] = -1;
    }

    return node;
}