#include <stdio.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"
#include "pilha_int_utils.h"

static int pilhasIguais(PilhaInt *a, PilhaInt *b) {
    PilhaInt auxA, auxB;
    pilhaIntInicializar(&auxA);
    pilhaIntInicializar(&auxB);

    int iguais = 1;
    int valorA, valorB;

    while (iguais && pilhaIntPop(a, &valorA)) {
        if (!pilhaIntPop(b, &valorB)) {
            iguais = 0;
            pilhaIntPush(&auxA, valorA);
            break;
        }
        if (valorA != valorB) {
            iguais = 0;
        }
        pilhaIntPush(&auxA, valorA);
        pilhaIntPush(&auxB, valorB);
    }

    if (pilhaIntVazia(&auxA) && !pilhaIntVazia(b)) {
        iguais = 0;
    }

    while (pilhaIntPop(b, &valorB)) {
        pilhaIntPush(&auxB, valorB);
        iguais = 0;
    }

    while (pilhaIntPop(&auxA, &valorA)) {
        pilhaIntPush(a, valorA);
    }
    while (pilhaIntPop(&auxB, &valorB)) {
        pilhaIntPush(b, valorB);
    }

    return iguais;
}

static void demonstrarComparacao(void) {
    PilhaInt p1, p2;
    pilhaIntInicializar(&p1);
    pilhaIntInicializar(&p2);

    int valores[] = {5, 4, 3, 2, 1};
    for (int i = 0; i < 5; i++) {
        pilhaIntPush(&p1, valores[i]);
        pilhaIntPush(&p2, valores[i]);
    }

    printMensagemColoridaInline(CYAN, "");
    pilhaIntImprimir(&p1);
    printMensagemColoridaInline(CYAN, "");
    pilhaIntImprimir(&p2);

    printMensagemColoridaFormatted(GREEN, "\nComparando pilha A e pilha B...");
    printf("Resultado: %s\n", pilhasIguais(&p1, &p2) ? "Pilhas iguais" : "Pilhas diferentes");

    pilhaIntPop(&p2, NULL);
    pilhaIntPush(&p2, 99);

    printf("\nAlterando topo da pilha B para 99...\n");
    printMensagemColoridaInline(CYAN, "");
    pilhaIntImprimir(&p1);
    printMensagemColoridaInline(CYAN, "");
    pilhaIntImprimir(&p2);

    printMensagemColoridaFormatted(GREEN, "Resultado: %s", pilhasIguais(&p1, &p2) ? "Pilhas iguais" : "Pilhas diferentes");

    pilhaIntLiberar(&p1);
    pilhaIntLiberar(&p2);
}

static void fluxoManual(void) {
    PilhaInt p1, p2;
    pilhaIntInicializar(&p1);
    pilhaIntInicializar(&p2);

    int quantidade;
    printf("Quantos elementos tera a pilha A? ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Erro na entrada!\n");
        pausar();
        return;
    }
    limparBufferTeclado();

    for (int i = 0; i < quantidade; i++) {
        int valor;
        printf("A[%d]: ", i + 1);
        if (scanf("%d", &valor) != 1) {
            limparBufferTeclado();
            valor = 0;
        } else {
            limparBufferTeclado();
        }
        pilhaIntPush(&p1, valor);
    }

    printf("\nQuantos elementos tera a pilha B? ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColorida(RED, "Entrada invalida!");
        pilhaIntLiberar(&p1);
        pausar();
        return;
    }
    limparBufferTeclado();

    for (int i = 0; i < quantidade; i++) {
        int valor;
        printf("B[%d]: ", i + 1);
        if (scanf("%d", &valor) != 1) {
            limparBufferTeclado();
            valor = 0;
        } else {
            limparBufferTeclado();
        }
        pilhaIntPush(&p2, valor);
    }

    printf("\nResultado: %s\n", pilhasIguais(&p1, &p2) ? "Pilhas iguais" : "Pilhas diferentes");

    printf("\nPilha A:\n");
    pilhaIntImprimir(&p1);
    printf("Pilha B:\n");
    pilhaIntImprimir(&p2);

    pilhaIntLiberar(&p1);
    pilhaIntLiberar(&p2);
}

static void cabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Pilha Dinamica - Questao 05 ===");
    printf("\n");
}

void executarQuestaoPilhaDinamica5(void) {
    executarQuestaoPilhaDinamica5Predefinido();
}

void executarQuestaoPilhaDinamica5Predefinido(void) {
    cabecalho();
    demonstrarComparacao();
    pausar();
}

void executarQuestaoPilhaDinamica5EntradaManual(void) {
    cabecalho();
    fluxoManual();
    pausar();
}
