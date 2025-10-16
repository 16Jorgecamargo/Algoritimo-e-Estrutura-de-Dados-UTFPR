#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

// Questao 4: Calcular k^n usando apenas multiplicacoes recursivas

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Recursividade - Questao 04 ===");
    printf("\n");
}

static long long potenciaRecursiva(long long base, int expoente) {
    if (expoente == 0) {
        return 1;
    }
    return base * potenciaRecursiva(base, expoente - 1);
}

static long long rastrearPotencia(long long base, int expoente, int nivel) {
    printMensagemColoridaFormatted(YELLOW, "Nivel %d -> potencia(%lld, %d)\n", nivel, base, expoente);

    if (expoente == 0) {
        printMensagemColoridaFormatted(GREEN, "Caso base: retorna 1\n");
        return 1;
    }

    printMensagemColoridaFormatted(CYAN, "Multiplica base (%lld) pela chamada potencia(%lld, %d)\n", base, base, expoente - 1);

    long long parcial = rastrearPotencia(base, expoente - 1, nivel + 1);
    long long resultado = base * parcial;

    printMensagemColoridaFormatted(GREEN, "Retorno ao nivel %d: %lld * %lld = %lld\n", nivel, base, parcial, resultado);

    return resultado;
}

void executarQuestaoRecursividade4(void) {
    executarQuestaoRecursividade4Predefinido();
}

void executarQuestaoRecursividade4Predefinido(void) {
    imprimirCabecalho();

    long long base = 3;
    int expoente = 4;

    printMensagemColoridaFormatted(CYAN, "Exemplo: %lld^%d\n", base, expoente);

    long long resultado = rastrearPotencia(base, expoente, 0);

    printMensagemColoridaFormatted(GREEN, "Resultado final: %lld", resultado);

    pausar();
}

void executarQuestaoRecursividade4EntradaManual(void) {
    imprimirCabecalho();

    long long base;
    int expoente;

    printf("Digite o valor de k (base): ");
    if (scanf("%lld", &base) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }

    printf("Digite o valor de n (expoente >= 0): ");
    if (scanf("%d", &expoente) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (expoente < 0) {
        printMensagemColoridaFormatted(RED, "\nInforme um expoente inteiro nao negativo.");
        pausar();
        return;
    }

    long long resultado = potenciaRecursiva(base, expoente);

    printMensagemColoridaFormatted(CYAN, "\n%lld^%d = %lld", base, expoente, resultado);

    pausar();
}
