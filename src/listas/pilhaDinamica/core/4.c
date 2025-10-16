#include <stdio.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"
#include "pilha_int_utils.h"

static int analisarPilha(PilhaInt *pilha, int *menor, int *maior, double *media) {
    if (pilhaIntVazia(pilha)) {
        return 0;
    }

    PilhaInt auxiliar;
    pilhaIntInicializar(&auxiliar);

    long soma = 0;
    int qtd = 0;
    int valor;

    if (!pilhaIntPop(pilha, &valor)) {
        return 0;
    }
    *menor = *maior = valor;
    soma += valor;
    qtd++;
    pilhaIntPush(&auxiliar, valor);

    while (pilhaIntPop(pilha, &valor)) {
        if (valor < *menor) *menor = valor;
        if (valor > *maior) *maior = valor;
        soma += valor;
        qtd++;
        pilhaIntPush(&auxiliar, valor);
    }

    while (pilhaIntPop(&auxiliar, &valor)) {
        pilhaIntPush(pilha, valor);
    }

    if (media) {
        *media = (double)soma / (double)qtd;
    }
    return 1;
}

static void demonstrarAnalise(void) {
    PilhaInt pilha;
    pilhaIntInicializar(&pilha);

    pilhaIntPush(&pilha, 12);
    pilhaIntPush(&pilha, 7);
    pilhaIntPush(&pilha, 23);
    pilhaIntPush(&pilha, 5);
    pilhaIntPush(&pilha, 17);

    printMensagemColorida(CYAN, "Pilha analisada:");
    pilhaIntImprimir(&pilha);

    int menor, maior;
    double media;
    if (analisarPilha(&pilha, &menor, &maior, &media)) {
        printf("\n");
        printMensagemColoridaFormatted(GREEN, "Menor valor: %d", menor);
        printMensagemColoridaFormatted(GREEN, "Maior valor: %d", maior);
        printMensagemColoridaFormatted(GREEN, "Media aritmetica: %.2f", media);
    }

    printMensagemColorida(GREEN, "\nPilha apos analise (deve permanecer igual):");
    pilhaIntImprimir(&pilha);

    pilhaIntLiberar(&pilha);
}

static void fluxoManual(void) {
    PilhaInt pilha;
    pilhaIntInicializar(&pilha);

    int quantidade;
    printMensagemColoridaInline(YELLOW, "Quantos elementos pretende empilhar? ");
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

    int menor, maior;
    double media;
    if (!analisarPilha(&pilha, &menor, &maior, &media)) {
        printMensagemColoridaFormatted(RED, "\nNao ha elementos na pilha para analisar.");
        pilhaIntLiberar(&pilha);
        pausar();
        return;
    }

    printMensagemColorida(GREEN, "\nResultado da analise:");
    printMensagemColoridaFormatted(GREEN, "Menor valor: %d", menor);
    printMensagemColoridaFormatted(GREEN, "Maior valor: %d", maior);
    printMensagemColoridaFormatted(GREEN, "Media: %.2f", media);

    printMensagemColorida(GREEN, "\nPilha apos analise:");
    pilhaIntImprimir(&pilha);

    pilhaIntLiberar(&pilha);
}

static void cabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Pilha Dinamica - Questao 04 ===");
    printf("\n");
}

void executarQuestaoPilhaDinamica4(void) {
    executarQuestaoPilhaDinamica4Predefinido();
}

void executarQuestaoPilhaDinamica4Predefinido(void) {
    cabecalho();
    demonstrarAnalise();
    pausar();
}

void executarQuestaoPilhaDinamica4EntradaManual(void) {
    cabecalho();
    fluxoManual();
    pausar();
}