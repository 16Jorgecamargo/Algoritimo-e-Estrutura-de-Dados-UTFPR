#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../index.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/clean.h"
#include "../../../shared/headlers/animacao.h"

// Questao 8: Criar vetor dinamico, preencher via funcao e liberar memoria

static void preencherAleatorio(int *vetor, int n) {
    srand((unsigned int)time(NULL));
    printComAnimacao("Preenchendo vetor com valores aleatorios (1-100)");
    for (int i = 0; i < n; i++) {
        vetor[i] = (rand() % 100) + 1;
    }
    printMensagemColoridaFormatted(GREEN, "Vetor preenchido automaticamente!\n");
}

static void lerVetor(int *vetor, int n) {
    printf("\nDigite os %d elementos do vetor:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Elemento [%d]: ", i);
        if (scanf("%d", &vetor[i]) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "Erro na entrada!\n");
            vetor[i] = 0;
        }
        limparBufferTeclado();
    }
}

static void imprimirVetor(const int *vetor, int n) {
    printMensagemColoridaFormatted(CYAN, "\nVetor preenchido:");
    printf("{");
    for (int i = 0; i < n; i++) {
        printf("%d", vetor[i]);
        if (i < n - 1) printf(", ");
    }
    printf("}\n");
}

static void executarFluxo(int n, int preencherAutomatico) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Ponteiros - Questao 08 ===\n\n");

    int *vetor = (int*)malloc((size_t)n * sizeof(int));
    if (vetor == NULL) {
        printMensagemColoridaFormatted(RED, "Erro ao alocar memoria!\n");
        pausar();
        return;
    }

    printf("Tamanho do vetor: %d\n", n);
    printf("Endereco alocado: %p\n", (void*)vetor);
    printf("Tamanho total: %zu bytes\n", (size_t)n * sizeof(int));

    if (preencherAutomatico) {
        preencherAleatorio(vetor, n);
    } else {
        lerVetor(vetor, n);
    }

    imprimirVetor(vetor, n);

    printf("\n");
    printComAnimacao("Liberando memoria alocada");
    free(vetor);
    printMensagemColoridaFormatted(GREEN, "Memoria liberada com sucesso!\n");

    pausar();
}

void executarQuestaoPonteiros8(void) {
    executarQuestaoPonteiros8Predefinido();
}

void executarQuestaoPonteiros8Predefinido(void) {
    executarFluxo(5, 1);
}

void executarQuestaoPonteiros8EntradaManual(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Ponteiros - Questao 08 ===\n\n");

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
        printMensagemColoridaFormatted(RED, "\nTamanho invalido!");
        pausar();
        return;
    }

    int escolha;
    printf("\nPreencher automaticamente (1) ou informar valores (2)? ");
    if (scanf("%d", &escolha) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    int autoPreencher = (escolha == 1);
    executarFluxo(n, autoPreencher);
}
