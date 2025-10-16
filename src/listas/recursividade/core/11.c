#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

// Questao 11: Imprimir numeros pares de N ate 0 em ordem decrescente

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Recursividade - Questao 11 ===");
    printf("\n");
}

static void imprimirParesDecrescente(int atual) {
    if (atual < 0) {
        return;
    }

    printf("%d ", atual);
    imprimirParesDecrescente(atual - 2);
}

static void rastrearPares(int atual, int nivel) {
    printMensagemColoridaFormatted(YELLOW, "Nivel %d -> paresDec(%d)", nivel, atual);

    if (atual < 0) {
        printMensagemColoridaFormatted(GREEN, "Caso base: atual < 0. Retorna.\n");
        return;
    }

    printMensagemColoridaFormatted(CYAN, "Imprime %d e chama paresDec(%d)\n", atual, atual - 2);

    rastrearPares(atual - 2, nivel + 1);
}

void executarQuestaoRecursividade11(void) {
    executarQuestaoRecursividade11Predefinido();
}

void executarQuestaoRecursividade11Predefinido(void) {
    imprimirCabecalho();

    int limite = 10;

    printMensagemColoridaFormatted(CYAN, "Limite escolhido: %d\n", limite);

    rastrearPares(limite, 0);

    printf("Sequencia resultante: ");
    imprimirParesDecrescente(limite);
    printf("\n");

    pausar();
}

void executarQuestaoRecursividade11EntradaManual(void) {
    imprimirCabecalho();

    int limite;

    printf("Digite um numero inteiro par e nao negativo: ");
    if (scanf("%d", &limite) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (limite < 0 || limite % 2 != 0) {
        printMensagemColoridaFormatted(RED, "\nInforme um valor par e nao negativo.");
        pausar();
        return;
    }

    printMensagemColoridaFormatted(CYAN, "\nPares de %d ate 0:", limite);

    imprimirParesDecrescente(limite);
    printf("\n");

    pausar();
}
