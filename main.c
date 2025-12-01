#include "function.h"
#include <string.h>

int main() {
    FILE* arquivo;
    char linha[50];

    BTree* arvore = create_tree(3);

    arquivo = fopen("operacoes.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    while (fgets(linha, sizeof(linha), arquivo)) {

        // Remove \n da linha
        linha[strcspn(linha, "\n")] = 0;

        // ---- TESTE DA FUNÇÃO ----
        int resultado = ler_comando_insert(linha);
        printf("Resultado ler_comando_insert(\"%s\") = %d\n", linha, resultado);

        if (resultado != -1) {
            printf("[OK] INSERT detectado -> valor %d\n", resultado);
        } else {
            printf("[ERRO] Linha nao e INSERT\n");
        }
    }

    fclose(arquivo);
    return 0;
}
