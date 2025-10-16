#include <stdlib.h>
#include "fila_int.h"

void filaIntInicializar(FilaInt *fila) {
    if (!fila) {
        return;
    }
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

void filaIntLiberar(FilaInt *fila) {
    if (!fila) {
        return;
    }

    NoFilaInt *atual = fila->inicio;
    while (atual) {
        NoFilaInt *prox = atual->prox;
        free(atual);
        atual = prox;
    }

    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

int filaIntEnfileirar(FilaInt *fila, int valor) {
    if (!fila) {
        return 0;
    }

    NoFilaInt *novo = (NoFilaInt *)malloc(sizeof(NoFilaInt));
    if (!novo) {
        return 0;
    }

    novo->valor = valor;
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

int filaIntDesenfileirar(FilaInt *fila, int *valor) {
    if (!fila || !fila->inicio) {
        return 0;
    }

    NoFilaInt *removido = fila->inicio;
    if (valor) {
        *valor = removido->valor;
    }

    fila->inicio = removido->prox;
    if (!fila->inicio) {
        fila->fim = NULL;
    }

    fila->tamanho--;
    free(removido);
    return 1;
}

int filaIntPrimeiro(const FilaInt *fila, int *valor) {
    if (!fila || !fila->inicio || !valor) {
        return 0;
    }
    *valor = fila->inicio->valor;
    return 1;
}

int filaIntVazia(const FilaInt *fila) {
    return !fila || fila->inicio == NULL;
}

size_t filaIntTamanho(const FilaInt *fila) {
    return fila ? fila->tamanho : 0;
}
