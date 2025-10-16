#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

// Questao 3: Somatorio de 1 ate N usando recursao

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Recursividade - Questao 03 ===");
    printf("\n");
}

static long long somatorioRecursivo(long long n) {
    if (n <= 0) {
        return 0;
    }
    return n + somatorioRecursivo(n - 1);
}

static long long rastrearSomatorio(long long n, int nivel) {
    printMensagemColoridaFormatted(YELLOW, "Nivel %d -> somatorio(%lld)", nivel, n);

    if (n <= 0) {
        printMensagemColoridaFormatted(GREEN, "Caso base atingido: retorna 0\n");
        return 0;
    }

    printMensagemColoridaFormatted(CYAN, "Resolve subproblema: somatorio(%lld)", n - 1);

    long long parcial = rastrearSomatorio(n - 1, nivel + 1);
    long long resultado = n + parcial;

    printMensagemColoridaFormatted(GREEN, "Retorno ao nivel %d: %lld + %lld = %lld\n", nivel, n, parcial, resultado);

    return resultado;
}

void executarQuestaoRecursividade3(void) {
    executarQuestaoRecursividade3Predefinido();
}

void executarQuestaoRecursividade3Predefinido(void) {
    imprimirCabecalho();

    long long numero = 5;
    printMensagemColoridaFormatted(CYAN, "Numero de exemplo: %lld\n", numero);

    long long soma = rastrearSomatorio(numero, 0);

    printMensagemColoridaFormatted(GREEN, "Resultado final: %lld", soma);

    pausar();
}

void executarQuestaoRecursividade3EntradaManual(void) {
    imprimirCabecalho();

    long long numero;
    printf("Digite um numero inteiro positivo: ");
    if (scanf("%lld", &numero) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (numero < 0) {
        printMensagemColoridaFormatted(RED, "\nInforme um valor nao negativo.");
        pausar();
        return;
    }

    long long soma = somatorioRecursivo(numero);

    printMensagemColoridaFormatted(CYAN, "\nSomatorio de 1 ate %lld = %lld", numero, soma);

    pausar();
}
