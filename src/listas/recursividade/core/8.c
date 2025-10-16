#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

// Questao 8: Multiplicacao por somas sucessivas (recursiva)

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Recursividade - Questao 08 ===");
    printf("\n");
}

static long long multiplicacaoRecursivaPositiva(long long a, long long b) {
    if (b == 0) {
        return 0;
    }
    return a + multiplicacaoRecursivaPositiva(a, b - 1);
}

static long long multiplicarComSinal(long long a, long long b) {
    int sinal = 1;
    if ((a < 0 && b > 0) || (a > 0 && b < 0)) {
        sinal = -1;
    }

    long long multiplicando = (a < 0) ? -a : a;
    long long multiplicador = (b < 0) ? -b : b;

    long long resultado = multiplicacaoRecursivaPositiva(multiplicando, multiplicador);
    return sinal * resultado;
}

static long long rastrearMultiplicacao(long long a, long long b, int nivel) {
    printMensagemColoridaFormatted(YELLOW, "Nivel %d -> multiplicacao(%lld, %lld)\n", nivel, a, b);

    if (b == 0) {
        printMensagemColoridaFormatted(GREEN, "Caso base: retorna 0\n");
        return 0;
    }

    printMensagemColoridaFormatted(CYAN, "Soma %lld ao resultado da chamada multiplicacao(%lld, %lld)\n", a, a, b - 1);

    long long parcial = rastrearMultiplicacao(a, b - 1, nivel + 1);
    long long resultado = a + parcial;

    printMensagemColoridaFormatted(GREEN, "Retorno ao nivel %d: %lld + %lld = %lld\n", nivel, a, parcial, resultado);

    return resultado;
}

void executarQuestaoRecursividade8(void) {
    executarQuestaoRecursividade8Predefinido();
}

void executarQuestaoRecursividade8Predefinido(void) {
    imprimirCabecalho();

    long long a = 7;
    long long b = 4;

    printMensagemColoridaFormatted(CYAN, "Multiplicando: %lld\nMultiplicador: %lld\n", a, b);

    long long resultado = rastrearMultiplicacao(a, b, 0);

    printMensagemColoridaFormatted(GREEN, "Resultado final: %lld", resultado);

    pausar();
}

void executarQuestaoRecursividade8EntradaManual(void) {
    imprimirCabecalho();

    long long a, b;

    printf("Digite o primeiro numero (multiplicando): ");
    if (scanf("%lld", &a) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }

    printf("Digite o segundo numero (multiplicador >= 0): ");
    if (scanf("%lld", &b) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    long long resultado = multiplicarComSinal(a, b);

    printMensagemColoridaFormatted(CYAN, "\n%lld x %lld = %lld", a, b, resultado);

    printMensagemColoridaFormatted(GREEN, "Calculo concluido!\n");

    pausar();
}
