#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"
#include "../../../shared/headlers/animacao.h"
#include "pilha_int_utils.h"

static int popN(PilhaInt *pilha, int n, int *destino) {
    if (n <= 0) {
        return 0;
    }
    int removidos = 0;
    while (removidos < n && pilhaIntPop(pilha, destino ? &destino[removidos] : NULL)) {
        removidos++;
    }
    return removidos;
}

static void demonstrarPopN(void) {
    PilhaInt pilha;
    pilhaIntInicializar(&pilha);

    for (int i = 1; i <= 5; i++) {
        pilhaIntPush(&pilha, i * 10);
    }

    printMensagemColoridaInline(CYAN, "Estado da pilha: ");
    pilhaIntImprimir(&pilha);

    int removidos[4] = {0};
    printf("\n");
    printComAnimacao("Aplicando popN(3) - removendo 3 elementos");
    int qtd = popN(&pilha, 3, removidos);
    printf("Elementos removidos (%d): ", qtd);
    for (int i = 0; i < qtd; i++) {
        printf("%d%s", removidos[i], i + 1 == qtd ? "" : ", ");
    }
    printf("\n\nEstado da pilha apos remocao:\n");
    pilhaIntImprimir(&pilha);

    pilhaIntLiberar(&pilha);
}

static void fluxoManual(void) {
    PilhaInt pilha;
    pilhaIntInicializar(&pilha);

    int quantidade;
    printf("Quantos valores deseja empilhar inicialmente? ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColorida(RED, "Entrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    for (int i = 0; i < quantidade; i++) {
        int valor;
        printf("Valor %d: ", i + 1);
        if (scanf("%d", &valor) != 1) {
            limparBufferTeclado();
            valor = 0;
        } else {
            limparBufferTeclado();
        }
        pilhaIntPush(&pilha, valor);
    }

    printf("\nEstado atual da pilha:\n");
    pilhaIntImprimir(&pilha);

    int n;
    printf("\nQuantos elementos deseja remover com popN? ");
    if (scanf("%d", &n) != 1) {
        limparBufferTeclado();
        n = 0;
    }
    limparBufferTeclado();

    if (n <= 0) {
        printMensagemColoridaFormatted(RED, "Entrada invalida!\n");
        pilhaIntLiberar(&pilha);
        pausar();
        return;
    }

    int *removidos = (int *)malloc((size_t)n * sizeof(int));
    if (!removidos) {
        printMensagemColoridaFormatted(RED, "Erro ao alocar memoria!\n");
        pilhaIntLiberar(&pilha);
        pausar();
        return;
    }

    printf("\n");
    printComAnimacao("Removendo elementos da pilha");
    int qtd = popN(&pilha, n, removidos);

    printMensagemColoridaFormatted(GREEN, "\nRemocao concluida: %d elemento(s) retirado(s).\n", qtd);
    if (qtd > 0) {
        printf("Elementos removidos (ordem de remocao): ");
        for (int i = 0; i < qtd; i++) {
            printf("%d%s", removidos[i], (i + 1 == qtd) ? "" : ", ");
        }
        printf("\n");
    }

    printf("\nPilha apos popN:\n");
    pilhaIntImprimir(&pilha);

    free(removidos);
    pilhaIntLiberar(&pilha);
}

static void cabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Pilha Dinamica - Questao 02 ===");
    printf("\n");
}

void executarQuestaoPilhaDinamica2(void) {
    executarQuestaoPilhaDinamica2Predefinido();
}

void executarQuestaoPilhaDinamica2Predefinido(void) {
    cabecalho();
    demonstrarPopN();
    pausar();
}

void executarQuestaoPilhaDinamica2EntradaManual(void) {
    cabecalho();
    fluxoManual();
    pausar();
}
