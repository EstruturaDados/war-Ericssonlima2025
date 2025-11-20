#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>   // para toupper

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

        /* Normaliza cor para MAIÚSCULAS para evitar erros de comparação */
        for (char *p = mapa[i].cor; *p; ++p) {
            *p = (char) toupper((unsigned char) *p);
        }

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

void listarTerritoriosDoJogador(Territorio* mapa, int n, const char* corJogador) {
    printf("\nTerritórios de %s:\n", corJogador);
    int achou = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            printf("  [%d] %s (Tropas: %d)\n", i + 1, mapa[i].nome, mapa[i].tropas);
            achou = 1;
        }
    }
    if (!achou) {
        printf("  (Nenhum território pertence a %s)\n", corJogador);
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
        int transfer = atacante->tropas / 2;
        if (transfer < 1) transfer = 1;
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = transfer;
        atacante->tropas -= transfer;
        printf("O território defensor agora pertence a %s!\n", atacante->cor);
        printf("Tropas transferidas: %d. Tropas restantes no atacante: %d\n",
               transfer, atacante->tropas);
    } else {
        printf("\n*** O defensor resistiu ao ataque! ***\n");
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
        printf("O atacante perdeu 1 tropa. Tropas restantes: %d\n", atacante->tropas);
    }
}

void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    srand((unsigned int) time(NULL));

    int n;
    printf("Quantos territórios deseja cadastrar? ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Número de territórios inválido.\n");
        return 1;
    }

    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    // Exibe apenas uma vez após cadastro
    exibirTerritorios(mapa, n);

    // FASE DE ATAQUE DIRETA (mantive o fluxo original, melhoramos a escolha do atacante)
    while (1) {
        int at, def;
        char corAtual[10];

        // Pergunta a cor do jogador que está atacando (opcional: você pode forçar cores fixas)
        printf("\nDigite a COR do jogador que vai atacar (ex: AZUL) ou 'SAIR' para encerrar: ");
        scanf(" %9s", corAtual);
        for (char *p = corAtual; *p; ++p) *p = (char) toupper((unsigned char)*p);

        if (strcmp(corAtual, "SAIR") == 0) break;

        // Lista apenas os territórios que pertencem a essa cor
        listarTerritoriosDoJogador(mapa, n, corAtual);

        printf("\nFase de ataque: Escolha o território atacante (1 a %d ou 0 para cancelar): ", n);
        if (scanf("%d", &at) != 1) { getchar(); printf("Entrada inválida.\n"); continue; }

        if (at == 0) continue;   // cancela o ataque desta vez

        if (at < 1 || at > n) {
            printf("ID inválido!\n");
            continue;
        }
        at -= 1;

        // Verifica se atacante realmente pertence à cor informada
        if (strcmp(mapa[at].cor, corAtual) != 0) {
            printf("Erro: o território atacante não pertence à cor informada (%s)!\n", corAtual);
            continue;
        }

        // Escolher defensor
        printf("Escolha o território defensor (1 a %d): ", n);
        if (scanf("%d", &def) != 1) { getchar(); printf("Entrada inválida.\n"); continue; }

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

        // opcional: exibir mapa atualizado a cada ataque
        exibirTerritorios(mapa, n);
    }

    liberarMemoria(mapa);
    printf("\nMemória liberada. Programa encerrado!\n");

    return 0;
}
