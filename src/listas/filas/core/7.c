#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "fila_int.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

static void imprimirFila(const FilaInt *fila, const char *titulo) {
    if (titulo) {
        printMensagemColoridaInline(CYAN, titulo);
        printf("\n");
    }

    printf("  [ ");
    const NoFilaInt *no = fila ? fila->inicio : NULL;
    while (no) {
        printf("%d", no->valor);
        if (no->prox) {
            printf(", ");
        }
        no = no->prox;
    }
    printf(" ]\n");
}

static void reversoRecursivo(FilaInt *fila) {
    if (filaIntVazia(fila)) {
        return;
    }

    int valor = 0;
    filaIntDesenfileirar(fila, &valor);
    reversoRecursivo(fila);
    filaIntEnfileirar(fila, valor);
}

static void preencherFila(FilaInt *fila, const int *valores, size_t quantidade) {
    filaIntInicializar(fila);
    for (size_t i = 0; i < quantidade; i++) {
        filaIntEnfileirar(fila, valores[i]);
    }
}

static int preencherFilaManual(FilaInt *fila) {
    filaIntInicializar(fila);

    int quantidade = 0;
    printMensagemColoridaInline(GREEN, "Quantidade de elementos (1 a 20)");
    printf(": ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida.\n");
        return 0;
    }
    limparBufferTeclado();

    if (quantidade < 1 || quantidade > 20) {
        printMensagemColoridaFormatted(RED, "\nQuantidade fora da faixa permitida.\n");
        return 0;
    }

    for (int i = 0; i < quantidade; i++) {
        int valor = 0;
        printf("  Valor %d: ", i + 1);
        if (scanf("%d", &valor) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "\nEntrada invalida.\n");
            filaIntLiberar(fila);
            return 0;
        }
        limparBufferTeclado();
        filaIntEnfileirar(fila, valor);
    }
    return 1;
}

static void executarReverso(FilaInt *fila) {
    imprimirFila(fila, "\nFila original:");
    reversoRecursivo(fila);
    printMensagemColoridaFormatted(GREEN, "\nFila apos aplicar reverso:\n");
    imprimirFila(fila, NULL);
}

void executarQuestaoFilas7Predefinido(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Filas - Questao 07 ===");
    printf("\nFuncao reverso baseada em recursao e operacoes de fila.\n");

    const int valores[] = {3, 6, 9, 12, 15};
    FilaInt fila;
    preencherFila(&fila, valores, sizeof(valores) / sizeof(valores[0]));

    executarReverso(&fila);

    filaIntLiberar(&fila);
    pausar();
}

void executarQuestaoFilas7EntradaManual(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Filas - Questao 07 (Valores informados) ===");
    printf("\nInforme a fila que sera invertida.\n");

    FilaInt fila;
    if (!preencherFilaManual(&fila)) {
        pausar();
        return;
    }

    executarReverso(&fila);

    filaIntLiberar(&fila);
    pausar();
}

void executarQuestaoFilas7(void) {
    executarQuestaoFilas7Predefinido();
}
