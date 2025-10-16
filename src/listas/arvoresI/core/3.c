#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

typedef struct NoArvore {
    int valor;
    struct NoArvore* esquerda;
    struct NoArvore* direita;
} NoArvore;

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Arvores I - Questao 03 ===");
    printf("\n");
}

static NoArvore* criarNo(int valor) {
    NoArvore* novo = (NoArvore*)malloc(sizeof(NoArvore));
    if (!novo) {
        return NULL;
    }
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

static NoArvore* inserirBST(NoArvore* raiz, int valor) {
    if (!raiz) {
        return criarNo(valor);
    }
    if (valor < raiz->valor) {
        raiz->esquerda = inserirBST(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserirBST(raiz->direita, valor);
    }
    return raiz;
}

static int contarNos(const NoArvore* raiz) {
    if (!raiz) {
        return 0;
    }
    int esquerda = contarNos(raiz->esquerda);
    int direita = contarNos(raiz->direita);
    return 1 + esquerda + direita;
}

static void liberarArvore(NoArvore* raiz) {
    if (!raiz) {
        return;
    }
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

static bool preencherArvoreManual(NoArvore** raiz, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printMensagemColoridaInline(YELLOW, "Valor ");
        printf("%d: ", i + 1);
        int valor;
        if (scanf("%d", &valor) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "Entrada invalida. Abortando preenchimento.");
            return false;
        }
        limparBufferTeclado();
        *raiz = inserirBST(*raiz, valor);
    }
    return true;
}

static void demonstracaoPredefinida(void) {
    int valores[] = {42, 21, 63, 10, 30, 55, 70, 5, 15};
    size_t quantidade = sizeof(valores) / sizeof(valores[0]);
    NoArvore* raiz = NULL;

    for (size_t i = 0; i < quantidade; i++) {
        raiz = inserirBST(raiz, valores[i]);
    }

    int total = contarNos(raiz);
    printMensagemColoridaFormatted(CYAN, "Valores inseridos: 42, 21, 63, 10, 30, 55, 70, 5, 15");
    printMensagemColoridaFormatted(GREEN, "Total de nos calculado recursivamente: %d", total);

    liberarArvore(raiz);
}

static void fluxoManual(void) {
    int quantidade;
    printMensagemColoridaInline(YELLOW, "Quantos valores deseja inserir na arvore (1 a 40): ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (quantidade < 1 || quantidade > 40) {
        printMensagemColoridaFormatted(RED, "Quantidade fora do intervalo permitido.");
        pausar();
        return;
    }

    NoArvore* raiz = NULL;
    printMensagemColoridaFormatted(CYAN, "Informe os valores para popular a arvore:");
    if (!preencherArvoreManual(&raiz, quantidade)) {
        liberarArvore(raiz);
        pausar();
        return;
    }

    int total = contarNos(raiz);
    printf("\n");
    printMensagemColoridaFormatted(GREEN, "A arvore possui %d no(s) ao todo.", total);

    liberarArvore(raiz);
    pausar();
}

void executarQuestaoArvoresI3(void) {
    executarQuestaoArvoresI3Predefinido();
}

void executarQuestaoArvoresI3Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: contagem recursiva de nos em uma arvore binaria.");
    printf("\n");
    demonstracaoPredefinida();
    pausar();
}

void executarQuestaoArvoresI3EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: cadastre os valores e descubra o total de nos da arvore.");
    printf("\n");
    fluxoManual();
}
