#ifndef FILA_CIRCULAR_H
#define FILA_CIRCULAR_H

typedef struct {
    float *dados;
    int capacidade;
    int inicio;
    int tamanho;
} FilaCircular;

int filaCircularInicializar(FilaCircular *fila, int capacidade);
void filaCircularLiberar(FilaCircular *fila);
int filaCircularVazia(const FilaCircular *fila);
int filaCircularCheia(const FilaCircular *fila);
int filaCircularEnfileirar(FilaCircular *fila, float valor);
int filaCircularDesenfileirar(FilaCircular *fila, float *valor);
int filaCircularPrimeiro(const FilaCircular *fila, float *valor);
int filaCircularFuraFila(FilaCircular *fila, float valor);

#endif
