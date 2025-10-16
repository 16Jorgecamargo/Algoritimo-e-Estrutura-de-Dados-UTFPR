#include <stdio.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"
#include "../../../shared/headlers/animacao.h"
#include "pilha_int_utils.h"

static void copiarPilha(PilhaInt *origem, PilhaInt *destino) {
    PilhaInt auxiliar;
    pilhaIntInicializar(&auxiliar);

    int valor;
    while (pilhaIntPop(origem, &valor)) {
        pilhaIntPush(&auxiliar, valor);
    }

    while (pilhaIntPop(&auxiliar, &valor)) {
        pilhaIntPush(origem, valor);
        pilhaIntPush(destino, valor);
    }
}

static void demonstrarCopia(void) {
    PilhaInt original;
    PilhaInt copia;
    pilhaIntInicializar(&original);
    pilhaIntInicializar(&copia);

    pilhaIntPush(&original, 50);
    pilhaIntPush(&original, 40);
    pilhaIntPush(&original, 30);
    pilhaIntPush(&original, 20);
    pilhaIntPush(&original, 10);

    printMensagemColoridaInline(CYAN, "Estado da pilha: ");
    pilhaIntImprimir(&original);

    printf("\n");
    printComAnimacao("Copiando pilha");
    copiarPilha(&original, &copia);
    printMensagemColoridaFormatted(GREEN, "Pilha copiada com sucesso!\n");

    printf("\n");
    printMensagemColorida(GREEN, "Pilha original apos copia (deve permanecer igual):");
    pilhaIntImprimir(&original);

    printf("\n");
    printMensagemColorida(GREEN, "Pilha copia:");
    pilhaIntImprimir(&copia);

    pilhaIntLiberar(&original);
    pilhaIntLiberar(&copia);
}

static void fluxoManual(void) {
    PilhaInt original;
    PilhaInt copia;
    pilhaIntInicializar(&original);
    pilhaIntInicializar(&copia);

    int quantidade;
    printMensagemColorida(YELLOW, "Quantos valores deseja empilhar na pilha original? ");
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
        pilhaIntPush(&original, valor);
    }

    printMensagemColorida(GREEN, "\nPilha original antes da copia:");
    pilhaIntImprimir(&original);

    printf("\n");
    printComAnimacao("Copiando pilha");
    copiarPilha(&original, &copia);
    printMensagemColoridaFormatted(GREEN, "Pilha copiada com sucesso!\n");

    printMensagemColorida(GREEN, "\nPilha original apos copia:");
    pilhaIntImprimir(&original);

    printMensagemColorida(GREEN, "\nPilha copia:");
    pilhaIntImprimir(&copia);

    pilhaIntLiberar(&original);
    pilhaIntLiberar(&copia);
}

static void cabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Pilha Dinamica - Questao 03 ===");
    printf("\n");
}

void executarQuestaoPilhaDinamica3(void) {
    executarQuestaoPilhaDinamica3Predefinido();
}

void executarQuestaoPilhaDinamica3Predefinido(void) {
    cabecalho();
    demonstrarCopia();
    pausar();
}

void executarQuestaoPilhaDinamica3EntradaManual(void) {
    cabecalho();
    fluxoManual();
    pausar();
}
