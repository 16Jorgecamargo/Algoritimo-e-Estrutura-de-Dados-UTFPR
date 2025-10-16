#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

// Questao 7: Contar ocorrencias de um digito K em um numero N (recursivo)

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Recursividade - Questao 07 ===");
    printf("\n");
}

static int contarOcorrencias(unsigned long long n, int digito) {
    if (n == 0) {
        return 0;
    }

    int ultimo = (int)(n % 10ULL);
    int corresponde = (ultimo == digito) ? 1 : 0;
    return corresponde + contarOcorrencias(n / 10ULL, digito);
}

static int rastrearOcorrencias(unsigned long long n, int digito, int nivel) {
    printMensagemColoridaFormatted(YELLOW, "Nivel %d -> contar(%llu)", nivel, n);

    if (n == 0) {
        printMensagemColoridaFormatted(GREEN, "Caso base: retorna 0\n");
        return 0;
    }

    int ultimo = (int)(n % 10ULL);
    int corresponde = (ultimo == digito) ? 1 : 0;

    printf("Ultimo digito: %d (%s %d)\n", ultimo, corresponde ? "==" : "!=", digito);
    printf("Chamada recursiva para %llu\n\n", n / 10ULL);

    int parcial = rastrearOcorrencias(n / 10ULL, digito, nivel + 1);
    int resultado = corresponde + parcial;

    printMensagemColoridaFormatted(GREEN, "Retorno ao nivel %d: %d + %d = %d\n", nivel, corresponde, parcial, resultado);

    return resultado;
}

void executarQuestaoRecursividade7(void) {
    executarQuestaoRecursividade7Predefinido();
}

void executarQuestaoRecursividade7Predefinido(void) {
    imprimirCabecalho();

    unsigned long long numero = 762021192ULL;
    int digito = 2;

    printf("Numero: %llu\n", numero);
    printf("Digito: %d\n\n", digito);

    int resultado;
    if (numero == 0ULL) {
        resultado = (digito == 0) ? 1 : 0;
        printMensagemColoridaFormatted(GREEN, "Numero eh zero. Resultado direto: %d", resultado);
    } else {
        resultado = rastrearOcorrencias(numero, digito, 0);
    }

    printMensagemColoridaFormatted(GREEN, "Total de ocorrencias: %d", resultado);

    pausar();
}

void executarQuestaoRecursividade7EntradaManual(void) {
    imprimirCabecalho();

    long long entradaNumero;
    int digito;

    printf("Digite o numero N (inteiro): ");
    if (scanf("%lld", &entradaNumero) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }

    printf("Digite o digito K (0 a 9): ");
    if (scanf("%d", &digito) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (digito < 0 || digito > 9) {
        printMensagemColoridaFormatted(RED, "\nO digito deve estar entre 0 e 9.");
        pausar();
        return;
    }

    unsigned long long numero = (entradaNumero < 0) ? (unsigned long long)(-entradaNumero) : (unsigned long long)entradaNumero;

    int resultado;
    if (numero == 0ULL) {
        resultado = (digito == 0) ? 1 : 0;
    } else {
        resultado = contarOcorrencias(numero, digito);
    }

    printf("\nNumero analisado: %lld\n", entradaNumero);
    printf("Digito procurado: %d\n", digito);

    printMensagemColoridaFormatted(GREEN, "Total de ocorrencias: %d", resultado);

    pausar();
}
