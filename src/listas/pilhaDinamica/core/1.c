#include <stdio.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"
#include "pilha_int_utils.h"

static int push2(PilhaInt *pilha, int primeiro, int segundo) {
    NoInt *n1 = (NoInt *)malloc(sizeof(NoInt));
    NoInt *n2 = (NoInt *)malloc(sizeof(NoInt));
    if (!n1 || !n2) {
        free(n1);
        free(n2);
        return 0;
    }

    n1->valor = primeiro;
    n1->prox = pilha->topo;

    n2->valor = segundo;
    n2->prox = n1;

    pilha->topo = n2;
    return 1;
}

static int pop2(PilhaInt *pilha, int *primeiro, int *segundo) {
    if (pilhaIntVazia(pilha) || pilha->topo->prox == NULL) {
        return 0;
    }

    NoInt *removido1 = pilha->topo;
    NoInt *removido2 = removido1->prox;

    if (primeiro) *primeiro = removido1->valor;
    if (segundo) *segundo = removido2->valor;

    pilha->topo = removido2->prox;
    free(removido1);
    free(removido2);
    return 1;
}

static void demonstrarPushPop2(void) {
    PilhaInt pilha;
    pilhaIntInicializar(&pilha);

    pilhaIntPush(&pilha, 30);
    pilhaIntPush(&pilha, 20);
    pilhaIntPush(&pilha, 10);

    printMensagemColorida(CYAN, "Pilha inicial:");
    pilhaIntImprimir(&pilha);
    printf("\n");

    printMensagemColorida(GREEN, "Aplicando push2(40, 50)...");
    push2(&pilha, 40, 50);
    pilhaIntImprimir(&pilha);
    printf("\n");

    int removidoTopo = 0, removidoSeguinte = 0;
    printMensagemColorida(GREEN, "Aplicando pop2()...");
    if (pop2(&pilha, &removidoTopo, &removidoSeguinte)) {
        printMensagemColoridaFormatted(GREEN, "Elementos removidos: %d (topo) e %d", removidoTopo, removidoSeguinte);
    } else {
        printMensagemColorida(RED, "Nao ha elementos suficientes para pop2.");
    }
    pilhaIntImprimir(&pilha);

    pilhaIntLiberar(&pilha);
}

static void fluxoManual(void) {
    PilhaInt pilha;
    pilhaIntInicializar(&pilha);

    int quantidade;
    printMensagemColoridaInline(YELLOW, "Quantos valores deseja empilhar inicialmente? ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColorida(RED, "Entrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    for (int i = 0; i < quantidade; i++) {
        int valor;
        printf("Valor %d: ", i + 1);
        if (scanf("%d", &valor) != 1) {
            limparBufferTeclado();
            valor = 0;
        } else {
            limparBufferTeclado();
        }
        pilhaIntPush(&pilha, valor);
    }

    printMensagemColorida(CYAN, "Pilha informada:");
    pilhaIntImprimir(&pilha);

    int primeiro, segundo;
    printMensagemColoridaInline(YELLOW, "Informe o primeiro valor para push2: ");
    if (scanf("%d", &primeiro) != 1) {
        limparBufferTeclado();
        printMensagemColorida(RED, "Entrada invalida!");
        pilhaIntLiberar(&pilha);
        pausar();
        return;
    }
    printMensagemColoridaInline(YELLOW, "Informe o segundo valor para push2: ");
    if (scanf("%d", &segundo) != 1) {
        limparBufferTeclado();
        printMensagemColorida(RED, "Entrada invalida!");
        pilhaIntLiberar(&pilha);
        pausar();
        return;
    }
    limparBufferTeclado();

    if (push2(&pilha, primeiro, segundo)) {
        printMensagemColorida(GREEN, "Pilha apos push2:");
        pilhaIntImprimir(&pilha);
    } else {
        printMensagemColorida(RED, "Falha ao empilhar os dois valores.");
    }

    int removidoTopo = 0, removidoSeguinte = 0;
    if (pop2(&pilha, &removidoTopo, &removidoSeguinte)) {
        printMensagemColoridaFormatted(GREEN, "pop2 removeu %d (topo) e %d.", removidoTopo, removidoSeguinte);
    } else {
        printMensagemColorida(RED, "Nao ha elementos suficientes para pop2.");
    }

    printMensagemColorida(CYAN, "Estado final da pilha:");
    pilhaIntImprimir(&pilha);

    pilhaIntLiberar(&pilha);
}

static void cabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Pilha Dinamica - Questao 01 ===");
    printf("\n");
}

void executarQuestaoPilhaDinamica1(void) {
    executarQuestaoPilhaDinamica1Predefinido();
}

void executarQuestaoPilhaDinamica1Predefinido(void) {
    cabecalho();
    demonstrarPushPop2();
    pausar();
}

void executarQuestaoPilhaDinamica1EntradaManual(void) {
    cabecalho();
    fluxoManual();
    pausar();
}
