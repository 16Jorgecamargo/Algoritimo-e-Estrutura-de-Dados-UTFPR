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
    printMensagemColoridaFormatted(YELLOW, "=== Arvores I - Questao 02 ===");
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

static void liberarArvore(NoArvore* raiz) {
    if (!raiz) {
        return;
    }
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

static void preOrdem(const NoArvore* raiz) {
    if (!raiz) {
        return;
    }
    printf("%d ", raiz->valor);
    preOrdem(raiz->esquerda);
    preOrdem(raiz->direita);
}

static void emOrdem(const NoArvore* raiz) {
    if (!raiz) {
        return;
    }
    emOrdem(raiz->esquerda);
    printf("%d ", raiz->valor);
    emOrdem(raiz->direita);
}

static void posOrdem(const NoArvore* raiz) {
    if (!raiz) {
        return;
    }
    posOrdem(raiz->esquerda);
    posOrdem(raiz->direita);
    printf("%d ", raiz->valor);
}

static void imprimirVarreduras(const NoArvore* raiz) {
    printMensagemColoridaFormatted(CYAN, "PRE-ORDEM (visita raiz antes dos filhos):");
    preOrdem(raiz);
    printf("\n\n");

    printMensagemColoridaFormatted(CYAN, "EM-ORDEM (visita esquerda, raiz, direita):");
    emOrdem(raiz);
    printf("\n\n");

    printMensagemColoridaFormatted(CYAN, "POS-ORDEM (visita os filhos e entao a raiz):");
    posOrdem(raiz);
    printf("\n\n");
}

static void demonstracaoPredefinida(void) {
    int valores[] = {50, 30, 20, 40, 70, 60, 80};
    size_t quantidade = sizeof(valores) / sizeof(valores[0]);
    NoArvore* raiz = NULL;

    for (size_t i = 0; i < quantidade; i++) {
        raiz = inserirBST(raiz, valores[i]);
    }

    printMensagemColoridaFormatted(CYAN, "Arvore base (mesmo conjunto usado nos testes da funcao original PREOrdem_Arvore):");
    imprimirVarreduras(raiz);

    liberarArvore(raiz);
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

static void fluxoManual(void) {
    int quantidade;
    printMensagemColoridaInline(YELLOW, "Quantos valores deseja inserir na arvore (1 a 25): ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (quantidade < 1 || quantidade > 25) {
        printMensagemColoridaFormatted(RED, "Quantidade fora do intervalo permitido.");
        pausar();
        return;
    }

    NoArvore* raiz = NULL;
    printMensagemColoridaFormatted(CYAN, "Informe os valores (a arvore sera tratada como BST):");
    if (!preencherArvoreManual(&raiz, quantidade)) {
        liberarArvore(raiz);
        pausar();
        return;
    }

    printf("\n");
    imprimirVarreduras(raiz);

    printMensagemColoridaFormatted(GREEN, "Lembre-se: PRE visita raiz primeiro, EM ordena os valores e POS visita a raiz por ultimo.");

    liberarArvore(raiz);
    pausar();
}

void executarQuestaoArvoresI2(void) {
    executarQuestaoArvoresI2Predefinido();
}

void executarQuestaoArvoresI2Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: varreduras PRE, EM e POS ordem a partir do modelo fornecido pelo projeto.");
    printf("\n");
    demonstracaoPredefinida();
    pausar();
}

void executarQuestaoArvoresI2EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: cadastre os valores e visualize as tres varreduras.");
    printf("\n");
    fluxoManual();
}
