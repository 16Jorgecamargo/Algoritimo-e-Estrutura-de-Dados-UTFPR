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
    printMensagemColoridaFormatted(YELLOW, "=== Listas - Questao 08 ===");
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

static void imprimirLista(const NoInt* inicio, const char* nome) {
    printMensagemColoridaInline(CYAN, nome);
    printf(": ");
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

static NoInt* fundirListasOrdenadas(NoInt** lista1, NoInt** lista2) {
    NoInt dummy = {0, NULL};
    NoInt* cauda = &dummy;
    NoInt* a = *lista1;
    NoInt* b = *lista2;

    while (a && b) {
        if (a->valor <= b->valor) {
            cauda->proximo = a;
            a = a->proximo;
        } else {
            cauda->proximo = b;
            b = b->proximo;
        }
        cauda = cauda->proximo;
    }

    cauda->proximo = a ? a : b;
    *lista1 = NULL;
    *lista2 = NULL;
    return dummy.proximo;
}

static bool preencherListaOrdenada(NoInt** lista, int quantidade, const char* nomeLista) {
    if (quantidade <= 0) {
        return true;
    }
    printMensagemColoridaFormatted(CYAN, "\nPreencha a lista %s (idealmente ordenada):", nomeLista);
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

void executarQuestaoListas8(void) {
    executarQuestaoListas8Predefinido();
}

void executarQuestaoListas8Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: fusao de duas listas ordenadas sem alocar novos nos.");
    printf("\n");

    NoInt* lista1 = NULL;
    NoInt* lista2 = NULL;

    int valoresL1[] = {1, 4, 7, 9};
    int valoresL2[] = {2, 3, 8, 10, 12};
    for (size_t i = 0; i < sizeof(valoresL1) / sizeof(valoresL1[0]); i++) {
        inserirFim(&lista1, valoresL1[i]);
    }
    for (size_t i = 0; i < sizeof(valoresL2) / sizeof(valoresL2[0]); i++) {
        inserirFim(&lista2, valoresL2[i]);
    }

    imprimirLista(lista1, "Lista L1 (ordenada)");
    imprimirLista(lista2, "Lista L2 (ordenada)");

    NoInt* listaFundida = fundirListasOrdenadas(&lista1, &lista2);

    printf("\n");
    printMensagemColoridaFormatted(GREEN, "Listas fundidas mantendo a ordenacao.");
    imprimirLista(listaFundida, "Lista resultante");
    imprimirLista(lista1, "Lista L1 apos fusao");
    imprimirLista(lista2, "Lista L2 apos fusao");

    liberarLista(&listaFundida);
    pausar();
}

void executarQuestaoListas8EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: leia duas listas ordenadas e realize a fusao sem copiar dados.");
    printf("\n");

    int qtdL1;
    printMensagemColoridaInline(YELLOW, "Quantidade de elementos da lista L1 (0 a 30): ");
    if (scanf("%d", &qtdL1) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (qtdL1 < 0 || qtdL1 > 30) {
        printMensagemColoridaFormatted(RED, "Quantidade fora do intervalo permitido.");
        pausar();
        return;
    }

    int qtdL2;
    printMensagemColoridaInline(YELLOW, "Quantidade de elementos da lista L2 (0 a 30): ");
    if (scanf("%d", &qtdL2) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (qtdL2 < 0 || qtdL2 > 30) {
        printMensagemColoridaFormatted(RED, "Quantidade fora do intervalo permitido.");
        pausar();
        return;
    }

    NoInt* lista1 = NULL;
    NoInt* lista2 = NULL;
    if (!preencherListaOrdenada(&lista1, qtdL1, "L1") || !preencherListaOrdenada(&lista2, qtdL2, "L2")) {
        liberarLista(&lista1);
        liberarLista(&lista2);
        pausar();
        return;
    }

    printf("\n");
    imprimirLista(lista1, "Lista L1");
    imprimirLista(lista2, "Lista L2");

    NoInt* listaFundida = fundirListasOrdenadas(&lista1, &lista2);

    printf("\n");
    printMensagemColoridaFormatted(GREEN, "Fusao concluida.");
    imprimirLista(listaFundida, "Lista resultante");
    imprimirLista(lista1, "Lista L1 apos fusao");
    imprimirLista(lista2, "Lista L2 apos fusao");

    liberarLista(&listaFundida);
    pausar();
}
