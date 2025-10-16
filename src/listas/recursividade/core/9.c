#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

// Questao 9: Imprimir numeros pares de 0 ate N em ordem crescente

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Recursividade - Questao 09 ===");
    printf("\n");
}

static void imprimirParesCrescente(int limite, int atual) {
    if (atual > limite) {
        return;
    }

    printf("%d ", atual);
    imprimirParesCrescente(limite, atual + 2);
}

static void rastrearPares(int limite, int atual, int nivel) {
    printMensagemColoridaFormatted(YELLOW, "Nivel %d -> pares(%d, %d)\n", nivel, limite, atual);

    if (atual > limite) {
        printMensagemColoridaFormatted(GREEN, "Caso base: atual (%d) > limite (%d). Retorna.\n", atual, limite);
        return;
    }

    printMensagemColoridaFormatted(CYAN, "Imprime %d e chama pares(%d, %d)\n\n", atual, limite, atual + 2);

    rastrearPares(limite, atual + 2, nivel + 1);
}

void executarQuestaoRecursividade9(void) {
    executarQuestaoRecursividade9Predefinido();
}

void executarQuestaoRecursividade9Predefinido(void) {
    imprimirCabecalho();

    int limite = 12;

    printMensagemColoridaFormatted(CYAN, "Limite escolhido: %d\n", limite);

    rastrearPares(limite, 0, 0);

    printf("Sequencia resultante: ");
    imprimirParesCrescente(limite, 0);
    printf("\n");

    pausar();
}

void executarQuestaoRecursividade9EntradaManual(void) {
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

    printMensagemColoridaFormatted(CYAN, "\nNumeros pares de 0 ate %d:", limite);

    imprimirParesCrescente(limite, 0);
    printf("\n");

    pausar();
}
