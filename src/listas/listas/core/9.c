#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

typedef struct TipoCelula {
    int valor;
    struct TipoCelula* proximo;
} TipoCelula;

typedef struct {
    TipoCelula* inicio;
} TipoLista;

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Listas - Questao 09 ===");
    printf("\n");
}

static TipoCelula* criarCelula(int valor) {
    TipoCelula* nova = (TipoCelula*)malloc(sizeof(TipoCelula));
    if (!nova) {
        return NULL;
    }
    nova->valor = valor;
    nova->proximo = NULL;
    return nova;
}

static bool inserirFim(TipoLista* lista, int valor) {
    TipoCelula* nova = criarCelula(valor);
    if (!nova) {
        return false;
    }
    if (!lista->inicio) {
        lista->inicio = nova;
        return true;
    }
    TipoCelula* atual = lista->inicio;
    while (atual->proximo) {
        atual = atual->proximo;
    }
    atual->proximo = nova;
    return true;
}

static void liberarLista(TipoLista* lista) {
    TipoCelula* atual = lista->inicio;
    while (atual) {
        TipoCelula* temp = atual->proximo;
        free(atual);
        atual = temp;
    }
    lista->inicio = NULL;
}

static void imprimirLista(const TipoLista* lista) {
    printf("[ ");
    for (TipoCelula* atual = lista->inicio; atual; atual = atual->proximo) {
        printf("%d", atual->valor);
        if (atual->proximo) {
            printf(" -> ");
        }
    }
    printf(" ]\n");
}

static bool trocarComProxima(TipoLista* lista, TipoCelula* p) {
    if (!lista || !p || !p->proximo) {
        return false;
    }

    TipoCelula* anterior = NULL;
    TipoCelula* atual = lista->inicio;

    while (atual && atual != p) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (!atual) {
        return false; // ponteiro nao pertence a lista
    }

    TipoCelula* proxima = atual->proximo;
    atual->proximo = proxima->proximo;
    proxima->proximo = atual;

    if (anterior) {
        anterior->proximo = proxima;
    } else {
        lista->inicio = proxima;
    }
    return true;
}

static TipoCelula* obterCelulaPorIndice(TipoLista* lista, int indice) {
    if (indice < 1) {
        return NULL;
    }
    int contador = 1;
    for (TipoCelula* atual = lista->inicio; atual; atual = atual->proximo, contador++) {
        if (contador == indice) {
            return atual;
        }
    }
    return NULL;
}

static int contarElementos(const TipoLista* lista) {
    int contador = 0;
    for (TipoCelula* atual = lista->inicio; atual; atual = atual->proximo) {
        contador++;
    }
    return contador;
}

void executarQuestaoListas9(void) {
    executarQuestaoListas9Predefinido();
}

void executarQuestaoListas9Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: troca fisica de uma celula pelo seu sucessor.");
    printf("\n");

    TipoLista lista = {NULL};
    int valores[] = {10, 20, 30, 40, 50};
    for (size_t i = 0; i < sizeof(valores) / sizeof(valores[0]); i++) {
        inserirFim(&lista, valores[i]);
    }

    printMensagemColoridaFormatted(CYAN, "Lista original:");
    imprimirLista(&lista);

    TipoCelula* alvo = obterCelulaPorIndice(&lista, 2); // celula com valor 20
    if (trocarComProxima(&lista, alvo)) {
        printMensagemColoridaFormatted(GREEN, "\nA celula da posicao 2 foi trocada com sua sucessora.");
    } else {
        printMensagemColoridaFormatted(RED, "\nNao foi possivel realizar a troca.");
    }

    printMensagemColoridaFormatted(CYAN, "Lista apos a troca:");
    imprimirLista(&lista);

    liberarLista(&lista);
    pausar();
}

void executarQuestaoListas9EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: escolha a celula a ser trocada com sua seguinte.");
    printf("\n");

    int quantidade;
    printMensagemColoridaInline(YELLOW, "Informe a quantidade de elementos da lista (2 a 30): ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (quantidade < 2 || quantidade > 30) {
        printMensagemColoridaFormatted(RED, "A lista deve ter pelo menos dois elementos e no maximo 30.");
        pausar();
        return;
    }

    TipoLista lista = {NULL};
    printMensagemColoridaFormatted(CYAN, "\nPreencha a lista:");
    for (int i = 0; i < quantidade; i++) {
        printMensagemColoridaInline(YELLOW, "Valor ");
        printf("%d: ", i + 1);
        int valor;
        if (scanf("%d", &valor) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "Entrada invalida. Abortando fluxo.");
            liberarLista(&lista);
            pausar();
            return;
        }
        limparBufferTeclado();
        if (!inserirFim(&lista, valor)) {
            printMensagemColoridaFormatted(RED, "Falha ao alocar memoria. Abortando fluxo.");
            liberarLista(&lista);
            pausar();
            return;
        }
    }

    printf("\n");
    printMensagemColoridaFormatted(CYAN, "Lista atual:");
    imprimirLista(&lista);

    int posicao;
    int tamanho = contarElementos(&lista);
    printMensagemColoridaInline(YELLOW, "\nInforme a posicao da celula que deseja trocar ");
    printf("(1 a %d): ", tamanho - 1);
    if (scanf("%d", &posicao) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        liberarLista(&lista);
        pausar();
        return;
    }
    limparBufferTeclado();

    if (posicao < 1 || posicao >= tamanho) {
        printMensagemColoridaFormatted(RED, "Posicao invalida para a operacao.");
        liberarLista(&lista);
        pausar();
        return;
    }

    TipoCelula* alvo = obterCelulaPorIndice(&lista, posicao);
    if (trocarComProxima(&lista, alvo)) {
        printMensagemColoridaFormatted(GREEN, "\nTroca realizada entre as posicoes %d e %d.", posicao, posicao + 1);
    } else {
        printMensagemColoridaFormatted(RED, "\nNao foi possivel realizar a troca.");
    }

    printMensagemColoridaFormatted(CYAN, "Lista final:");
    imprimirLista(&lista);

    liberarLista(&lista);
    pausar();
}
