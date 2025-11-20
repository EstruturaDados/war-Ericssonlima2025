#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n------------------------------------\n");
        printf(">>> Cadastrando Território %d <<<\n", i + 1);

        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);

        printf("Cor do exército: ");
        scanf(" %9s", mapa[i].cor);

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n====================================\n");
    printf("       LISTA DE TERRITÓRIOS\n");
    printf("====================================\n");

    for (int i = 0; i < n; i++) {
        printf("\n(%d)\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("------------------------------------\n");
    }
}

void atacar(Territorio* atacante, Territorio* defensor) {
    if (atacante->tropas <= 1) {
        printf("\nO território atacante precisa de mais de 1 tropa para atacar!\n");
        return;
    }

    printf("\n>>> Ataque: %s (%s) ATACANDO %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAtq = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    printf("Dado do atacante: %d\n", dadoAtq);
    printf("Dado do defensor: %d\n", dadoDef);

    if (dadoAtq > dadoDef) {
        printf("\n*** O atacante venceu! ***\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= atacante->tropas / 2;
        printf("O território defensor agora pertence a %s!\n", atacante->cor);
    } else {
        printf("\n*** O defensor resistiu ao ataque! ***\n");
        atacante->tropas -= 1;
        printf("O atacante perdeu 1 tropa.\n");
    }
}

void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL));

    int n;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    // Exibe apenas uma vez após cadastro
    exibirTerritorios(mapa, n);

    // FASE DE ATAQUE DIRETA
    while (1) {
        int at, def;

        // Escolher atacante
        printf("\nFase de ataque: Escolha o território atacante (1 a %d ou 0 para sair): ", n);
        scanf("%d", &at);

        if (at == 0) break;   // Encerra fase de ataque

        if (at < 1 || at > n) {
            printf("ID inválido!\n");
            continue;
        }

        at -= 1;

        // Escolher defensor
        printf("Escolha o território defensor (1 a %d): ", n);
        scanf("%d", &def);

        if (def < 1 || def > n) {
            printf("ID inválido!\n");
            continue;
        }

        def -= 1;

        if (strcmp(mapa[at].cor, mapa[def].cor) == 0) {
            printf("\nERRO: Você não pode atacar um território da mesma cor!\n");
            continue;
        }

        atacar(&mapa[at], &mapa[def]);
    }

    liberarMemoria(mapa);
    printf("\nMemória liberada. Programa encerrado!\n");

    return 0;
}