#include "function.h"
#include <string.h>

int main() {
    FILE* arquivo_leitura;
    FILE* arquivo_saida;

    char linha[50];
    char cmd[10];
    int valor;

    BTree* arvore = create_tree(3);

    int escolha;

    printf("Digite 1 para ler o arquivo ou 2 para escrever nele: ");
    scanf("%d", &escolha);

    // ---------------- MODO LEITURA ----------------
    if (escolha == 1) {

        arquivo_leitura = fopen("operacoes.txt", "r");
        if (!arquivo_leitura) {
            printf("Erro ao abrir operacoes.txt para leitura!\n");
            return 1;
        }

        while (fgets(linha, sizeof(linha), arquivo_leitura)) {

            linha[strcspn(linha, "\n")] = 0;

            int tipo = ler_comando_insert_search(linha, &valor);

            if (tipo == 1)
                printf("[ARQUIVO] INSERT %d\n", valor);

            else if (tipo == 2)
                printf("[ARQUIVO] SEARCH %d\n", valor);

            else
                printf("[ARQUIVO] Linha inválida: %s\n", linha);
        }

        fclose(arquivo_leitura);
    }

    // ---------------- MODO ESCRITA ----------------
    else if (escolha == 2) {

        arquivo_saida = fopen("operacoes.txt", "a");
        if (!arquivo_saida) {
            printf("Erro ao abrir operacoes.txt para escrita!\n");
            return 1;
        }

        printf("Digite o comando (INSERT ou SEARCH): ");
        scanf("%9s", cmd);

        printf("Digite o valor: ");
        scanf("%d", &valor);

        // CORREÇÃO IMPORTANTE  
        int tipo = identificar_comando(cmd);

        if (tipo == 1) {
            EscreverInsert(arquivo_saida, valor);
            printf("Gravado: INSERT %d\n", valor);
        }
        else if (tipo == 2) {
            EscreverSearch(arquivo_saida, valor);
            printf("Gravado: SEARCH %d\n", valor);
        }
        else {
            printf("Comando inválido!\n");
        }

        fclose(arquivo_saida);
    }

    else {
        printf("Opção inválida!\n");
    }

    return 0;
}
