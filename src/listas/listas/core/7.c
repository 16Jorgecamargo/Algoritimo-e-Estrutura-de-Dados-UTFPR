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
    printMensagemColoridaFormatted(YELLOW, "=== Listas - Questao 07 ===");
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

static void liberarLista(NoInt** inicio) {
    NoInt* atual = *inicio;
    while (atual) {
        NoInt* temp = atual->proximo;
        free(atual);
        atual = temp;
    }
    *inicio = NULL;
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

static int removerDuplicados(NoInt* inicio) {
    int removidos = 0;
    for (NoInt* atual = inicio; atual; atual = atual->proximo) {
        NoInt* anterior = atual;
        NoInt* cursor = atual->proximo;
        while (cursor) {
            if (cursor->valor == atual->valor) {
                anterior->proximo = cursor->proximo;
                free(cursor);
                cursor = anterior->proximo;
                removidos++;
            } else {
                anterior = cursor;
                cursor = cursor->proximo;
            }
        }
    }
    return removidos;
}

static bool preencherLista(NoInt** lista, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printMensagemColoridaInline(YELLOW, "Valor ");
        printf("%d: ", i + 1);
        int valor;
        if (scanf("%d", &valor) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "Entrada invalida. Abortando preenchimento.");
            liberarLista(lista);
            return false;
        }
        limparBufferTeclado();
        if (!inserirFim(lista, valor)) {
            printMensagemColoridaFormatted(RED, "Falha ao alocar memoria. Abortando preenchimento.");
            liberarLista(lista);
            return false;
        }
    }
    return true;
}

void executarQuestaoListas7(void) {
    executarQuestaoListas7Predefinido();
}

void executarQuestaoListas7Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: remover elementos repetidos preservando a primeira ocorrencia.");
    printf("\n");

    NoInt* lista = NULL;
    int valores[] = {5, 3, 5, 2, 3, 7, 2};
    for (size_t i = 0; i < sizeof(valores) / sizeof(valores[0]); i++) {
        inserirFim(&lista, valores[i]);
    }

    printMensagemColoridaFormatted(CYAN, "Lista original:");
    imprimirLista(lista);

    int removidos = removerDuplicados(lista);
    printf("\n");
    printMensagemColoridaFormatted(GREEN, "%d duplicata(s) removida(s).", removidos);

    printMensagemColoridaFormatted(CYAN, "Lista apos a eliminacao de duplicados:");
    imprimirLista(lista);

    liberarLista(&lista);
    pausar();
}

void executarQuestaoListas7EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: remocao de duplicatas mantendo a primeira ocorrencia.");
    printf("\n");

    int quantidade;
    printMensagemColoridaInline(YELLOW, "Informe a quantidade de elementos da lista (0 a 35): ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (quantidade < 0 || quantidade > 35) {
        printMensagemColoridaFormatted(RED, "Quantidade fora do intervalo permitido.");
        pausar();
        return;
    }

    NoInt* lista = NULL;
    if (!preencherLista(&lista, quantidade)) {
        pausar();
        return;
    }

    printf("\n");
    printMensagemColoridaFormatted(CYAN, "Lista original:");
    imprimirLista(lista);

    int removidos = removerDuplicados(lista);
    printf("\n");
    if (removidos > 0) {
        printMensagemColoridaFormatted(GREEN, "%d duplicata(s) eliminada(s).", removidos);
    } else {
        printMensagemColoridaFormatted(GREEN, "Nenhum elemento duplicado encontrado.");
    }

    printMensagemColoridaFormatted(CYAN, "Lista final:");
    imprimirLista(lista);

    liberarLista(&lista);
    pausar();
}
