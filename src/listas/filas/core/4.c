#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "fila_circular.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

static void imprimirFilaCircular(const FilaCircular *fila, const char *titulo) {
    if (titulo) {
        printMensagemColoridaInline(CYAN, titulo);
        printf("\n");
    }

    if (!fila || !fila->dados) {
        printMensagemColoridaFormatted(RED, "  Fila nao inicializada.\n");
        return;
    }

    if (filaCircularVazia(fila)) {
        printMensagemColoridaFormatted(YELLOW, "  (fila vazia)\n");
        return;
    }

    printf("  [ ");
    for (int i = 0; i < fila->tamanho; i++) {
        int indice = (fila->inicio + i) % fila->capacidade;
        printf("%.2f", fila->dados[indice]);
        if (i < fila->tamanho - 1) {
            printf(", ");
        }
    }
    printf(" ]\n");
}

static void demonstrarFuraFilaComDados(const float *dados, size_t quantidade, float novoValor) {
    FilaCircular fila;
    if (!filaCircularInicializar(&fila, (int)(quantidade + 4))) {
        printMensagemColoridaFormatted(RED, "Falha ao alocar fila circular.\n");
        pausar();
        return;
    }

    for (size_t i = 0; i < quantidade; i++) {
        filaCircularEnfileirar(&fila, dados[i]);
    }

    imprimirFilaCircular(&fila, "Fila circular antes do FuraFila:");

    if (!filaCircularFuraFila(&fila, novoValor)) {
        printMensagemColoridaFormatted(RED, "\nNao foi possivel inserir %0.2f: fila cheia.\n", novoValor);
    } else {
        printMensagemColoridaFormatted(GREEN,
            "\nValor %.2f inserido na primeira posicao sem deslocamentos.\n\n",
            novoValor);
        imprimirFilaCircular(&fila, "Fila circular apos FuraFila:");
    }

    filaCircularLiberar(&fila);
    pausar();
}

void executarQuestaoFilas4Predefinido(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Filas - Questao 04 ===");
    printf("\nInsercao O(1) na primeira posicao de uma fila circular.\n\n");

    const float valores[] = {10.0f, 20.0f, 30.0f, 40.0f};
    demonstrarFuraFilaComDados(valores, sizeof(valores) / sizeof(valores[0]), 99.9f);
}

static int preencherFilaCircularManual(FilaCircular *fila) {
    int capacidade = 0;
    printMensagemColoridaInline(GREEN, "Capacidade total da fila (1 a 30)");
    printf(": ");
    if (scanf("%d", &capacidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida.\n");
        return 0;
    }
    limparBufferTeclado();

    if (capacidade < 1 || capacidade > 30) {
        printMensagemColoridaFormatted(RED, "\nCapacidade fora da faixa permitida.\n");
        return 0;
    }

    if (!filaCircularInicializar(fila, capacidade)) {
        printMensagemColoridaFormatted(RED, "\nFalha ao alocar fila circular.\n");
        return 0;
    }

    int quantidade = 0;
    printMensagemColoridaInline(GREEN, "Quantos valores deseja inserir inicialmente");
    printf(" (0 a %d): ", capacidade);
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida.\n");
        return 0;
    }
    limparBufferTeclado();

    if (quantidade < 0 || quantidade > capacidade) {
        printMensagemColoridaFormatted(RED, "\nQuantidade fora da faixa permitida.\n");
        return 0;
    }

    for (int i = 0; i < quantidade; i++) {
        float valor = 0.0f;
        printf("  Valor %d: ", i + 1);
        if (scanf("%f", &valor) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "\nEntrada invalida.\n");
            return 0;
        }
        limparBufferTeclado();
        filaCircularEnfileirar(fila, valor);
    }

    return 1;
}

void executarQuestaoFilas4EntradaManual(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Filas - Questao 04 (Valores informados) ===");
    printf("\nMonte a fila circular e aplique o FuraFila.\n\n");

    FilaCircular fila = {0};
    if (!preencherFilaCircularManual(&fila)) {
        filaCircularLiberar(&fila);
        pausar();
        return;
    }

    imprimirFilaCircular(&fila, "Fila montada:");

    float novoValor = 0.0f;
    printMensagemColoridaInline(GREEN, "\nValor que deve furar a fila");
    printf(": ");
    if (scanf("%f", &novoValor) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida.\n");
        filaCircularLiberar(&fila);
        pausar();
        return;
    }
    limparBufferTeclado();

    if (!filaCircularFuraFila(&fila, novoValor)) {
        printMensagemColoridaFormatted(RED, "\nNao foi possivel inserir: fila cheia.\n");
    } else {
        printMensagemColoridaFormatted(GREEN, "\nInsercao realizada no inicio.\n");
        imprimirFilaCircular(&fila, "\nFila apos FuraFila:");
    }

    filaCircularLiberar(&fila);
    pausar();
}

void executarQuestaoFilas4(void) {
    executarQuestaoFilas4Predefinido();
}
