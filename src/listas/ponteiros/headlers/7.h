#ifndef PONTEIROS_7_H
#define PONTEIROS_7_H

typedef struct {
    char produto[50];
    float preco;
    int codigo;
} Produto;

void cadastrarProduto(Produto *p);
void buscarProduto(Produto *produtos, int tamanho, int codigo);
void listarProdutos(Produto *produtos, int tamanho);
int mostrarMenuQuestaoPonteiros7(Produto *p);
void processarOpcaoQuestaoPonteiros7(int op, Produto **p, int *qtd);
void executarQuestaoPonteiros7(void);

#endif
