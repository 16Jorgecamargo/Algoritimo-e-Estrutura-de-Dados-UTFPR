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
    printMensagemColoridaFormatted(YELLOW, "=== Arvores I - Questao 01 ===");
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

static bool contemValor(const NoArvore* raiz, int valor) {
    if (!raiz) {
        return false;
    }
    if (valor == raiz->valor) {
        return true;
    }
    if (valor < raiz->valor) {
        return contemValor(raiz->esquerda, valor);
    }
    return contemValor(raiz->direita, valor);
}

static NoArvore* inserirBST(NoArvore* raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }
    if (valor < raiz->valor) {
        raiz->esquerda = inserirBST(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserirBST(raiz->direita, valor);
    }
    return raiz;
}

static NoArvore* encontrarMinimo(NoArvore* raiz) {
    NoArvore* atual = raiz;
    while (atual && atual->esquerda) {
        atual = atual->esquerda;
    }
    return atual;
}

static NoArvore* removerBST(NoArvore* raiz, int valor) {
    if (raiz == NULL) {
        return NULL;
    }

    if (valor < raiz->valor) {
        raiz->esquerda = removerBST(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = removerBST(raiz->direita, valor);
    } else {
        if (raiz->esquerda == NULL) {
            NoArvore* direita = raiz->direita;
            free(raiz);
            return direita;
        }
        if (raiz->direita == NULL) {
            NoArvore* esquerda = raiz->esquerda;
            free(raiz);
            return esquerda;
        }

        NoArvore* sucessor = encontrarMinimo(raiz->direita);
        raiz->valor = sucessor->valor;
        raiz->direita = removerBST(raiz->direita, sucessor->valor);
    }
    return raiz;
}

static void imprimirArvoreEmNivel(const NoArvore* raiz, int nivel) {
    if (!raiz) {
        return;
    }
    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }
    printf("- %d\n", raiz->valor);
    imprimirArvoreEmNivel(raiz->esquerda, nivel + 1);
    imprimirArvoreEmNivel(raiz->direita, nivel + 1);
}

static void imprimirResumoOperacoes(void) {
    printMensagemColoridaFormatted(CYAN, "Resumo conceitual das operacoes:");
    printMensagemColoridaFormatted(GREEN, "1) Insercao (insere_Arvore):");
    printf("   - Percorre a arvore comparando chaves ate encontrar uma posicao nula.\n");
    printf("   - Elementos menores sao inseridos a esquerda, maiores a direita.\n\n");

    printMensagemColoridaFormatted(GREEN, "2) Remocao (remove_Arvore):");
    printf("   - Caso 1: Nó folha -> apenas libera o ponteiro.\n");
    printf("   - Caso 2: Nó com um filho -> substitui o nó pelo unico filho.\n");
    printf("   - Caso 3: Nó com dois filhos -> troca pelo sucessor em ordem (menor da subarvore direita) e remove o sucessor na subarvore.\n\n");
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

static void demonstrarInsercaoRemocaoPadrao(void) {
    NoArvore* raiz = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    size_t total = sizeof(valores) / sizeof(valores[0]);

    printMensagemColoridaFormatted(CYAN, "Inserindo os valores na ordem: 50, 30, 70, 20, 40, 60, 80");
    for (size_t i = 0; i < total; i++) {
        raiz = inserirBST(raiz, valores[i]);
    }

    printMensagemColoridaFormatted(CYAN, "Arvore resultante (raiz exibida first, filhos identados):");
    imprimirArvoreEmNivel(raiz, 0);
    printf("\n");

    printMensagemColoridaFormatted(CYAN, "Removendo o valor 20 (no folha):");
    raiz = removerBST(raiz, 20);
    imprimirArvoreEmNivel(raiz, 0);

    printf("\n");
    printMensagemColoridaFormatted(CYAN, "Removendo o valor 30 (no com um filho):");
    raiz = removerBST(raiz, 30);
    imprimirArvoreEmNivel(raiz, 0);

    printf("\n");
    printMensagemColoridaFormatted(CYAN, "Removendo o valor 50 (no com dois filhos):");
    raiz = removerBST(raiz, 50);
    imprimirArvoreEmNivel(raiz, 0);

    printf("\n");
    imprimirResumoOperacoes();

    liberarArvore(raiz);
}

static void fluxoManual(void) {
    NoArvore* raiz = NULL;

    int quantidade;
    printMensagemColoridaInline(YELLOW, "Informe quantos valores deseja inserir na arvore (1 a 20): ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (quantidade < 1 || quantidade > 20) {
        printMensagemColoridaFormatted(RED, "Quantidade fora do intervalo permitido.");
        pausar();
        return;
    }

    printMensagemColoridaFormatted(CYAN, "Informe os valores (serao inseridos como em uma BST):");
    if (!preencherArvoreManual(&raiz, quantidade)) {
        liberarArvore(raiz);
        pausar();
        return;
    }

    printf("\n");
    printMensagemColoridaFormatted(CYAN, "Arvore atual:");
    imprimirArvoreEmNivel(raiz, 0);

    printMensagemColoridaInline(YELLOW, "\nInforme um valor para remover: ");
    int alvo;
    if (scanf("%d", &alvo) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        liberarArvore(raiz);
        pausar();
        return;
    }
    limparBufferTeclado();

    printf("\n");
    printMensagemColoridaFormatted(CYAN, "Processando remocao de %d...", alvo);
    bool existia = contemValor(raiz, alvo);
    raiz = removerBST(raiz, alvo);

    if (existia) {
        printMensagemColoridaFormatted(GREEN, "Valor %d removido. Analise a estrutura atualizada abaixo.", alvo);
    } else {
        printMensagemColoridaFormatted(RED, "Valor %d nao encontrado. A arvore permanece inalterada.", alvo);
    }

    printMensagemColoridaFormatted(CYAN, "Arvore apos remocao:");
    imprimirArvoreEmNivel(raiz, 0);
    printf("\n");

    imprimirResumoOperacoes();

    liberarArvore(raiz);
    pausar();
}

void executarQuestaoArvoresI1(void) {
    executarQuestaoArvoresI1Predefinido();
}

void executarQuestaoArvoresI1Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: investigando insercao e remocao em arvore binaria de busca.");
    printf("\n");
    demonstrarInsercaoRemocaoPadrao();
    pausar();
}

void executarQuestaoArvoresI1EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: teste a insercao e remocao na arvore binaria de busca.");
    printf("\n");
    fluxoManual();
}
