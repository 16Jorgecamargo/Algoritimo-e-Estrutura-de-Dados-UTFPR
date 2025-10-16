#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"
#include "../../../shared/headlers/animacao.h"

// Questao 5: Inverter vetor e encontrar maior valor

static int inverte_vetor(int *v1, int *v2, int n) {
    int maior = v1[0];

    for (int i = 0; i < n; i++) {
        v2[i] = v1[n - 1 - i];
        if (v1[i] > maior) {
            maior = v1[i];
        }
    }

    return maior;
}

static void imprimirVetor(const int *v, int n, const char* nome) {
    printf("%s = {", nome);
    for (int i = 0; i < n; i++) {
        printf("%d", v[i]);
        if (i < n - 1) printf(", ");
    }
    printf("}\n");
}

static void executarFluxoComVetor(int *v1, int n) {
    int *v2 = (int*)malloc((size_t)n * sizeof(int));
    if (v2 == NULL) {
        printMensagemColorida(RED, "Erro ao alocar memoria auxiliar!");
        pausar();
        return;
    }

    printf("Vetor original:\n");
    imprimirVetor(v1, n, "v1");

    printComAnimacao("Invertendo vetor e buscando maior valor");
    int maior = inverte_vetor(v1, v2, n);

    printf("\nVetor invertido:\n");
    imprimirVetor(v2, n, "v2");

    printf("\n");
    printMensagemColoridaFormatted(GREEN, "Maior valor encontrado em v1: %d", maior);

    free(v2);
    pausar();
}

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Ponteiros - Questao 05 ===");
    printf("\n");
}

void executarQuestaoPonteiros5(void) {
    executarQuestaoPonteiros5Predefinido();
}

void executarQuestaoPonteiros5Predefinido(void) {
    imprimirCabecalho();

    int v1[] = {3, 5, 2, 1, 6, 2, 7};
    executarFluxoComVetor(v1, (int)(sizeof(v1) / sizeof(v1[0])));
}

void executarQuestaoPonteiros5EntradaManual(void) {
    imprimirCabecalho();

    int n;
    printf("Digite o tamanho do vetor: ");
    if (scanf("%d", &n) != 1) {
        limparBufferTeclado();
        printMensagemColorida(RED, "\nEntrada invalida!\n");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (n <= 0) {
        printMensagemColorida(RED, "\nTamanho invalido!\n");
        pausar();
        return;
    }

    int *v1 = (int*)malloc((size_t)n * sizeof(int));
    if (v1 == NULL) {
        printMensagemColorida(RED, "\nErro ao alocar memoria!\n");
        pausar();
        return;
    }

    printf("\nDigite os %d elementos do vetor:\n", n);
    for (int i = 0; i < n; i++) {
        printf("v1[%d]: ", i);
        if (scanf("%d", &v1[i]) != 1) {
            limparBufferTeclado();
            printMensagemColorida(RED, "\nEntrada invalida!\n");
            free(v1);
            pausar();
            return;
        }
        limparBufferTeclado();
    }

    executarFluxoComVetor(v1, n);

    free(v1);
}
