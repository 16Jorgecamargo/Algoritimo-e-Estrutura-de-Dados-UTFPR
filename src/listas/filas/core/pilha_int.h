#ifndef PILHA_INT_H
#define PILHA_INT_H

#include <stddef.h>

typedef struct NoPilhaInt {
    int valor;
    struct NoPilhaInt *prox;
} NoPilhaInt;

typedef struct {
    NoPilhaInt *topo;
    size_t tamanho;
} PilhaInt;

void pilhaIntInicializar(PilhaInt *pilha);
void pilhaIntLiberar(PilhaInt *pilha);
int pilhaIntEmpilhar(PilhaInt *pilha, int valor);
int pilhaIntDesempilhar(PilhaInt *pilha, int *valor);
int pilhaIntTopo(const PilhaInt *pilha, int *valor);
int pilhaIntVazia(const PilhaInt *pilha);
size_t pilhaIntTamanho(const PilhaInt *pilha);

#endif
