#ifndef PILHA_INT_UTILS_H
#define PILHA_INT_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include "../../../shared/headlers/color.h"

typedef struct NoInt {
    int valor;
    struct NoInt *prox;
} NoInt;

typedef struct {
    NoInt *topo;
} PilhaInt;

static inline void pilhaIntInicializar(PilhaInt *pilha) {
    pilha->topo = NULL;
}

static inline int pilhaIntVazia(const PilhaInt *pilha) {
    return pilha->topo == NULL;
}

static inline void pilhaIntLiberar(PilhaInt *pilha) {
    NoInt *atual = pilha->topo;
    while (atual != NULL) {
        NoInt *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    pilha->topo = NULL;
}

static inline int pilhaIntPush(PilhaInt *pilha, int valor) {
    NoInt *novo = (NoInt *)malloc(sizeof(NoInt));
    if (!novo) {
        return 0;
    }
    novo->valor = valor;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    return 1;
}

static inline int pilhaIntPop(PilhaInt *pilha, int *valor) {
    if (pilhaIntVazia(pilha)) {
        return 0;
    }
    NoInt *removido = pilha->topo;
    pilha->topo = removido->prox;
    if (valor) {
        *valor = removido->valor;
    }
    free(removido);
    return 1;
}

static inline int pilhaIntTamanho(const PilhaInt *pilha) {
    int cont = 0;
    for (NoInt *no = pilha->topo; no != NULL; no = no->prox) {
        cont++;
    }
    return cont;
}

static inline int pilhaIntTopo(const PilhaInt *pilha, int *valor) {
    if (!pilha->topo) {
        return 0;
    }
    if (valor) {
        *valor = pilha->topo->valor;
    }
    return 1;
}

static inline void pilhaIntImprimir(const PilhaInt *pilha) {
    setColor(CYAN);
    printf("Topo -> ");
    resetColor();
    for (NoInt *no = pilha->topo; no != NULL; no = no->prox) {
        printf("[%d] ", no->valor);
    }
    printf("\n");
}

#endif
