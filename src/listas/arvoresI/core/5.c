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
    printMensagemColoridaFormatted(YELLOW, "=== Arvores I - Questao 05 ===");
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

static NoArvore* removerArvoreAtual(NoArvore* atual) {
    if (!atual) {
        return NULL;
    }

    if (atual->esquerda == NULL) {
        NoArvore* direita = atual->direita;
        free(atual);
        return direita;
    }

    if (atual->direita == NULL) {
        NoArvore* esquerda = atual->esquerda;
        free(atual);
        return esquerda;
    }

    NoArvore* sucessorPai = atual;
    NoArvore* sucessor = atual->direita;
    while (sucessor->esquerda) {
        sucessorPai = sucessor;
        sucessor = sucessor->esquerda;
    }

    atual->valor = sucessor->valor;

    if (sucessorPai == atual) {
        sucessorPai->direita = sucessor->direita;
    } else {
        sucessorPai->esquerda = sucessor->direita;
    }

    free(sucessor);
    return atual;
}

static void liberarArvore(NoArvore* raiz) {
    if (!raiz) {
        return;
    }
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

static NoArvore* buscarNo(NoArvore* raiz, int valor) {
    if (!raiz) {
        return NULL;
    }
    if (valor == raiz->valor) {
        return raiz;
    }
    if (valor < raiz->valor) {
        return buscarNo(raiz->esquerda, valor);
    }
    return buscarNo(raiz->direita, valor);
}

static void imprimirArvore(const NoArvore* raiz, int nivel) {
    if (!raiz) {
        return;
    }
    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }
    printf("- %d\n", raiz->valor);
    imprimirArvore(raiz->esquerda, nivel + 1);
    imprimirArvore(raiz->direita, nivel + 1);
}

static void demonstracaoPredefinida(void) {
    int valores[] = {45, 30, 60, 20, 35, 50, 70};
    size_t quantidade = sizeof(valores) / sizeof(valores[0]);
    NoArvore* raiz = NULL;

    for (size_t i = 0; i < quantidade; i++) {
        raiz = inserirBST(raiz, valores[i]);
    }

    printMensagemColoridaFormatted(CYAN, "Arvore original:");
    imprimirArvore(raiz, 0);
    printf("\n");

    int alvo = 60;
    NoArvore* ponteiro = buscarNo(raiz, alvo);
    if (ponteiro) {
        printMensagemColoridaFormatted(CYAN, "Removendo o no apontado (valor %d) utilizando Remove_ArvoreAtual.", alvo);
        NoArvore* novoSub = removerArvoreAtual(ponteiro);

        if (novoSub != ponteiro) {
            if (raiz == ponteiro) {
                raiz = novoSub;
            } else {
                NoArvore* pai = raiz;
                while (pai && pai->esquerda != ponteiro && pai->direita != ponteiro) {
                    if (alvo < pai->valor) {
                        pai = pai->esquerda;
                    } else {
                        pai = pai->direita;
                    }
                }
                if (pai) {
                    if (pai->esquerda == ponteiro) {
                        pai->esquerda = novoSub;
                    } else if (pai->direita == ponteiro) {
                        pai->direita = novoSub;
                    }
                }
            }
        }
    }

    printMensagemColoridaFormatted(CYAN, "Arvore apos remocao do no indicado:");
    imprimirArvore(raiz, 0);

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
    printMensagemColoridaInline(YELLOW, "Quantos valores deseja inserir (1 a 25): ");
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
    printMensagemColoridaFormatted(CYAN, "Informe os valores para montar a arvore (BST):");
    if (!preencherArvoreManual(&raiz, quantidade)) {
        liberarArvore(raiz);
        pausar();
        return;
    }

    printf("\n");
    printMensagemColoridaFormatted(CYAN, "Estrutura atual:");
    imprimirArvore(raiz, 0);

    int alvo;
    printMensagemColoridaInline(YELLOW, "\nInforme o valor do no que deseja remover: ");
    if (scanf("%d", &alvo) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        liberarArvore(raiz);
        pausar();
        return;
    }
    limparBufferTeclado();

    NoArvore* ponteiro = buscarNo(raiz, alvo);
    if (!ponteiro) {
        printMensagemColoridaFormatted(RED, "Valor %d nao encontrado. Nenhum no foi removido.", alvo);
    } else {
        NoArvore* novoSub = removerArvoreAtual(ponteiro);
        if (novoSub != ponteiro) {
            if (raiz == ponteiro) {
                raiz = novoSub;
            } else {
                NoArvore* pai = raiz;
                while (pai && pai->esquerda != ponteiro && pai->direita != ponteiro) {
                    if (alvo < pai->valor) {
                        pai = pai->esquerda;
                    } else {
                        pai = pai->direita;
                    }
                }
                if (pai) {
                    if (pai->esquerda == ponteiro) {
                        pai->esquerda = novoSub;
                    } else if (pai->direita == ponteiro) {
                        pai->direita = novoSub;
                    }
                }
            }
        }
        printMensagemColoridaFormatted(GREEN, "No removido com sucesso.");
    }

    printf("\n");
    printMensagemColoridaFormatted(CYAN, "Estrutura apos a remocao:");
    imprimirArvore(raiz, 0);

    liberarArvore(raiz);
    pausar();
}

void executarQuestaoArvoresI5(void) {
    executarQuestaoArvoresI5Predefinido();
}

void executarQuestaoArvoresI5Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: remove o no apontado usando Remove_ArvoreAtual.");
    printf("\n");
    demonstracaoPredefinida();
    pausar();
}

void executarQuestaoArvoresI5EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: selecione um no especifico para remover.");
    printf("\n");
    fluxoManual();
}
