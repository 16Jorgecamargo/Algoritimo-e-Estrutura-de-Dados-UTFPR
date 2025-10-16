#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"
#include "../../../shared/headlers/animacao.h"

// Questao 6: Maximo divisor comum (MDC) com algoritmo de Euclides recursivo

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Recursividade - Questao 06 ===");
    printf("\n");
}

static int mdcRecursivo(int x, int y) {
    if (y == 0) {
        return x;
    }
    return mdcRecursivo(y, x % y);
}

static int rastrearMdc(int x, int y, int nivel) {
    printMensagemColoridaFormatted(YELLOW, "Nivel %d -> mdc(%d, %d)\n", nivel, x, y);

    if (y == 0) {
        printMensagemColoridaFormatted(GREEN, "Caso base (y == 0). Retorna %d\n", x);
        return x;
    }

    int resto = x % y;

    printf("Calcula resto: %d %% %d = %d\n", x, y, resto);
    printf("Proxima chamada: mdc(%d, %d)\n\n", y, resto);

    return rastrearMdc(y, resto, nivel + 1);
}

void executarQuestaoRecursividade6(void) {
    executarQuestaoRecursividade6Predefinido();
}

void executarQuestaoRecursividade6Predefinido(void) {
    imprimirCabecalho();

    int x = 48;
    int y = 18;

    printf("Valores: x = %d, y = %d\n", x, y);
    printComAnimacao("Calculando MDC usando algoritmo de Euclides");
    printf("\n");

    int resultado = rastrearMdc(x, y, 0);

    printMensagemColoridaFormatted(GREEN, "Resultado final: MDC = %d", resultado);

    pausar();
}

void executarQuestaoRecursividade6EntradaManual(void) {
    imprimirCabecalho();

    int x, y;

    printf("Digite o primeiro inteiro positivo: ");
    if (scanf("%d", &x) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }

    printf("Digite o segundo inteiro positivo: ");
    if (scanf("%d", &y) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (x <= 0 || y <= 0) {
        printMensagemColoridaFormatted(RED, "\nInforme valores inteiros positivos.");
        pausar();
        return;
    }

    int resultado = mdcRecursivo(x, y);

    printMensagemColoridaFormatted(CYAN, "\nmdc(%d, %d) = %d\n", x, y, resultado);

    pausar();
}
