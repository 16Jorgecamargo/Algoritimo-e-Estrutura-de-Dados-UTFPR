#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

// Questao 2: Somatorio de elementos de um vetor usando recursao

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Recursividade - Questao 02 ===");
    printf("\n");
}

static int somarVetorRecursivo(const int *vetor, int tamanho) {
    if (tamanho == 0) {
        return 0;
    }
    return vetor[0] + somarVetorRecursivo(vetor + 1, tamanho - 1);
}

static int rastrearSomatorio(const int *vetor, int tamanho, int profundidade, int indice) {
    printMensagemColoridaFormatted(YELLOW, "Nivel %d -> soma(%d elementos)", profundidade, tamanho);

    if (tamanho == 0) {
        printMensagemColoridaFormatted(GREEN, "Caso base atingido: retorno 0\n");
        return 0;
    }

    printMensagemColoridaFormatted(CYAN, "Elemento atual: vetor[%d] = %d", indice, vetor[0]);

    int parcial = rastrearSomatorio(vetor + 1, tamanho - 1, profundidade + 1, indice + 1);
    int resultado = vetor[0] + parcial;

    printMensagemColoridaFormatted(GREEN, "Retornando ao nivel %d: %d + %d = %d\n", profundidade, vetor[0], parcial, resultado);

    return resultado;
}

static void imprimirVetor(const int *vetor, int tamanho) {
    printf("{");
    for (int i = 0; i < tamanho; i++) {
        printf("%d", vetor[i]);
        if (i < tamanho - 1) {
            printf(", ");
        }
    }
    printf("}");
}

void executarQuestaoRecursividade2(void) {
    executarQuestaoRecursividade2Predefinido();
}

void executarQuestaoRecursividade2Predefinido(void) {
    imprimirCabecalho();

    int vetor[] = {1, 2, 3, 4, 7, 9, 10};
    int tamanho = (int)(sizeof(vetor) / sizeof(vetor[0]));

    printMensagemColoridaInline(CYAN, "Vetor de exemplo: ");
    imprimirVetor(vetor, tamanho);
    printf("\n\n");

    int soma = rastrearSomatorio(vetor, tamanho, 0, 0);

    printMensagemColoridaFormatted(GREEN, "Resultado final: %d\n", soma);

    pausar();
}

void executarQuestaoRecursividade2EntradaManual(void) {
    imprimirCabecalho();

    const int MAX_ELEMENTOS = 50;
    int vetor[MAX_ELEMENTOS];
    int tamanho;

    printf("Informe o tamanho do vetor (1 a %d): ", MAX_ELEMENTOS);
    if (scanf("%d", &tamanho) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!\n");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (tamanho <= 0 || tamanho > MAX_ELEMENTOS) {
        printMensagemColoridaFormatted(RED, "\nTamanho fora do intervalo permitido!\n");
        pausar();
        return;
    }

    printMensagemColoridaFormatted(CYAN, "\nDigite os %d elementos:\n", tamanho);
    for (int i = 0; i < tamanho; i++) {
        printf("Elemento %d: ", i + 1);
        if (scanf("%d", &vetor[i]) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "\nEntrada invalida! Encerrando operacao.\n");
            pausar();
            return;
        }
        limparBufferTeclado();
    }

    int soma = somarVetorRecursivo(vetor, tamanho);

    printMensagemColoridaInline(CYAN, "\nVetor informado: ");
    imprimirVetor(vetor, tamanho);
    printf("\n");

    printMensagemColoridaFormatted(GREEN, "Somatorio recursivo: %d\n", soma);

    pausar();
}
