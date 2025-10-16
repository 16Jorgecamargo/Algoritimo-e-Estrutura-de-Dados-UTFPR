#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../index.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/clean.h"

// Questao 7: Cadastro de produtos com struct

typedef struct {
    int codigo;
    char nome[50];
    float preco;
} Produto;

static Produto* produtos = NULL;
static int numProdutos = 0;

static void liberarProdutos(void) {
    if (produtos != NULL) {
        free(produtos);
        produtos = NULL;
        numProdutos = 0;
    }
}

static void inicializarProdutos(void) {
    liberarProdutos();

    numProdutos = 5;
    produtos = (Produto*)malloc((size_t)numProdutos * sizeof(Produto));
    if (!produtos) {
        numProdutos = 0;
        return;
    }

    produtos[0] = (Produto){10, "Arroz", 8.50f};
    produtos[1] = (Produto){15, "Feijao", 10.00f};
    produtos[2] = (Produto){20, "Acucar", 5.20f};
    produtos[3] = (Produto){25, "Cafe", 12.30f};
    produtos[4] = (Produto){30, "Leite", 4.80f};
}

static void garantirProdutosIniciais(void) {
    if (produtos == NULL) {
        inicializarProdutos();
    }
}

static void listarProdutos(void) {
    printMensagemColoridaFormatted(CYAN, "\n=== LISTA DE PRODUTOS ===\n");

    printf("%-8s %-20s %s\n", "Codigo", "Nome", "Preco");
    printf("----------------------------------------\n");

    for (int i = 0; i < numProdutos; i++) {
        printf("%-8d %-20s R$ %.2f\n",
               produtos[i].codigo,
               produtos[i].nome,
               produtos[i].preco);
    }
    printf("\n");
}

static Produto* buscarProduto(int codigo) {
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            return &produtos[i];
        }
    }
    return NULL;
}

static void demonstrarCadastroCompleto(void) {
    garantirProdutosIniciais();

    printMensagemColoridaFormatted(YELLOW, "=== Ponteiros - Questao 07 ===\n\n");

    listarProdutos();

    int codigoDemo = 15;
    Produto *p = buscarProduto(codigoDemo);
    if (p) {
        printMensagemColoridaFormatted(GREEN, "Busca automatica pelo codigo %d:\n", codigoDemo);
        printf("Produto: %s\n", p->nome);
        printf("Preco  : R$ %.2f\n", p->preco);
        printf("Codigo : %d\n\n", p->codigo);
    }

    printMensagemColoridaFormatted(GREEN, "Total de produtos cadastrados: %d", numProdutos);

    pausar();
}

static void fluxoInterativo(void) {
    garantirProdutosIniciais();

    printMensagemColoridaFormatted(YELLOW, "=== Ponteiros - Questao 07 ===\n\n");

    int opcao;
    printf("Escolha uma opcao:\n");
    printf("1 - Listar todos os produtos\n");
    printf("2 - Buscar produto por codigo\n");
    printf("Opcao: ");
    if (scanf("%d", &opcao) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (opcao == 1) {
        listarProdutos();
        printMensagemColoridaFormatted(GREEN, "Total de produtos cadastrados: %d", numProdutos);
    } else if (opcao == 2) {
        int codigo;
        printf("Digite o codigo do produto: ");
        if (scanf("%d", &codigo) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
            pausar();
            return;
        }
        limparBufferTeclado();

        Produto *p = buscarProduto(codigo);
        printf("\n");
        if (p) {
            printMensagemColoridaFormatted(GREEN, "== PRODUTO ENCONTRADO ==\n");
            printf("Produto: %s\n", p->nome);
            printf("Preco  : R$ %.2f\n", p->preco);
            printf("Codigo : %d\n", p->codigo);
        } else {
            printMensagemColoridaFormatted(RED, "Produto com codigo %d nao encontrado!", codigo);
        }
    } else {
        printMensagemColoridaFormatted(RED, "\nOpcao invalida.");
    }

    pausar();
}

void executarQuestaoPonteiros7(void) {
    executarQuestaoPonteiros7Predefinido();
}

void executarQuestaoPonteiros7Predefinido(void) {
    demonstrarCadastroCompleto();
}

void executarQuestaoPonteiros7EntradaManual(void) {
    fluxoInterativo();
}
