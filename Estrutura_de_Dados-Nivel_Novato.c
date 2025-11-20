#include <stdio.h>
#include <string.h>

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    struct Territorio territorios[5];

    printf("--- Cadastro de Territorio 1 ---\n");
    for (int i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Digite o nome do territorio: ");
        scanf(" %29[^\n]", territorios[i].nome);
        printf("Digite a cor do exercito: ");
        scanf(" %9[^\n]", territorios[i].cor); // aceita cor com espaços
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        printf("\n");
    }

    printf("--- Territorio Cadastrado ---\n");
    printf("%-29s %-9s %-s\n", "Nome", "Cor", "Tropas");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < 5; i++) {
        printf("%-29s %-9s %-d\n", territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }

    return 0;
}