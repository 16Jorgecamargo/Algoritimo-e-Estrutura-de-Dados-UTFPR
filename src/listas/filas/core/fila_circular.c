#include <stdlib.h>
#include "fila_circular.h"

int filaCircularInicializar(FilaCircular *fila, int capacidade) {
    if (!fila || capacidade <= 0) {
        return 0;
    }

    fila->dados = (float *)malloc((size_t)capacidade * sizeof(float));
    if (!fila->dados) {
        fila->capacidade = 0;
        fila->inicio = 0;
        fila->tamanho = 0;
        return 0;
    }

    fila->capacidade = capacidade;
    fila->inicio = 0;
    fila->tamanho = 0;
    return 1;
}

void filaCircularLiberar(FilaCircular *fila) {
    if (!fila) {
        return;
    }

    free(fila->dados);
    fila->dados = NULL;
    fila->capacidade = 0;
    fila->inicio = 0;
    fila->tamanho = 0;
}

int filaCircularVazia(const FilaCircular *fila) {
    return !fila || fila->tamanho == 0;
}

int filaCircularCheia(const FilaCircular *fila) {
    return fila && fila->tamanho == fila->capacidade;
}

int filaCircularEnfileirar(FilaCircular *fila, float valor) {
    if (!fila || !fila->dados || filaCircularCheia(fila)) {
        return 0;
    }

    int posicao = (fila->inicio + fila->tamanho) % fila->capacidade;
    fila->dados[posicao] = valor;
    fila->tamanho++;
    return 1;
}

int filaCircularDesenfileirar(FilaCircular *fila, float *valor) {
    if (!fila || !fila->dados || filaCircularVazia(fila)) {
        return 0;
    }

    if (valor) {
        *valor = fila->dados[fila->inicio];
    }

    fila->inicio = (fila->inicio + 1) % fila->capacidade;
    fila->tamanho--;
    return 1;
}

int filaCircularPrimeiro(const FilaCircular *fila, float *valor) {
    if (!fila || !fila->dados || filaCircularVazia(fila) || !valor) {
        return 0;
    }
    *valor = fila->dados[fila->inicio];
    return 1;
}

int filaCircularFuraFila(FilaCircular *fila, float valor) {
    if (!fila || !fila->dados || filaCircularCheia(fila)) {
        return 0;
    }

    fila->inicio = (fila->inicio - 1 + fila->capacidade) % fila->capacidade;
    fila->dados[fila->inicio] = valor;
    fila->tamanho++;
    return 1;
}
