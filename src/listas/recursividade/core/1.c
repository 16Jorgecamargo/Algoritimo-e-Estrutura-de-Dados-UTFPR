#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

// Questao 1: Inverter numero inteiro utilizando recursao

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Recursividade - Questao 01 ===");
    printf("\n");
}

static unsigned long long inverterRec(unsigned long long n, unsigned long long acumulado) {
    if (n == 0) {
        return acumulado;
    }
    return inverterRec(n / 10, acumulado * 10 + (n % 10));
}

static void exibirPassosInversao(unsigned long long n) {
    printMensagemColoridaFormatted(CYAN, "RASTREAMENTO DAS CHAMADAS RECURSIVAS\n");

    unsigned long long restante = n;
    unsigned long long acumulado = 0;
    int nivel = 0;

    while (1) {
        printMensagemColoridaFormatted(YELLOW, "Nivel %d -> inverterRec(%llu, %llu)\n", nivel, restante, acumulado);

        if (restante == 0) {
            printMensagemColoridaFormatted(GREEN, "Base atingida: retorna %llu\n", acumulado);
            break;
        }

        unsigned long long digito = restante % 10;
        unsigned long long proximoAcumulado = acumulado * 10 + digito;
        unsigned long long proximoNumero = restante / 10;

        printf("   Extrai ultimo digito: %llu\n", digito);
        printf("   Atualiza acumulado : %llu * 10 + %llu = %llu\n", acumulado, digito, proximoAcumulado);

        printMensagemColoridaFormatted(GREEN, "   Proxima chamada -> inverterRec(%llu, %llu)\n\n", proximoNumero, proximoAcumulado);

        acumulado = proximoAcumulado;
        restante = proximoNumero;
        nivel++;
    }
}

void executarQuestaoRecursividade1(void) {
    executarQuestaoRecursividade1Predefinido();
}

void executarQuestaoRecursividade1Predefinido(void) {
    imprimirCabecalho();

    unsigned long long numero = 12345ULL;
    unsigned long long invertido = inverterRec(numero, 0);

    printMensagemColoridaFormatted(CYAN, "Numero escolhido: %llu\n", numero);

    exibirPassosInversao(numero);

    printMensagemColoridaFormatted(GREEN, "Resultado final: %llu", invertido);

    printf("\nDica: voce pode tentar novamente com qualquer outro numero no menu!\n");

    pausar();
}

void executarQuestaoRecursividade1EntradaManual(void) {
    imprimirCabecalho();

    long long entrada;
    printMensagemColoridaInline(YELLOW, "Digite um numero inteiro (positivo ou negativo): ");
    if (scanf("%lld", &entrada) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    unsigned long long valorAbsoluto = (entrada < 0) ? (unsigned long long)(-entrada) : (unsigned long long)entrada;
    unsigned long long invertido = inverterRec(valorAbsoluto, 0);

    printMensagemColoridaFormatted(CYAN, "\nNumero original : %lld\n", entrada);
    printMensagemColoridaInline(CYAN, "Numero invertido: ");
    if (entrada < 0 && invertido != 0) {
        printf("-");
    }
    printf("%llu\n", invertido);

    printMensagemColoridaFormatted(GREEN, "\nProcesso concluido com sucesso!\n");

    pausar();
}
