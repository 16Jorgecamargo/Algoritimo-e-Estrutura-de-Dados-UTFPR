#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headlers/7.h"
#include "../../../shared/headlers/clean.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"

void cadastrarProduto(Produto *p){
    char nome[5][50] = {"feijao", "arroz", "macarrao", "batata", "pao"};
    float precos[5] = {4.99, 3.49, 2.99, 1.99, 0.99};
    for (int i= 0; i< 5; i++) {
        p[i].codigo = i+1; 
        strcpy(p[i].produto, nome[i]);
        p[i].preco = precos[i];
    }
}

void imprimirProduto(Produto *p) {
    printf("\nProduto: %s\n", p->produto);
    printf("Preco: %.2f\n", p->preco);
    printf("Codigo: %d\n", p->codigo);
}

void buscarProduto(Produto *produtos, int tamanho, int codigo) {
    for (int i = 0; i < tamanho; i++) {
        if (produtos[i].codigo == codigo) {
            imprimirProduto(&produtos[i]);
            return;
        }
    }
    printf("Produto com codigo %d nao encontrado.\n", codigo);
}

int mostrarMenuQuestaoPonteiros7(Produto *p){
    int op;
    int qtd=5;
    do
    {
        limparTela();
        setColor(YELLOW);
        printf("=== Ponteiros ===\n");
        printf("=== Executando a Questao 7 ===\n\n");
        resetColor();
        printf("Escolha uma opcao:\n");
        printMenuItem(1, "Listar todos produtos");
        printMenuItem(2, "Buscar Produto");
        printMenuItem(3, "Adicionar Produto");
        printMenuItem(0, "Voltar");
        setColor(YELLOW);
        printf("> ");

        if (scanf("%d", &op) != 1)
        {
            setColor(RED);
            printf("Entrada invalida! Digite apenas numeros.\n");
            resetColor();
            while (getchar() != '\n')
                ;
            printf("\n\nPressione Enter para continuar...");
            getchar();
            continue;
        }
        resetColor();
        processarOpcaoQuestaoPonteiros7(op, &p, &qtd);
    } while (op != 0);
    return (op == 0) ? 0 : 1;
}

void processarOpcaoQuestaoPonteiros7(int op, Produto **p, int *qtd){
    int cod;
    switch (op)
    {
    case 1:
        setColor(YELLOW);
        printf("Produtos cadastrados:\n");
        for (int i = 0; i < *qtd; i++) {
            if ((*p)[i].codigo != 0) {
                imprimirProduto(&(*p)[i]);
            }
        }
        resetColor();
        pausar();
        break;
    case 2:
        setColor(YELLOW);
        printf("Digite o codigo do produto: ");
        scanf("%d", &cod);
        resetColor();
        buscarProduto(*p, *qtd, cod);
        pausar();
        break;
    case 3:
        (*qtd)++;
        *p = realloc(*p, (*qtd) * sizeof(Produto));
        setColor(YELLOW);
        printf("Codigo do produto: %d\n", *qtd);
        (*p)[*qtd-1].codigo = *qtd;
        printf("Digite o nome do produto: ");
        scanf("%s", (*p)[*qtd-1].produto);
        printf("Digite o preco do produto: ");
        scanf("%f", &(*p)[*qtd-1].preco);
        resetColor();
        pausar();
        break;
    case 0:
        return;
    default:
        setColor(RED);
        printf("Opcao invalida! Digite um numero entre 0 e 3.\n");
        resetColor();
        printf("\n\nPressione Enter para continuar...");
        while (getchar() != '\n');
        getchar();
        limparTela();
        break;
    }
}

void executarQuestaoPonteiros7(void) {
    Produto *produtos = malloc(5 * sizeof(Produto));
    if (produtos == NULL) {
        fprintf(stderr, "Erro ao alocar memoria.\n");
        return;
    }
    cadastrarProduto(produtos);
    mostrarMenuQuestaoPonteiros7(produtos);
    ungetc('\n', stdin);
    free(produtos);
}
