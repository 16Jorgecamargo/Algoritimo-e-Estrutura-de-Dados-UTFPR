#include <stdlib.h>
#include "pilha_int.h"

void pilhaIntInicializar(PilhaInt *pilha) {
    if (!pilha) {
        return;
    }
    pilha->topo = NULL;
    pilha->tamanho = 0;
}

void pilhaIntLiberar(PilhaInt *pilha) {
    if (!pilha) {
        return;
    }

    NoPilhaInt *atual = pilha->topo;
    while (atual) {
        NoPilhaInt *prox = atual->prox;
        free(atual);
        atual = prox;
    }

    pilha->topo = NULL;
    pilha->tamanho = 0;
}

int pilhaIntEmpilhar(PilhaInt *pilha, int valor) {
    if (!pilha) {
        return 0;
    }

    NoPilhaInt *novo = (NoPilhaInt *)malloc(sizeof(NoPilhaInt));
    if (!novo) {
        return 0;
    }

    novo->valor = valor;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho++;
    return 1;
}

int pilhaIntDesempilhar(PilhaInt *pilha, int *valor) {
    if (!pilha || !pilha->topo) {
        return 0;
    }

    NoPilhaInt *removido = pilha->topo;
    if (valor) {
        *valor = removido->valor;
    }
    pilha->topo = removido->prox;
    pilha->tamanho--;
    free(removido);
    return 1;
}

int pilhaIntTopo(const PilhaInt *pilha, int *valor) {
    if (!pilha || !pilha->topo || !valor) {
        return 0;
    }
    *valor = pilha->topo->valor;
    return 1;
}

int pilhaIntVazia(const PilhaInt *pilha) {
    return !pilha || pilha->topo == NULL;
}

size_t pilhaIntTamanho(const PilhaInt *pilha) {
    return pilha ? pilha->tamanho : 0;
}
