#ifndef PILHA_CHAR_UTILS_H
#define PILHA_CHAR_UTILS_H

#include <stdlib.h>

typedef struct NoChar {
    char caractere;
    struct NoChar *prox;
} NoChar;

typedef struct {
    NoChar *topo;
} PilhaChar;

static inline void pilhaCharInit(PilhaChar *pilha) {
    pilha->topo = NULL;
}

static inline void pilhaCharFree(PilhaChar *pilha) {
    NoChar *no = pilha->topo;
    while (no) {
        NoChar *prox = no->prox;
        free(no);
        no = prox;
    }
    pilha->topo = NULL;
}

static inline int pilhaCharPush(PilhaChar *pilha, char c) {
    NoChar *novo = (NoChar *)malloc(sizeof(NoChar));
    if (!novo) return 0;
    novo->caractere = c;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    return 1;
}

static inline int pilhaCharPop(PilhaChar *pilha, char *c) {
    if (!pilha->topo) return 0;
    NoChar *removido = pilha->topo;
    pilha->topo = removido->prox;
    if (c) *c = removido->caractere;
    free(removido);
    return 1;
}

#endif
