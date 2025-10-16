#include <stdio.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"
#include "pilha_int_utils.h"

static void contarParImpar(PilhaInt *pilha, int *pares, int *impares) {
    *pares = 0;
    *impares = 0;

    PilhaInt auxiliar;
    pilhaIntInicializar(&auxiliar);

    int valor;
    while (pilhaIntPop(pilha, &valor)) {
        if (valor % 2 == 0) {
            (*pares)++;
        } else {
            (*impares)++;
        }
        pilhaIntPush(&auxiliar, valor);
    }

    while (pilhaIntPop(&auxiliar, &valor)) {
        pilhaIntPush(pilha, valor);
    }
}

static void demonstrarContagem(void) {
    PilhaInt pilha;
    pilhaIntInicializar(&pilha);

    int valores[] = {7, 6, 5, 4, 3, 2, 1};
    for (int i = 0; i < 7; i++) {
        pilhaIntPush(&pilha, valores[i]);
    }

    printMensagemColorida(CYAN, "Conteudo da pilha:");
    pilhaIntImprimir(&pilha);

    int pares, impares;
    contarParImpar(&pilha, &pares, &impares);

    printf("\n");
    printMensagemColoridaFormatted(GREEN, "Pares: %d", pares);
    printMensagemColoridaFormatted(GREEN, "Impares: %d", impares);

    pilhaIntLiberar(&pilha);
}

static void fluxoManual(void) {
    PilhaInt pilha;
    pilhaIntInicializar(&pilha);

    int quantidade;
    printMensagemColoridaInline(YELLOW, "Quantos valores deseja empilhar? ");
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

    int pares, impares;
    contarParImpar(&pilha, &pares, &impares);

    printf("\nTotal de elementos: %d\n", pilhaIntTamanho(&pilha));
    printMensagemColoridaFormatted(GREEN, "Pares: %d", pares);
    printMensagemColoridaFormatted(GREEN, "Impares: %d", impares);

    pilhaIntLiberar(&pilha);
}

static void cabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Pilha Dinamica - Questao 07 ===");
    printf("\n");
}

void executarQuestaoPilhaDinamica7(void) {
    executarQuestaoPilhaDinamica7Predefinido();
}

void executarQuestaoPilhaDinamica7Predefinido(void) {
    cabecalho();
    demonstrarContagem();
    pausar();
}

void executarQuestaoPilhaDinamica7EntradaManual(void) {
    cabecalho();
    fluxoManual();
    pausar();
}
