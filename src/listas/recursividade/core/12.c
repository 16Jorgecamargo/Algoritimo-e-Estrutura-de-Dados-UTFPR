#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"
#include "../../../shared/headlers/animacao.h"

// Questao 12: Fatorial duplo de um numero impar positivo

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Recursividade - Questao 12 ===");
    printf("\n");
}

static long long fatorialDuploRecursivo(long long n) {
    if (n <= 1) {
        return 1;
    }
    return n * fatorialDuploRecursivo(n - 2);
}

static long long rastrearFatorialDuplo(long long n, int nivel) {
    printMensagemColoridaFormatted(YELLOW, "Nivel %d -> fatorialDuplo(%lld)", nivel, n);

    if (n <= 1) {
        printMensagemColoridaFormatted(GREEN, "Caso base: retorna 1\n");
        return 1;
    }

    printMensagemColoridaFormatted(CYAN, "Multiplica %lld por fatorialDuplo(%lld)\n", n, n - 2);

    long long parcial = rastrearFatorialDuplo(n - 2, nivel + 1);
    long long resultado = n * parcial;

    printMensagemColoridaFormatted(GREEN, "Retorno ao nivel %d: %lld * %lld = %lld\n", nivel, n, parcial, resultado);

    return resultado;
}

void executarQuestaoRecursividade12(void) {
    executarQuestaoRecursividade12Predefinido();
}

void executarQuestaoRecursividade12Predefinido(void) {
    imprimirCabecalho();

    long long numero = 9;

    printf("Numero: %lld\n", numero);
    printComAnimacao("Calculando fatorial duplo");
    printf("\n");

    long long resultado = rastrearFatorialDuplo(numero, 0);

    printMensagemColoridaFormatted(GREEN, "Resultado final: %lld!! = %lld", numero, resultado);

    pausar();
}

void executarQuestaoRecursividade12EntradaManual(void) {
    imprimirCabecalho();

    long long numero;

    printf("Digite um numero inteiro impar e positivo: ");
    if (scanf("%lld", &numero) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (numero <= 0 || numero % 2 == 0) {
        printMensagemColoridaFormatted(RED, "\nInforme um numero impar positivo.");
        pausar();
        return;
    }

    long long resultado = fatorialDuploRecursivo(numero);

    printf("\n%lld!! = ", numero);
    for (long long i = numero; i > 1; i -= 2) {
        printf("%lld", i);
        if (i - 2 > 1) {
            printf(" * ");
        }
    }
    if (numero > 1) {
        printf(" * 1");
    }
    printf("\n");

    printMensagemColoridaFormatted(GREEN, "Resultado: %lld", resultado);

    pausar();
}
