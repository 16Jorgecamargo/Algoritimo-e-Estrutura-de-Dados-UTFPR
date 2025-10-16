#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "fila_int.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

static void imprimirFilaIntSimples(const FilaInt *fila, const char *titulo) {
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

static void mesclarFilasOrdenadas(const FilaInt *fila1,
                                  const FilaInt *fila2,
                                  FilaInt *resultado) {
    filaIntLiberar(resultado);
    filaIntInicializar(resultado);

    FilaInt copia1;
    FilaInt copia2;
    filaIntInicializar(&copia1);
    filaIntInicializar(&copia2);

    const NoFilaInt *no = fila1 ? fila1->inicio : NULL;
    while (no) {
        filaIntEnfileirar(&copia1, no->valor);
        no = no->prox;
    }
    no = fila2 ? fila2->inicio : NULL;
    while (no) {
        filaIntEnfileirar(&copia2, no->valor);
        no = no->prox;
    }

    int valor1 = 0;
    int valor2 = 0;
    int tem1 = filaIntPrimeiro(&copia1, &valor1);
    int tem2 = filaIntPrimeiro(&copia2, &valor2);

    while (tem1 || tem2) {
        if (!tem2 || (tem1 && valor1 <= valor2)) {
            filaIntDesenfileirar(&copia1, &valor1);
            filaIntEnfileirar(resultado, valor1);
            tem1 = filaIntPrimeiro(&copia1, &valor1);
        } else {
            filaIntDesenfileirar(&copia2, &valor2);
            filaIntEnfileirar(resultado, valor2);
            tem2 = filaIntPrimeiro(&copia2, &valor2);
        }
    }

    filaIntLiberar(&copia1);
    filaIntLiberar(&copia2);
}

static void preencherFilaComArray(FilaInt *fila, const int *valores, size_t quantidade) {
    filaIntInicializar(fila);
    for (size_t i = 0; i < quantidade; i++) {
        filaIntEnfileirar(fila, valores[i]);
    }
}

void executarQuestaoFilas6Predefinido(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Filas - Questao 06 ===");
    printf("\nMerge de duas filas ordenadas em uma terceira fila.\n\n");

    FilaInt filaA;
    FilaInt filaB;
    FilaInt filaMesclada;
    filaIntInicializar(&filaA);
    filaIntInicializar(&filaB);
    filaIntInicializar(&filaMesclada);

    const int primeira[] = {2, 8, 15, 30};
    const int segunda[] = {1, 10, 18, 41, 50};

    preencherFilaComArray(&filaA, primeira, sizeof(primeira) / sizeof(primeira[0]));
    preencherFilaComArray(&filaB, segunda, sizeof(segunda) / sizeof(segunda[0]));

    imprimirFilaIntSimples(&filaA, "Fila A (ordenada):");
    imprimirFilaIntSimples(&filaB, "Fila B (ordenada):");

    mesclarFilasOrdenadas(&filaA, &filaB, &filaMesclada);

    printMensagemColoridaFormatted(GREEN, "\nFila resultante em ordem crescente:\n");
    imprimirFilaIntSimples(&filaMesclada, NULL);

    filaIntLiberar(&filaA);
    filaIntLiberar(&filaB);
    filaIntLiberar(&filaMesclada);
    pausar();
}

static int preencherFilaManual(FilaInt *fila, const char *nomeFila) {
    filaIntInicializar(fila);

    int quantidade = 0;
    printMensagemColoridaInline(GREEN, "Quantidade de elementos para ");
    printf("%s (1 a 20): ", nomeFila);
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

    printMensagemColoridaFormatted(CYAN,
        "Informe os %d valores em ordem crescente para %s:\n",
        quantidade, nomeFila);

    for (int i = 0; i < quantidade; i++) {
        int valor = 0;
        printf("  %s[%d]: ", nomeFila, i);
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

void executarQuestaoFilas6EntradaManual(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Filas - Questao 06 (Valores informados) ===");
    printf("\nForneca duas filas ja ordenadas para gerar a fila mesclada.\n\n");

    FilaInt filaA;
    FilaInt filaB;
    FilaInt filaMesclada;
    filaIntInicializar(&filaA);
    filaIntInicializar(&filaB);
    filaIntInicializar(&filaMesclada);

    if (!preencherFilaManual(&filaA, "Fila A")) {
        filaIntLiberar(&filaA);
        filaIntLiberar(&filaB);
        filaIntLiberar(&filaMesclada);
        pausar();
        return;
    }

    if (!preencherFilaManual(&filaB, "Fila B")) {
        filaIntLiberar(&filaA);
        filaIntLiberar(&filaB);
        filaIntLiberar(&filaMesclada);
        pausar();
        return;
    }

    imprimirFilaIntSimples(&filaA, "\nFila A:");
    imprimirFilaIntSimples(&filaB, "Fila B:");

    mesclarFilasOrdenadas(&filaA, &filaB, &filaMesclada);

    printMensagemColoridaFormatted(GREEN, "\nFila mesclada em ordem crescente:\n");
    imprimirFilaIntSimples(&filaMesclada, NULL);

    filaIntLiberar(&filaA);
    filaIntLiberar(&filaB);
    filaIntLiberar(&filaMesclada);
    pausar();
}

void executarQuestaoFilas6(void) {
    executarQuestaoFilas6Predefinido();
}
