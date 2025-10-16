#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "fila_int.h"
#include "pilha_int.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

typedef struct NoFilaPtr {
    void *dado;
    struct NoFilaPtr *prox;
} NoFilaPtr;

typedef struct {
    NoFilaPtr *inicio;
    NoFilaPtr *fim;
    size_t tamanho;
} FilaPtr;

typedef struct NoPilhaPtr {
    void *dado;
    struct NoPilhaPtr *prox;
} NoPilhaPtr;

typedef struct {
    NoPilhaPtr *topo;
    size_t tamanho;
} PilhaPtr;

static void filaPtrInicializar(FilaPtr *fila) {
    if (!fila) {
        return;
    }
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

static int filaPtrEnfileirar(FilaPtr *fila, void *dado) {
    if (!fila) {
        return 0;
    }

    NoFilaPtr *novo = (NoFilaPtr *)malloc(sizeof(NoFilaPtr));
    if (!novo) {
        return 0;
    }

    novo->dado = dado;
    novo->prox = NULL;

    if (fila->fim) {
        fila->fim->prox = novo;
    } else {
        fila->inicio = novo;
    }

    fila->fim = novo;
    fila->tamanho++;
    return 1;
}

static void *filaPtrDesenfileirar(FilaPtr *fila) {
    if (!fila || !fila->inicio) {
        return NULL;
    }

    NoFilaPtr *removido = fila->inicio;
    void *dado = removido->dado;
    fila->inicio = removido->prox;
    if (!fila->inicio) {
        fila->fim = NULL;
    }

    fila->tamanho--;
    free(removido);
    return dado;
}

static void filaPtrLiberar(FilaPtr *fila, void (*liberarDado)(void *)) {
    if (!fila) {
        return;
    }

    NoFilaPtr *atual = fila->inicio;
    while (atual) {
        NoFilaPtr *prox = atual->prox;
        if (liberarDado) {
            liberarDado(atual->dado);
        }
        free(atual);
        atual = prox;
    }

    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

static void pilhaPtrInicializar(PilhaPtr *pilha) {
    if (!pilha) {
        return;
    }
    pilha->topo = NULL;
    pilha->tamanho = 0;
}

static int pilhaPtrEmpilhar(PilhaPtr *pilha, void *dado) {
    if (!pilha) {
        return 0;
    }

    NoPilhaPtr *novo = (NoPilhaPtr *)malloc(sizeof(NoPilhaPtr));
    if (!novo) {
        return 0;
    }

    novo->dado = dado;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho++;
    return 1;
}

static void *pilhaPtrDesempilhar(PilhaPtr *pilha) {
    if (!pilha || !pilha->topo) {
        return NULL;
    }

    NoPilhaPtr *removido = pilha->topo;
    void *dado = removido->dado;
    pilha->topo = removido->prox;
    pilha->tamanho--;
    free(removido);
    return dado;
}

static void pilhaPtrLiberar(PilhaPtr *pilha, void (*liberarDado)(void *)) {
    if (!pilha) {
        return;
    }

    NoPilhaPtr *atual = pilha->topo;
    while (atual) {
        NoPilhaPtr *prox = atual->prox;
        if (liberarDado) {
            liberarDado(atual->dado);
        }
        free(atual);
        atual = prox;
    }

    pilha->topo = NULL;
    pilha->tamanho = 0;
}

static void imprimirFilaInt(const FilaInt *fila) {
    printf("[ ");
    const NoFilaInt *no = fila ? fila->inicio : NULL;
    while (no) {
        printf("%d", no->valor);
        if (no->prox) {
            printf(", ");
        }
        no = no->prox;
    }
    printf(" ]");
}

static void imprimirPilhaInt(const PilhaInt *pilha) {
    printf("[ topo -> ");
    const NoPilhaInt *no = pilha ? pilha->topo : NULL;
    while (no) {
        printf("%d", no->valor);
        if (no->prox) {
            printf(" | ");
        }
        no = no->prox;
    }
    printf(" ]");
}

static FilaInt *criarFilaIntComValores(const int *valores, size_t quantidade) {
    FilaInt *fila = (FilaInt *)malloc(sizeof(FilaInt));
    if (!fila) {
        return NULL;
    }
    filaIntInicializar(fila);

    for (size_t i = 0; i < quantidade; i++) {
        if (!filaIntEnfileirar(fila, valores[i])) {
            filaIntLiberar(fila);
            free(fila);
            return NULL;
        }
    }
    return fila;
}

static PilhaInt *criarPilhaIntComValores(const int *valores, size_t quantidade) {
    PilhaInt *pilha = (PilhaInt *)malloc(sizeof(PilhaInt));
    if (!pilha) {
        return NULL;
    }
    pilhaIntInicializar(pilha);

    for (size_t i = 0; i < quantidade; i++) {
        if (!pilhaIntEmpilhar(pilha, valores[i])) {
            pilhaIntLiberar(pilha);
            free(pilha);
            return NULL;
        }
    }
    return pilha;
}

static void demonstrarFilaDeFilas(const int *const *linhas,
                                  const int *tamanhos,
                                  size_t quantidade) {
    FilaPtr filaDeFilas;
    filaPtrInicializar(&filaDeFilas);

    for (size_t i = 0; i < quantidade; i++) {
        FilaInt *fila = criarFilaIntComValores(linhas[i], (size_t)tamanhos[i]);
        if (!fila) {
            printMensagemColoridaFormatted(RED, "Falha ao criar fila %zu.\n", i + 1);
            continue;
        }
        filaPtrEnfileirar(&filaDeFilas, fila);
    }

    printf("Consumo FIFO da fila de filas:\n");
    size_t indice = 1;
    void *dado = NULL;
    while ((dado = filaPtrDesenfileirar(&filaDeFilas)) != NULL) {
        FilaInt *filaAtual = (FilaInt *)dado;
        printf("  Fila %zu -> ", indice);
        imprimirFilaInt(filaAtual);
        printf("\n");
        filaIntLiberar(filaAtual);
        free(filaAtual);
        indice++;
    }
    printf("\n");
    filaPtrLiberar(&filaDeFilas, NULL);
}

static void demonstrarFilaDePilhas(const int *const *linhas,
                                   const int *tamanhos,
                                   size_t quantidade) {
    FilaPtr filaDePilhas;
    filaPtrInicializar(&filaDePilhas);

    for (size_t i = 0; i < quantidade; i++) {
        PilhaInt *pilha = criarPilhaIntComValores(linhas[i], (size_t)tamanhos[i]);
        if (!pilha) {
            printMensagemColoridaFormatted(RED, "Falha ao criar pilha %zu.\n", i + 1);
            continue;
        }
        filaPtrEnfileirar(&filaDePilhas, pilha);
    }

    printf("Pilhas aguardando em ordem de chegada:\n");
    size_t indice = 1;
    void *dado = NULL;
    while ((dado = filaPtrDesenfileirar(&filaDePilhas)) != NULL) {
        PilhaInt *pilhaAtual = (PilhaInt *)dado;
        printf("  Pilha %zu -> ", indice);
        imprimirPilhaInt(pilhaAtual);
        printf("\n");
        pilhaIntLiberar(pilhaAtual);
        free(pilhaAtual);
        indice++;
    }
    printf("\n");
    filaPtrLiberar(&filaDePilhas, NULL);
}

static void demonstrarPilhaDeFilas(const int *const *linhas,
                                   const int *tamanhos,
                                   size_t quantidade) {
    PilhaPtr pilhaDeFilas;
    pilhaPtrInicializar(&pilhaDeFilas);

    for (size_t i = 0; i < quantidade; i++) {
        FilaInt *fila = criarFilaIntComValores(linhas[i], (size_t)tamanhos[i]);
        if (!fila) {
            printMensagemColoridaFormatted(RED, "Falha ao criar fila %zu.\n", i + 1);
            continue;
        }
        pilhaPtrEmpilhar(&pilhaDeFilas, fila);
    }

    printf("Consumo LIFO das filas empilhadas:\n");
    size_t indice = 1;
    void *dado = NULL;
    while ((dado = pilhaPtrDesempilhar(&pilhaDeFilas)) != NULL) {
        FilaInt *filaAtual = (FilaInt *)dado;
        printf("  Retirada %zu -> ", indice);
        imprimirFilaInt(filaAtual);
        printf("\n");
        filaIntLiberar(filaAtual);
        free(filaAtual);
        indice++;
    }
    printf("\n");
    pilhaPtrLiberar(&pilhaDeFilas, NULL);
}

void executarQuestaoFilas2Predefinido(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Filas - Questao 02 ===");
    printf("\nCombinacoes classicas envolvendo filas e pilhas.\n\n");

    const int filaA1[] = {10, 20};
    const int filaA2[] = {5, 7, 9};
    const int filaA3[] = {30};
    const int *filasFila[] = {filaA1, filaA2, filaA3};
    const int tamanhosFila[] = {2, 3, 1};

    const int pilhaB1[] = {1, 2, 3};
    const int pilhaB2[] = {7, 8};
    const int *pilhasFila[] = {pilhaB1, pilhaB2};
    const int tamanhosPilhas[] = {3, 2};

    const int filaC1[] = {4, 6};
    const int filaC2[] = {11, 13, 15};
    const int *filasPilha[] = {filaC1, filaC2};
    const int tamanhosFilasPilha[] = {2, 3};

    printMensagemColoridaFormatted(YELLOW, "a) Fila de Filas\n");
    demonstrarFilaDeFilas(filasFila, tamanhosFila, 3);

    printMensagemColoridaFormatted(YELLOW, "b) Fila de Pilhas\n");
    demonstrarFilaDePilhas(pilhasFila, tamanhosPilhas, 2);

    printMensagemColoridaFormatted(YELLOW, "c) Pilha de Filas\n");
    demonstrarPilhaDeFilas(filasPilha, tamanhosFilasPilha, 2);

    pausar();
}

static int lerInteiro(const char *mensagem, int *destino, int minimo, int maximo) {
    if (mensagem) {
        printMensagemColoridaInline(GREEN, mensagem);
        printf(": ");
    }
    if (scanf("%d", destino) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida.\n");
        return 0;
    }
    limparBufferTeclado();
    if (minimo != maximo) {
        if (*destino < minimo || *destino > maximo) {
            printMensagemColoridaFormatted(RED,
                "\nValor deve estar entre %d e %d.\n",
                minimo, maximo);
            return 0;
        }
    }
    return 1;
}

static FilaInt *criarFilaIntManual(int indice) {
    printf("\n--- Fila %d ---\n", indice);
    int quantidade = 0;
    if (!lerInteiro("Quantidade de elementos (0 a 10)", &quantidade, 0, 10)) {
        return NULL;
    }

    FilaInt *fila = (FilaInt *)malloc(sizeof(FilaInt));
    if (!fila) {
        printMensagemColoridaFormatted(RED, "Falha ao alocar fila.\n");
        return NULL;
    }
    filaIntInicializar(fila);

    for (int i = 0; i < quantidade; i++) {
        int valor = 0;
        char prompt[64];
        snprintf(prompt, sizeof(prompt), "Valor %d", i + 1);
        if (!lerInteiro(prompt, &valor, -1000000, 1000000)) {
            filaIntLiberar(fila);
            free(fila);
            return NULL;
        }
        filaIntEnfileirar(fila, valor);
    }

    return fila;
}

static PilhaInt *criarPilhaIntManual(int indice) {
    printf("\n--- Pilha %d ---\n", indice);
    int quantidade = 0;
    if (!lerInteiro("Quantidade de elementos (0 a 10)", &quantidade, 0, 10)) {
        return NULL;
    }

    PilhaInt *pilha = (PilhaInt *)malloc(sizeof(PilhaInt));
    if (!pilha) {
        printMensagemColoridaFormatted(RED, "Falha ao alocar pilha.\n");
        return NULL;
    }
    pilhaIntInicializar(pilha);

    for (int i = 0; i < quantidade; i++) {
        int valor = 0;
        char prompt[64];
        snprintf(prompt, sizeof(prompt), "Valor %d (empilhado nessa ordem)", i + 1);
        if (!lerInteiro(prompt, &valor, -1000000, 1000000)) {
            pilhaIntLiberar(pilha);
            free(pilha);
            return NULL;
        }
        pilhaIntEmpilhar(pilha, valor);
    }

    return pilha;
}

static void demonstrarFilaDeFilasManual(void) {
    printMensagemColoridaFormatted(YELLOW, "\n>>> Montagem manual - Fila de Filas <<<\n");
    int quantidade = 0;
    if (!lerInteiro("Quantas filas deseja enfileirar (1 a 5)", &quantidade, 1, 5)) {
        return;
    }

    FilaPtr filaDeFilas;
    filaPtrInicializar(&filaDeFilas);

    for (int i = 0; i < quantidade; i++) {
        FilaInt *fila = criarFilaIntManual(i + 1);
        if (fila) {
            filaPtrEnfileirar(&filaDeFilas, fila);
        }
    }

    if (!filaDeFilas.tamanho) {
        printMensagemColoridaFormatted(YELLOW, "\nNenhuma fila valida cadastrada.\n");
        filaPtrLiberar(&filaDeFilas, NULL);
        return;
    }

    printf("\nProcessando as filas na ordem de chegada:\n");
    size_t indice = 1;
    void *dado = NULL;
    while ((dado = filaPtrDesenfileirar(&filaDeFilas)) != NULL) {
        FilaInt *filaAtual = (FilaInt *)dado;
        printf("  Fila %zu -> ", indice);
        imprimirFilaInt(filaAtual);
        printf("\n");
        filaIntLiberar(filaAtual);
        free(filaAtual);
        indice++;
    }
    printf("\n");
    filaPtrLiberar(&filaDeFilas, NULL);
}

static void demonstrarFilaDePilhasManual(void) {
    printMensagemColoridaFormatted(YELLOW, "\n>>> Montagem manual - Fila de Pilhas <<<\n");
    int quantidade = 0;
    if (!lerInteiro("Quantas pilhas deseja enfileirar (1 a 5)", &quantidade, 1, 5)) {
        return;
    }

    FilaPtr filaDePilhas;
    filaPtrInicializar(&filaDePilhas);

    for (int i = 0; i < quantidade; i++) {
        PilhaInt *pilha = criarPilhaIntManual(i + 1);
        if (pilha) {
            filaPtrEnfileirar(&filaDePilhas, pilha);
        }
    }

    if (!filaDePilhas.tamanho) {
        printMensagemColoridaFormatted(YELLOW, "\nNenhuma pilha valida cadastrada.\n");
        filaPtrLiberar(&filaDePilhas, NULL);
        return;
    }

    printf("\nProcessando cada pilha em FIFO:\n");
    size_t indice = 1;
    void *dado = NULL;
    while ((dado = filaPtrDesenfileirar(&filaDePilhas)) != NULL) {
        PilhaInt *pilhaAtual = (PilhaInt *)dado;
        printf("  Pilha %zu -> ", indice);
        imprimirPilhaInt(pilhaAtual);
        printf("\n");
        pilhaIntLiberar(pilhaAtual);
        free(pilhaAtual);
        indice++;
    }
    printf("\n");
    filaPtrLiberar(&filaDePilhas, NULL);
}

static void demonstrarPilhaDeFilasManual(void) {
    printMensagemColoridaFormatted(YELLOW, "\n>>> Montagem manual - Pilha de Filas <<<\n");
    int quantidade = 0;
    if (!lerInteiro("Quantas filas deseja empilhar (1 a 5)", &quantidade, 1, 5)) {
        return;
    }

    PilhaPtr pilhaDeFilas;
    pilhaPtrInicializar(&pilhaDeFilas);

    for (int i = 0; i < quantidade; i++) {
        FilaInt *fila = criarFilaIntManual(i + 1);
        if (fila) {
            pilhaPtrEmpilhar(&pilhaDeFilas, fila);
        }
    }

    if (!pilhaDeFilas.tamanho) {
        printMensagemColoridaFormatted(YELLOW, "\nNenhuma fila valida empilhada.\n");
        pilhaPtrLiberar(&pilhaDeFilas, NULL);
        return;
    }

    printf("\nProcessando as filas em ordem LIFO:\n");
    size_t indice = 1;
    void *dado = NULL;
    while ((dado = pilhaPtrDesempilhar(&pilhaDeFilas)) != NULL) {
        FilaInt *filaAtual = (FilaInt *)dado;
        printf("  Retirada %zu -> ", indice);
        imprimirFilaInt(filaAtual);
        printf("\n");
        filaIntLiberar(filaAtual);
        free(filaAtual);
        indice++;
    }
    printf("\n");
    pilhaPtrLiberar(&pilhaDeFilas, NULL);
}

void executarQuestaoFilas2EntradaManual(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Filas - Questao 02 (Valores informados) ===");
    printf("\nMonte manualmente cada uma das combinacoes solicitadas.\n");

    demonstrarFilaDeFilasManual();
    demonstrarFilaDePilhasManual();
    demonstrarPilhaDeFilasManual();

    pausar();
}

void executarQuestaoFilas2(void) {
    executarQuestaoFilas2Predefinido();
}
