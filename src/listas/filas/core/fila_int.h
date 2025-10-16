#ifndef FILA_INT_H
#define FILA_INT_H

#include <stddef.h>

typedef struct NoFilaInt {
    int valor;
    struct NoFilaInt *prox;
} NoFilaInt;

typedef struct {
    NoFilaInt *inicio;
    NoFilaInt *fim;
    size_t tamanho;
} FilaInt;

void filaIntInicializar(FilaInt *fila);
void filaIntLiberar(FilaInt *fila);
int filaIntEnfileirar(FilaInt *fila, int valor);
int filaIntDesenfileirar(FilaInt *fila, int *valor);
int filaIntVazia(const FilaInt *fila);
size_t filaIntTamanho(const FilaInt *fila);
int filaIntPrimeiro(const FilaInt *fila, int *valor);

#endif
