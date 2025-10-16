#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

typedef struct NoInt {
    int valor;
    struct NoInt* proximo;
} NoInt;

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Listas - Questao 03 ===");
    printf("\n");
}

static NoInt* criarNo(int valor) {
    NoInt* novo = (NoInt*)malloc(sizeof(NoInt));
    if (!novo) {
        return NULL;
    }
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

static bool inserirFim(NoInt** inicio, int valor) {
    NoInt* novo = criarNo(valor);
    if (!novo) {
        return false;
    }
    if (*inicio == NULL) {
        *inicio = novo;
        return true;
    }
    NoInt* atual = *inicio;
    while (atual->proximo) {
        atual = atual->proximo;
    }
    atual->proximo = novo;
    return true;
}

static int contarElementos(const NoInt* inicio) {
    int contador = 0;
    for (const NoInt* atual = inicio; atual; atual = atual->proximo) {
        contador++;
    }
    return contador;
}

static bool inserirNaPosicao(NoInt** inicio, int valor, int posicao) {
    if (posicao < 1) {
        return false;
    }
    NoInt* novo = criarNo(valor);
    if (!novo) {
        return false;
    }

    if (posicao == 1) {
        novo->proximo = *inicio;
        *inicio = novo;
        return true;
    }

    NoInt* atual = *inicio;
    int indice = 1;
    while (atual && indice < posicao - 1) {
        atual = atual->proximo;
        indice++;
    }

    if (!atual) {
        free(novo);
        return false;
    }

    novo->proximo = atual->proximo;
    atual->proximo = novo;
    return true;
}

static void imprimirLista(const NoInt* inicio) {
    printf("[ ");
    for (const NoInt* atual = inicio; atual; atual = atual->proximo) {
        printf("%d", atual->valor);
        if (atual->proximo) {
            printf(" -> ");
        }
    }
    printf(" ]\n");
}

static void liberarLista(NoInt** inicio) {
    NoInt* atual = *inicio;
    while (atual) {
        NoInt* temp = atual->proximo;
        free(atual);
        atual = temp;
    }
    *inicio = NULL;
}

static void preencherLista(NoInt** lista, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printMensagemColoridaInline(YELLOW, "Valor ");
        printf("%d: ", i + 1);
        int valor;
        if (scanf("%d", &valor) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "Entrada invalida. Abortando preenchimento.");
            liberarLista(lista);
            return;
        }
        limparBufferTeclado();
        if (!inserirFim(lista, valor)) {
            printMensagemColoridaFormatted(RED, "Falha ao alocar memoria. Abortando preenchimento.");
            liberarLista(lista);
            return;
        }
    }
}

void executarQuestaoListas3(void) {
    executarQuestaoListas3Predefinido();
}

void executarQuestaoListas3Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: insercao na posicao desejada.");
    printf("\n");

    NoInt* lista = NULL;
    int valoresBase[] = {3, 6, 9, 12};
    for (size_t i = 0; i < sizeof(valoresBase) / sizeof(valoresBase[0]); i++) {
        inserirFim(&lista, valoresBase[i]);
    }

    printMensagemColoridaFormatted(CYAN, "Lista original:");
    imprimirLista(lista);

    int valorInserir = 99;
    int posicao = 3;
    if (inserirNaPosicao(&lista, valorInserir, posicao)) {
        printMensagemColoridaFormatted(GREEN, "\nValor %d inserido na posicao %d.", valorInserir, posicao);
    } else {
        printMensagemColoridaFormatted(RED, "\nFalha ao inserir valor na posicao desejada.");
    }
    printMensagemColoridaFormatted(CYAN, "Lista apos insercao:");
    imprimirLista(lista);

    liberarLista(&lista);
    pausar();
}

void executarQuestaoListas3EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: insira elementos e escolha a posicao de insercao.");
    printf("\n");

    int quantidade;
    printMensagemColoridaInline(YELLOW, "Informe a quantidade inicial de elementos (0 a 25): ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (quantidade < 0 || quantidade > 25) {
        printMensagemColoridaFormatted(RED, "Quantidade fora do intervalo permitido.");
        pausar();
        return;
    }

    NoInt* lista = NULL;
    if (quantidade > 0) {
        preencherLista(&lista, quantidade);
        if (lista == NULL) {
            pausar();
            return;
        }
    }

    printf("\n");
    printMensagemColoridaFormatted(CYAN, "Lista atual:");
    imprimirLista(lista);

    int valorInserir;
    printMensagemColoridaInline(YELLOW, "\nInforme o valor a inserir: ");
    if (scanf("%d", &valorInserir) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        liberarLista(&lista);
        pausar();
        return;
    }
    limparBufferTeclado();

    int tamanhoAtual = contarElementos(lista);
    int posicao;
    printMensagemColoridaInline(YELLOW, "Informe a posicao desejada ");
    printf("(1 a %d): ", tamanhoAtual + 1);
    if (scanf("%d", &posicao) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        liberarLista(&lista);
        pausar();
        return;
    }
    limparBufferTeclado();

    if (posicao < 1 || posicao > tamanhoAtual + 1) {
        printMensagemColoridaFormatted(RED, "Posicao fora do intervalo permitido.");
        liberarLista(&lista);
        pausar();
        return;
    }

    if (inserirNaPosicao(&lista, valorInserir, posicao)) {
        printMensagemColoridaFormatted(GREEN, "\nValor %d inserido na posicao %d.", valorInserir, posicao);
    } else {
        printMensagemColoridaFormatted(RED, "\nFalha ao inserir valor na posicao %d.", posicao);
    }

    printMensagemColoridaFormatted(CYAN, "Lista final:");
    imprimirLista(lista);

    liberarLista(&lista);
    pausar();
}
