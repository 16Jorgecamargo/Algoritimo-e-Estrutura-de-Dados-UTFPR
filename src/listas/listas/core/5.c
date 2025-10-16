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
    printMensagemColoridaFormatted(YELLOW, "=== Listas - Questao 05 ===");
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

static void liberarLista(NoInt** inicio) {
    NoInt* atual = *inicio;
    while (atual) {
        NoInt* temp = atual->proximo;
        free(atual);
        atual = temp;
    }
    *inicio = NULL;
}

static int removerOcorrencias(NoInt** inicio, int valor) {
    int removidos = 0;
    while (*inicio && (*inicio)->valor == valor) {
        NoInt* temp = *inicio;
        *inicio = temp->proximo;
        free(temp);
        removidos++;
    }
    NoInt* atual = *inicio;
    while (atual && atual->proximo) {
        if (atual->proximo->valor == valor) {
            NoInt* temp = atual->proximo;
            atual->proximo = temp->proximo;
            free(temp);
            removidos++;
        } else {
            atual = atual->proximo;
        }
    }
    return removidos;
}

static void preencherLista(NoInt** lista, int quantidade) {
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

void executarQuestaoListas5(void) {
    executarQuestaoListas5Predefinido();
}

void executarQuestaoListas5Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: remover todas as ocorrencias de um valor nao negativo.");
    printf("\n");

    NoInt* lista = NULL;
    int valores[] = {7, 3, 7, 7, 10, 7, 15};
    for (size_t i = 0; i < sizeof(valores) / sizeof(valores[0]); i++) {
        inserirFim(&lista, valores[i]);
    }

    printMensagemColoridaFormatted(CYAN, "Lista original:");
    imprimirLista(lista);

    int alvo = 7;
    int removidos = removerOcorrencias(&lista, alvo);
    printf("\n");
    printMensagemColoridaFormatted(GREEN, "%d ocorrencia(s) do valor %d removida(s).", removidos, alvo);

    printMensagemColoridaFormatted(CYAN, "Lista apos as remocoes:");
    imprimirLista(lista);

    liberarLista(&lista);
    pausar();
}

void executarQuestaoListas5EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: remocao de todas as ocorrencias de um valor nao negativo.");
    printf("\n");

    int quantidade;
    printMensagemColoridaInline(YELLOW, "Informe a quantidade de elementos da lista (0 a 30): ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (quantidade < 0 || quantidade > 30) {
        printMensagemColoridaFormatted(RED, "Quantidade fora do intervalo permitido.");
        pausar();
        return;
    }

    NoInt* lista = NULL;
    if (quantidade > 0) {
        preencherLista(&lista, quantidade);
        if (lista == NULL) {
            pausar();
            return;
        }
    }

    printf("\n");
    printMensagemColoridaFormatted(CYAN, "Lista atual:");
    imprimirLista(lista);

    int alvo;
    printMensagemColoridaInline(YELLOW, "\nInforme o valor nao negativo que deseja remover: ");
    if (scanf("%d", &alvo) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        liberarLista(&lista);
        pausar();
        return;
    }
    limparBufferTeclado();

    if (alvo < 0) {
        printMensagemColoridaFormatted(RED, "O valor deve ser nao negativo.");
        liberarLista(&lista);
        pausar();
        return;
    }

    int removidos = removerOcorrencias(&lista, alvo);
    printf("\n");
    if (removidos > 0) {
        printMensagemColoridaFormatted(GREEN, "%d ocorrencia(s) do valor %d foram removidas.", removidos, alvo);
    } else {
        printMensagemColoridaFormatted(RED, "Nenhum no com valor %d foi encontrado.", alvo);
    }

    printMensagemColoridaFormatted(CYAN, "Lista apos processamento:");
    imprimirLista(lista);

    liberarLista(&lista);
    pausar();
}
