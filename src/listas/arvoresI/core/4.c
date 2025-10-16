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
    printMensagemColoridaFormatted(YELLOW, "=== Arvores I - Questao 04 ===");
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

static bool consultarValor(const NoArvore* raiz, int valor) {
    if (!raiz) {
        return false;
    }
    if (valor == raiz->valor) {
        return true;
    }
    if (valor < raiz->valor) {
        return consultarValor(raiz->esquerda, valor);
    }
    return consultarValor(raiz->direita, valor);
}

static void liberarArvore(NoArvore* raiz) {
    if (!raiz) {
        return;
    }
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

static void demonstracaoPredefinida(void) {
    int valores[] = {35, 15, 50, 10, 25, 40, 60};
    size_t quantidade = sizeof(valores) / sizeof(valores[0]);
    NoArvore* raiz = NULL;

    for (size_t i = 0; i < quantidade; i++) {
        raiz = inserirBST(raiz, valores[i]);
    }

    int consultas[] = {25, 55, 35};
    size_t totalConsultas = sizeof(consultas) / sizeof(consultas[0]);

    printMensagemColoridaFormatted(CYAN, "Valores utilizados: 35, 15, 50, 10, 25, 40, 60");
    printf("\n");

    for (size_t i = 0; i < totalConsultas; i++) {
        int valor = consultas[i];
        bool encontrado = consultarValor(raiz, valor);
        if (encontrado) {
            printMensagemColoridaFormatted(GREEN, "Valor %d encontrado na arvore.", valor);
        } else {
            printMensagemColoridaFormatted(RED, "Valor %d nao encontrado na arvore.", valor);
        }
    }

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
    printMensagemColoridaInline(YELLOW, "Quantos valores deseja inserir na arvore (1 a 30): ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (quantidade < 1 || quantidade > 30) {
        printMensagemColoridaFormatted(RED, "Quantidade fora do intervalo permitido.");
        pausar();
        return;
    }

    NoArvore* raiz = NULL;
    printMensagemColoridaFormatted(CYAN, "Informe os valores para montar a arvore:");
    if (!preencherArvoreManual(&raiz, quantidade)) {
        liberarArvore(raiz);
        pausar();
        return;
    }

    int valorConsulta;
    printMensagemColoridaInline(YELLOW, "\nInforme um valor para consultar na arvore: ");
    if (scanf("%d", &valorConsulta) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        liberarArvore(raiz);
        pausar();
        return;
    }
    limparBufferTeclado();

    bool encontrado = consultarValor(raiz, valorConsulta);
    printf("\n");
    if (encontrado) {
        printMensagemColoridaFormatted(GREEN, "Valor %d encontrado na arvore.", valorConsulta);
    } else {
        printMensagemColoridaFormatted(RED, "Valor %d nao encontrado.", valorConsulta);
    }

    liberarArvore(raiz);
    pausar();
}

void executarQuestaoArvoresI4(void) {
    executarQuestaoArvoresI4Predefinido();
}

void executarQuestaoArvoresI4Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: consulta de valores em uma arvore binaria de busca.");
    printf("\n");
    demonstracaoPredefinida();
    pausar();
}

void executarQuestaoArvoresI4EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: monte a arvore e consulte se um valor existe.");
    printf("\n");
    fluxoManual();
}
