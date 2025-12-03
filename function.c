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

int btree_search(BTree* tree, BTreeNode* node, int key) {
    if (node == NULL) return 0;

    int i = 0;

    while (i < node->num_keys && key > node->keys[i])
        i++;

    if (i < node->num_keys && key == node->keys[i])
        return 1; // Achou

    if (node->is_leaf)
        return 0; // Não existe

    return btree_search(tree, (BTreeNode*)node->children[i], key);
}

void btree_split_child(BTreeNode* parent, int index, int t) {
    BTreeNode* full_child = (BTreeNode*)parent->children[index];
    BTreeNode* new_child = create_node(full_child->is_leaf);

    new_child->num_keys = t - 1;

    for (int j = 0; j < t - 1; j++)
        new_child->keys[j] = full_child->keys[j + t];

    if (!full_child->is_leaf) {
        for (int j = 0; j < t; j++)
            new_child->children[j] = full_child->children[j + t];
    }

    full_child->num_keys = t - 1;

    for (int j = parent->num_keys; j >= index + 1; j--)
        parent->children[j + 1] = parent->children[j];

    parent->children[index + 1] = (int)new_child;

    for (int j = parent->num_keys - 1; j >= index; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[index] = full_child->keys[t - 1];

    parent->num_keys++;
}

void btree_insert_nonfull(BTreeNode* node, int key, int t) {
    int i = node->num_keys - 1;

    if (node->is_leaf) {

        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->num_keys++;
    }
    else {

        while (i >= 0 && key < node->keys[i])
            i--;

        i++;

        BTreeNode* child = (BTreeNode*)node->children[i];

        if (child->num_keys == 2 * t - 1) {

            btree_split_child(node, i, t);

            if (key > node->keys[i])
                i++;
        }

        btree_insert_nonfull((BTreeNode*)node->children[i], key, t);
    }
}

void btree_insert(BTree* tree, int key) {

    if (tree->root_id == -1) {
        BTreeNode* root = create_node(1);
        root->keys[0] = key;
        root->num_keys = 1;

        tree->root_id = (int)root;
        return;
    }

    BTreeNode* root = (BTreeNode*)tree->root_id;

    if (root->num_keys == 2 * tree->t - 1) {

        BTreeNode* new_root = create_node(0);
        new_root->children[0] = (int)root;

        btree_split_child(new_root, 0, tree->t);

        int i = 0;
        if (key > new_root->keys[0])
            i = 1;

        btree_insert_nonfull((BTreeNode*)new_root->children[i], key, tree->t);

        tree->root_id = (int)new_root;
    }
    else {
        btree_insert_nonfull(root, key, tree->t);
    }
}
