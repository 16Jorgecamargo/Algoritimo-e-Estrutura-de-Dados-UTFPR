#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"
#include "../../../shared/headlers/animacao.h"

// Questao 4: Alocacao dinamica de vetor

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Ponteiros - Questao 04 ===");
    printf("\n");
}

static int* criarVetor(int n) {
    int* v = (int*)malloc((size_t)n * sizeof(int));
    if (v == NULL) {
        printMensagemColoridaFormatted(RED, "Erro ao alocar memoria!\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        v[i] = i + 1;
    }

    return v;
}

static void imprimirVetor(const int* v, int n) {
    printf("v[%d] = {", n);
    for (int i = 0; i < n; i++) {
        printf("%d", v[i]);
        if (i < n - 1) printf(", ");
    }
    printf("}\n");
}

static void executarFluxo(int n) {
    imprimirCabecalho();

    printMensagemColoridaFormatted(GREEN, "Tamanho do vetor: %d\n", n);

    printComAnimacao("Alocando vetor dinamicamente com malloc");
    int* vetor = criarVetor(n);

    if (vetor != NULL) {
        printf("Vetor alocado com sucesso!\n");
        printf("Endereco do vetor: %p\n", (void*)vetor);
        printf("Tamanho total: %zu bytes\n\n", (size_t)n * sizeof(int));

        printf("Vetor preenchido:\n");
        imprimirVetor(vetor, n);

        printf("\n");
        printComAnimacao("Liberando memoria com free()");
        free(vetor);
        printf("Memoria liberada com sucesso!\n");
    }

    pausar();
}

void executarQuestaoPonteiros4(void) {
    executarQuestaoPonteiros4Predefinido();
}

void executarQuestaoPonteiros4Predefinido(void) {
    executarFluxo(9);
}

void executarQuestaoPonteiros4EntradaManual(void) {
    imprimirCabecalho();

    int n;
    printf("Digite o tamanho do vetor: ");
    if (scanf("%d", &n) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (n <= 0) {
        printMensagemColoridaFormatted(RED, "\nTamanho invalido! Deve ser maior que zero.");
        pausar();
        return;
    }

    executarFluxo(n);
}
