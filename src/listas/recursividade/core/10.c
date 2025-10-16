#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

// Questao 10: Imprimir numeros naturais de N ate 0 (ordem decrescente)

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Recursividade - Questao 10 ===");
    printf("\n");
}

static void imprimirDecrescente(int atual) {
    if (atual < 0) {
        return;
    }
    printf("%d ", atual);
    imprimirDecrescente(atual - 1);
}

static void rastrearDecrescente(int atual, int nivel) {
    printMensagemColoridaFormatted(YELLOW, "Nivel %d -> decrescente(%d)", nivel, atual);

    if (atual < 0) {
        printMensagemColoridaFormatted(GREEN, "Caso base: atual < 0. Retorna.\n");
        return;
    }

    printMensagemColoridaFormatted(CYAN, "Imprime %d e chama decrescente(%d)\n", atual, atual - 1);

    rastrearDecrescente(atual - 1, nivel + 1);
}

void executarQuestaoRecursividade10(void) {
    executarQuestaoRecursividade10Predefinido();
}

void executarQuestaoRecursividade10Predefinido(void) {
    imprimirCabecalho();

    int numero = 10;

    printMensagemColoridaFormatted(CYAN, "Imprimindo numeros de %d ate 0:\n", numero);

    rastrearDecrescente(numero, 0);

    printf("Sequencia resultante: ");
    imprimirDecrescente(numero);
    printf("\n");

    pausar();
}

void executarQuestaoRecursividade10EntradaManual(void) {
    imprimirCabecalho();

    int numero;

    printf("Digite um numero inteiro nao negativo: ");
    if (scanf("%d", &numero) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (numero < 0) {
        printMensagemColoridaFormatted(RED, "\nInforme um valor >= 0.");
        pausar();
        return;
    }

    printMensagemColoridaFormatted(CYAN, "\nNumeros de %d ate 0:", numero);

    imprimirDecrescente(numero);
    printf("\n");

    pausar();
}
