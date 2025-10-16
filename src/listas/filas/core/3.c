#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "fila_int.h"
#include "pilha_int.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

static void imprimirFilaIntDetalhada(const FilaInt *fila, const char *titulo) {
    if (titulo) {
        printMensagemColoridaInline(CYAN, titulo);
        printf("\n");
    }

    if (!fila || filaIntVazia(fila)) {
        printMensagemColoridaFormatted(YELLOW, "  (fila vazia)\n");
        return;
    }

    const NoFilaInt *no = fila->inicio;
    size_t pos = 0;
    while (no) {
        printf("  [%zu] -> %d\n", pos, no->valor);
        no = no->prox;
        pos++;
    }
}

static void inverterFilaComPilha(FilaInt *fila) {
    if (!fila || filaIntVazia(fila)) {
        return;
    }

    PilhaInt pilhaAuxiliar;
    pilhaIntInicializar(&pilhaAuxiliar);

    int valor = 0;
    while (filaIntDesenfileirar(fila, &valor)) {
        pilhaIntEmpilhar(&pilhaAuxiliar, valor);
    }

    while (pilhaIntDesempilhar(&pilhaAuxiliar, &valor)) {
        filaIntEnfileirar(fila, valor);
    }

    pilhaIntLiberar(&pilhaAuxiliar);
}

static void preencherFilaComValores(FilaInt *fila, const int *valores, size_t quantidade) {
    for (size_t i = 0; i < quantidade; i++) {
        filaIntEnfileirar(fila, valores[i]);
    }
}

static int preencherFilaManual(FilaInt *fila) {
    int quantidade = 0;
    printMensagemColoridaInline(GREEN, "Quantos elementos deseja inserir (1 a 20)");
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
            return 0;
        }
        limparBufferTeclado();
        filaIntEnfileirar(fila, valor);
    }
    return 1;
}

static void executarQuestaoFilas3ComFila(FilaInt *fila) {
    printf("\n");
    imprimirFilaIntDetalhada(fila, "Fila original:");

    inverterFilaComPilha(fila);

    printMensagemColoridaFormatted(GREEN, "\nFila apos aplicar o inversor baseado em pilha:\n");
    imprimirFilaIntDetalhada(fila, NULL);
    printf("\n");
}

void executarQuestaoFilas3Predefinido(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Filas - Questao 03 ===");
    printf("\nInverter a ordem de uma fila utilizando apenas as operacoes basicas.\n\n");

    FilaInt fila;
    filaIntInicializar(&fila);

    const int valores[] = {5, 12, 19, 25, 33};
    preencherFilaComValores(&fila, valores, sizeof(valores) / sizeof(valores[0]));

    executarQuestaoFilas3ComFila(&fila);

    filaIntLiberar(&fila);
    pausar();
}

void executarQuestaoFilas3EntradaManual(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Filas - Questao 03 (Valores informados) ===");
    printf("\nForneca os elementos que serao invertidos.\n\n");

    FilaInt fila;
    filaIntInicializar(&fila);

    if (!preencherFilaManual(&fila)) {
        filaIntLiberar(&fila);
        pausar();
        return;
    }

    executarQuestaoFilas3ComFila(&fila);

    filaIntLiberar(&fila);
    pausar();
}

void executarQuestaoFilas3(void) {
    executarQuestaoFilas3Predefinido();
}
