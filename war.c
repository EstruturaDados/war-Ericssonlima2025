#include <stdio.h>
#include <string.h>

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    struct Territorio territorios[5];
    int i;

    printf("====================================\n");
    printf("     SISTEMA DE CADASTRO DE TERRITÓRIOS\n");
    printf("====================================\n");

    for (i = 0; i < 5; i++) {
        printf("\n------------------------------------\n");
        printf(">>> Cadastrando Território %d <<<\n", i + 1);
        printf("------------------------------------\n");

        printf("Nome do Território: ");
        scanf(" %29[^\n]", territorios[i].nome);

        printf("Cor do Exército (ex: Azul, Verde): ");
        scanf(" %9s", territorios[i].cor);

        printf("Número de Tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    printf("\n====================================\n");
    printf("        TERRITÓRIOS CADASTRADOS\n");
    printf("====================================\n");

    for (i = 0; i < 5; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("------------------------------------\n");
    }

    printf("\nCadastro concluído com sucesso!\n");

    return 0;

}