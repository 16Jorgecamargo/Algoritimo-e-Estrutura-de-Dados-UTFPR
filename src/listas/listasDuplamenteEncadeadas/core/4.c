#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

typedef struct NoCircular {
    int valor;
    struct NoCircular* ant;
    struct NoCircular* prox;
} NoCircular;

typedef struct {
    NoCircular* cabeca;
    int tamanho;
} ListaCircularDupla;

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Listas Duplamente Encadeadas - Questao 04 ===");
    printf("\n");
}

static void inicializarLista(ListaCircularDupla* lista) {
    lista->cabeca = NULL;
    lista->tamanho = 0;
}

static NoCircular* criarNo(int valor) {
    NoCircular* novo = (NoCircular*)malloc(sizeof(NoCircular));
    if (!novo) {
        return NULL;
    }
    novo->valor = valor;
    novo->ant = novo;
    novo->prox = novo;
    return novo;
}

static bool inserirInicio(ListaCircularDupla* lista, int valor) {
    NoCircular* novo = criarNo(valor);
    if (!novo) {
        return false;
    }

    if (lista->cabeca == NULL) {
        lista->cabeca = novo;
    } else {
        NoCircular* ultimo = lista->cabeca->ant;
        novo->prox = lista->cabeca;
        novo->ant = ultimo;
        ultimo->prox = novo;
        lista->cabeca->ant = novo;
        lista->cabeca = novo;
    }
    lista->tamanho++;
    return true;
}

static bool inserirFim(ListaCircularDupla* lista, int valor) {
    if (lista->cabeca == NULL) {
        return inserirInicio(lista, valor);
    }
    NoCircular* novo = criarNo(valor);
    if (!novo) {
        return false;
    }

    NoCircular* ultimo = lista->cabeca->ant;
    novo->prox = lista->cabeca;
    novo->ant = ultimo;
    ultimo->prox = novo;
    lista->cabeca->ant = novo;
    lista->tamanho++;
    return true;
}

static bool removerInicio(ListaCircularDupla* lista, int* removido) {
    if (lista->cabeca == NULL) {
        return false;
    }

    NoCircular* primeiro = lista->cabeca;
    if (removido) {
        *removido = primeiro->valor;
    }

    if (lista->tamanho == 1) {
        lista->cabeca = NULL;
    } else {
        NoCircular* ultimo = primeiro->ant;
        lista->cabeca = primeiro->prox;
        lista->cabeca->ant = ultimo;
        ultimo->prox = lista->cabeca;
    }

    free(primeiro);
    lista->tamanho--;
    return true;
}

static bool removerFim(ListaCircularDupla* lista, int* removido) {
    if (lista->cabeca == NULL) {
        return false;
    }

    NoCircular* ultimo = lista->cabeca->ant;
    if (removido) {
        *removido = ultimo->valor;
    }

    if (lista->tamanho == 1) {
        free(ultimo);
        lista->cabeca = NULL;
        lista->tamanho = 0;
        return true;
    }

    NoCircular* penultimo = ultimo->ant;
    penultimo->prox = lista->cabeca;
    lista->cabeca->ant = penultimo;
    free(ultimo);
    lista->tamanho--;
    return true;
}

static void percorrerCircular(const ListaCircularDupla* lista) {
    if (lista->cabeca == NULL) {
        printMensagemColoridaFormatted(CYAN, "Lista vazia (percorrimento circular).");
        return;
    }

    printMensagemColoridaInline(CYAN, "Percurso circular: ");
    printf("[ ");
    NoCircular* atual = lista->cabeca;
    for (int i = 0; i < lista->tamanho; i++) {
        printf("%d", atual->valor);
        if (i + 1 < lista->tamanho) {
            printf(" <-> ");
        }
        atual = atual->prox;
    }
    printf(" ]\n");
}

static void liberarLista(ListaCircularDupla* lista) {
    if (lista->cabeca == NULL) {
        return;
    }

    NoCircular* atual = lista->cabeca;
    for (int i = 0; i < lista->tamanho; i++) {
        NoCircular* proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    lista->cabeca = NULL;
    lista->tamanho = 0;
}

void executarQuestaoListasDuplamenteEncadeadas4(void) {
    executarQuestaoListasDuplamenteEncadeadas4Predefinido();
}

void executarQuestaoListasDuplamenteEncadeadas4Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: insercoes e remocoes em lista duplamente encadeada circular.");
    printf("\n");

    ListaCircularDupla lista;
    inicializarLista(&lista);

    inserirFim(&lista, 10);
    inserirFim(&lista, 20);
    inserirFim(&lista, 30);
    printMensagemColoridaFormatted(CYAN, "Estado inicial apos insercoes no fim:");
    percorrerCircular(&lista);

    inserirInicio(&lista, 5);
    inserirFim(&lista, 40);
    printMensagemColoridaFormatted(CYAN, "\nLista apos inserir no inicio e no fim:");
    percorrerCircular(&lista);

    int removido;
    if (removerInicio(&lista, &removido)) {
        printMensagemColoridaFormatted(GREEN, "\nRemocao no inicio removeu: %d", removido);
    }
    if (removerFim(&lista, &removido)) {
        printMensagemColoridaFormatted(GREEN, "Remocao no fim removeu: %d", removido);
    }

    printMensagemColoridaFormatted(CYAN, "\nPercorrendo a lista circular apos as remocoes:");
    percorrerCircular(&lista);

    liberarLista(&lista);
    pausar();
}

void executarQuestaoListasDuplamenteEncadeadas4EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: teste insercoes/remocoes em uma lista duplamente encadeada circular.");
    printf("\n");

    int quantidade;
    printMensagemColoridaInline(YELLOW, "Quantidade inicial de elementos (0 a 20): ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (quantidade < 0 || quantidade > 20) {
        printMensagemColoridaFormatted(RED, "Quantidade fora do intervalo permitido.");
        pausar();
        return;
    }

    ListaCircularDupla lista;
    inicializarLista(&lista);

    for (int i = 0; i < quantidade; i++) {
        int valor;
        printMensagemColoridaInline(YELLOW, "Valor ");
        printf("%d: ", i + 1);
        if (scanf("%d", &valor) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "Entrada invalida. Abortando preenchimento.");
            liberarLista(&lista);
            pausar();
            return;
        }
        limparBufferTeclado();

        if (!inserirFim(&lista, valor)) {
            printMensagemColoridaFormatted(RED, "Falha ao inserir elemento no fim.");
            liberarLista(&lista);
            pausar();
            return;
        }
    }

    printf("\n");
    percorrerCircular(&lista);

    int valor;
    printMensagemColoridaInline(YELLOW, "\nInforme um valor para inserir no inicio: ");
    if (scanf("%d", &valor) == 1) {
        if (inserirInicio(&lista, valor)) {
            printMensagemColoridaFormatted(GREEN, "Valor inserido no inicio mantendo a circularidade.");
        } else {
            printMensagemColoridaFormatted(RED, "Falha ao inserir no inicio.");
        }
    } else {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida para insercao no inicio.");
    }
    limparBufferTeclado();

    printMensagemColoridaInline(YELLOW, "Informe um valor para inserir no fim: ");
    if (scanf("%d", &valor) == 1) {
        if (inserirFim(&lista, valor)) {
            printMensagemColoridaFormatted(GREEN, "Valor inserido no fim mantendo a circularidade.");
        } else {
            printMensagemColoridaFormatted(RED, "Falha ao inserir no fim.");
        }
    } else {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida para insercao no fim.");
    }
    limparBufferTeclado();

    printf("\n");
    percorrerCircular(&lista);

    int opcao;
    printMensagemColoridaInline(YELLOW, "\nDeseja remover um elemento do inicio? (1 = sim / 0 = nao): ");
    if (scanf("%d", &opcao) == 1 && opcao == 1) {
        if (removerInicio(&lista, &valor)) {
            printMensagemColoridaFormatted(GREEN, "Removido do inicio: %d", valor);
        } else {
            printMensagemColoridaFormatted(RED, "Lista vazia - remocao nao realizada.");
        }
    }
    limparBufferTeclado();

    printMensagemColoridaInline(YELLOW, "Deseja remover um elemento do fim? (1 = sim / 0 = nao): ");
    if (scanf("%d", &opcao) == 1 && opcao == 1) {
        if (removerFim(&lista, &valor)) {
            printMensagemColoridaFormatted(GREEN, "Removido do fim: %d", valor);
        } else {
            printMensagemColoridaFormatted(RED, "Lista vazia - remocao nao realizada.");
        }
    }
    limparBufferTeclado();

    printf("\n");
    printMensagemColoridaFormatted(CYAN, "Percurso final do comportamento circular:");
    percorrerCircular(&lista);

    liberarLista(&lista);
    pausar();
}
