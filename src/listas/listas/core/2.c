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
    printMensagemColoridaFormatted(YELLOW, "=== Listas - Questao 02 ===");
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

static NoInt* removerRecursivoInterno(NoInt* atual, int valor, bool* removido) {
    if (!atual) {
        return NULL;
    }
    if (!*removido && atual->valor == valor) {
        NoInt* proximo = atual->proximo;
        free(atual);
        *removido = true;
        return proximo;
    }
    atual->proximo = removerRecursivoInterno(atual->proximo, valor, removido);
    return atual;
}

static bool removerValorRecursivo(NoInt** inicio, int valor) {
    bool removido = false;
    *inicio = removerRecursivoInterno(*inicio, valor, &removido);
    return removido;
}

static bool listasIguaisRecursivo(const NoInt* a, const NoInt* b) {
    if (a == NULL && b == NULL) {
        return true;
    }
    if (a == NULL || b == NULL) {
        return false;
    }
    if (a->valor != b->valor) {
        return false;
    }
    return listasIguaisRecursivo(a->proximo, b->proximo);
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

static void preencherListaComEntrada(NoInt** lista, int quantidade, const char* label) {
    printMensagemColoridaFormatted(CYAN, "\nPreenchendo %s com %d elemento(s):", label, quantidade);
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

void executarQuestaoListas2(void) {
    executarQuestaoListas2Predefinido();
}

void executarQuestaoListas2Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: remocao recursiva e comparacao de listas.");
    printf("\n");

    NoInt* listaPrincipal = NULL;
    NoInt* listaComparacaoA = NULL;
    NoInt* listaComparacaoB = NULL;

    int valoresPrincipais[] = {10, 20, 30, 40, 50};
    int valoresComparacaoA[] = {10, 20, 40, 50};
    int valoresComparacaoB[] = {10, 20, 35, 50};

    for (size_t i = 0; i < sizeof(valoresPrincipais) / sizeof(valoresPrincipais[0]); i++) {
        inserirFim(&listaPrincipal, valoresPrincipais[i]);
    }
    for (size_t i = 0; i < sizeof(valoresComparacaoA) / sizeof(valoresComparacaoA[0]); i++) {
        inserirFim(&listaComparacaoA, valoresComparacaoA[i]);
    }
    for (size_t i = 0; i < sizeof(valoresComparacaoB) / sizeof(valoresComparacaoB[0]); i++) {
        inserirFim(&listaComparacaoB, valoresComparacaoB[i]);
    }

    printMensagemColoridaFormatted(CYAN, "Lista original:");
    imprimirLista(listaPrincipal);

    bool removido = removerValorRecursivo(&listaPrincipal, 30);
    printf("\n");
    if (removido) {
        printMensagemColoridaFormatted(GREEN, "Elemento 30 removido com sucesso.");
    } else {
        printMensagemColoridaFormatted(RED, "Elemento 30 nao encontrado na lista.");
    }

    printMensagemColoridaFormatted(CYAN, "Lista apos remocao:");
    imprimirLista(listaPrincipal);

    printf("\n");
    printMensagemColoridaFormatted(CYAN, "Comparando lista com listaComparacaoA:");
    if (listasIguaisRecursivo(listaPrincipal, listaComparacaoA)) {
        printMensagemColoridaFormatted(GREEN, "As listas sao iguais.");
    } else {
        printMensagemColoridaFormatted(RED, "As listas sao diferentes.");
    }

    printf("\n");
    printMensagemColoridaFormatted(CYAN, "Comparando lista com listaComparacaoB:");
    if (listasIguaisRecursivo(listaPrincipal, listaComparacaoB)) {
        printMensagemColoridaFormatted(GREEN, "As listas sao iguais.");
    } else {
        printMensagemColoridaFormatted(RED, "As listas sao diferentes.");
    }

    liberarLista(&listaPrincipal);
    liberarLista(&listaComparacaoA);
    liberarLista(&listaComparacaoB);
    pausar();
}

void executarQuestaoListas2EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: remocao recursiva em L1 e comparacao com L2.");
    printf("\n");

    NoInt* listaPrincipal = NULL;
    NoInt* listaComparacao = NULL;

    int quantidadeL1;
    printMensagemColoridaInline(YELLOW, "Informe a quantidade de elementos da lista principal (0 a 25): ");
    if (scanf("%d", &quantidadeL1) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (quantidadeL1 < 0 || quantidadeL1 > 25) {
        printMensagemColoridaFormatted(RED, "Quantidade fora do intervalo permitido.");
        pausar();
        return;
    }

    preencherListaComEntrada(&listaPrincipal, quantidadeL1, "a lista principal");
    if (listaPrincipal == NULL && quantidadeL1 > 0) {
        pausar();
        return;
    }

    printf("\n");
    printMensagemColoridaFormatted(CYAN, "Lista principal cadastrada:");
    imprimirLista(listaPrincipal);

    int valorParaRemover;
    printMensagemColoridaInline(YELLOW, "\nInforme o valor que deseja remover: ");
    if (scanf("%d", &valorParaRemover) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        liberarLista(&listaPrincipal);
        pausar();
        return;
    }
    limparBufferTeclado();

    bool removido = removerValorRecursivo(&listaPrincipal, valorParaRemover);
    printf("\n");
    if (removido) {
        printMensagemColoridaFormatted(GREEN, "Elemento %d removido.", valorParaRemover);
    } else {
        printMensagemColoridaFormatted(RED, "Valor %d nao encontrado na lista.", valorParaRemover);
    }

    printMensagemColoridaFormatted(CYAN, "Lista principal apos tentativa de remocao:");
    imprimirLista(listaPrincipal);

    int quantidadeL2;
    printMensagemColoridaInline(YELLOW, "\nInforme a quantidade de elementos da segunda lista (0 a 25): ");
    if (scanf("%d", &quantidadeL2) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        liberarLista(&listaPrincipal);
        pausar();
        return;
    }
    limparBufferTeclado();

    if (quantidadeL2 < 0 || quantidadeL2 > 25) {
        printMensagemColoridaFormatted(RED, "Quantidade fora do intervalo permitido.");
        liberarLista(&listaPrincipal);
        pausar();
        return;
    }

    preencherListaComEntrada(&listaComparacao, quantidadeL2, "a segunda lista");
    if (listaComparacao == NULL && quantidadeL2 > 0) {
        liberarLista(&listaPrincipal);
        pausar();
        return;
    }

    printf("\n");
    printMensagemColoridaFormatted(CYAN, "Segunda lista cadastrada:");
    imprimirLista(listaComparacao);

    printf("\n");
    if (listasIguaisRecursivo(listaPrincipal, listaComparacao)) {
        printMensagemColoridaFormatted(GREEN, "As listas sao iguais.");
    } else {
        printMensagemColoridaFormatted(RED, "As listas sao diferentes.");
    }

    liberarLista(&listaPrincipal);
    liberarLista(&listaComparacao);
    pausar();
}
