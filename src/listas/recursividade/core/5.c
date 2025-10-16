#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

// Questao 5: Inverter vetor de numeros reais via recursao

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Recursividade - Questao 05 ===");
    printf("\n");
}

static void imprimirVetor(const double *vetor, int tamanho) {
    printf("{");
    for (int i = 0; i < tamanho; i++) {
        printf("%.2f", vetor[i]);
        if (i < tamanho - 1) {
            printf(", ");
        }
    }
    printf("}");
}

static void inverterVetorRecursivo(double *vetor, int inicio, int fim) {
    if (inicio >= fim) {
        return;
    }

    double temp = vetor[inicio];
    vetor[inicio] = vetor[fim];
    vetor[fim] = temp;

    inverterVetorRecursivo(vetor, inicio + 1, fim - 1);
}

static void rastrearInversao(double *vetor, int inicio, int fim, int nivel, int tamanhoTotal) {
    printMensagemColoridaFormatted(YELLOW, "Nivel %d -> inverter(%d, %d)\n", nivel, inicio, fim);

    if (inicio >= fim) {
        printMensagemColoridaFormatted(GREEN, "Caso base atingido (inicio >= fim). Nenhuma troca necessaria.\n");
        return;
    }

    printMensagemColoridaFormatted(CYAN, "Troca vetor[%d] (%.2f) com vetor[%d] (%.2f)", inicio, vetor[inicio], fim, vetor[fim]);

    double temp = vetor[inicio];
    vetor[inicio] = vetor[fim];
    vetor[fim] = temp;

    printf("Vetor parcial: ");
    imprimirVetor(vetor, tamanhoTotal);
    printf("\n\n");

    rastrearInversao(vetor, inicio + 1, fim - 1, nivel + 1, tamanhoTotal);
}

void executarQuestaoRecursividade5(void) {
    executarQuestaoRecursividade5Predefinido();
}

void executarQuestaoRecursividade5Predefinido(void) {
    imprimirCabecalho();

    double vetor[] = {3.30, 1.50, 7.80, 5.50, 4.20};
    int tamanho = (int)(sizeof(vetor) / sizeof(vetor[0]));

    printf("Vetor original: ");
    imprimirVetor(vetor, tamanho);
    printf("\n\n");

    rastrearInversao(vetor, 0, tamanho - 1, 0, tamanho);

    printf("Vetor invertido: ");
    imprimirVetor(vetor, tamanho);
    printf("\n");

    pausar();
}

void executarQuestaoRecursividade5EntradaManual(void) {
    imprimirCabecalho();

    const int MAX_ELEMENTOS = 100;
    int tamanho;

    printf("Informe o tamanho do vetor (1 a %d): ", MAX_ELEMENTOS);
    if (scanf("%d", &tamanho) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (tamanho <= 0 || tamanho > MAX_ELEMENTOS) {
        printMensagemColoridaFormatted(RED, "\nTamanho fora do intervalo permitido.");
        pausar();
        return;
    }

    double *vetor = (double *)malloc((size_t)tamanho * sizeof(double));
    if (vetor == NULL) {
        printMensagemColoridaFormatted(RED, "\nFalha ao alocar memoria.");
        pausar();
        return;
    }

    printMensagemColoridaFormatted(CYAN, "\nDigite os %d valores:", tamanho);

    for (int i = 0; i < tamanho; i++) {
        printf("Elemento %d: ", i + 1);
        if (scanf("%lf", &vetor[i]) != 1) {
            limparBufferTeclado();
            free(vetor);
            printMensagemColoridaFormatted(RED, "\nEntrada invalida! Encerrando operacao.");
            pausar();
            return;
        }
        limparBufferTeclado();
    }

    printf("\nVetor informado: ");
    imprimirVetor(vetor, tamanho);
    printf("\n");

    inverterVetorRecursivo(vetor, 0, tamanho - 1);

    printf("Vetor invertido: ");
    imprimirVetor(vetor, tamanho);
    printf("\n");

    free(vetor);
    pausar();
}
