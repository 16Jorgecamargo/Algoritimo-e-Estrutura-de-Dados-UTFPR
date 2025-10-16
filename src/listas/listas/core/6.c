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
    printMensagemColoridaFormatted(YELLOW, "=== Listas - Questao 06 ===");
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

static void concatenarListas(NoInt** l1, NoInt** l2) {
    if (*l1 == NULL) {
        *l1 = *l2;
        *l2 = NULL;
        return;
    }
    NoInt* atual = *l1;
    while (atual->proximo) {
        atual = atual->proximo;
    }
    atual->proximo = *l2;
    *l2 = NULL;
}

static bool preencherLista(NoInt** lista, int quantidade, const char* titulo) {
    if (quantidade <= 0) {
        return true;
    }
    printMensagemColoridaFormatted(CYAN, "\nPreenchendo %s com %d elemento(s):", titulo, quantidade);
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

void executarQuestaoListas6(void) {
    executarQuestaoListas6Predefinido();
}

void executarQuestaoListas6Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: concatenar L1 e L2 sem criar novos nos.");
    printf("\n");

    NoInt* lista1 = NULL;
    NoInt* lista2 = NULL;

    int valoresL1[] = {1, 2, 3};
    int valoresL2[] = {4, 5, 6};

    for (size_t i = 0; i < sizeof(valoresL1) / sizeof(valoresL1[0]); i++) {
        inserirFim(&lista1, valoresL1[i]);
    }
    for (size_t i = 0; i < sizeof(valoresL2) / sizeof(valoresL2[0]); i++) {
        inserirFim(&lista2, valoresL2[i]);
    }

    imprimirLista(lista1, "Lista L1 antes");
    imprimirLista(lista2, "Lista L2 antes");

    concatenarListas(&lista1, &lista2);

    printf("\n");
    printMensagemColoridaFormatted(GREEN, "Concatenacao concluida. L2 agora aponta para NULL.");
    imprimirLista(lista1, "Lista L1 unida");
    imprimirLista(lista2, "Lista L2 (apos concatenacao)");

    liberarLista(&lista1);
    liberarLista(&lista2);
    pausar();
}

void executarQuestaoListas6EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: informe as duas listas para concatenacao (sem copiar nos).");
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

    if (!preencherLista(&lista1, qtdL1, "a lista L1") || !preencherLista(&lista2, qtdL2, "a lista L2")) {
        liberarLista(&lista1);
        liberarLista(&lista2);
        pausar();
        return;
    }

    printf("\n");
    imprimirLista(lista1, "Lista L1 informada");
    imprimirLista(lista2, "Lista L2 informada");

    concatenarListas(&lista1, &lista2);

    printf("\n");
    printMensagemColoridaFormatted(GREEN, "Listas concatenadas com sucesso.");
    imprimirLista(lista1, "Lista resultante (L1)");
    imprimirLista(lista2, "Lista L2 (aponta para NULL)");

    liberarLista(&lista1);
    liberarLista(&lista2);
    pausar();
}
