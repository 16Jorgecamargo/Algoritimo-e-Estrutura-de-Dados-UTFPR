#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../index.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/clean.h"
#include "../../../shared/headlers/animacao.h"

// Questao 9: Alocacao dinamica de matrizes usando 1 + m chamadas a malloc

static int** alocarMatriz(int m, int n) {
    int **matriz = (int**)malloc((size_t)m * sizeof(int*));
    if (matriz == NULL) {
        return NULL;
    }

    for (int i = 0; i < m; i++) {
        matriz[i] = (int*)malloc((size_t)n * sizeof(int));
        if (matriz[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matriz[j]);
            }
            free(matriz);
            return NULL;
        }
    }

    return matriz;
}

static void liberarMatriz(int **matriz, int m) {
    if (!matriz) return;
    for (int i = 0; i < m; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

static void preencherMatriz(int **matriz, int m, int n) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = (rand() % 99) + 1;
        }
    }
}

static void imprimirMatriz(int **matriz, int m, int n) {
    printMensagemColoridaFormatted(CYAN, "\nMatriz %dx%d:", m, n);

    for (int i = 0; i < m; i++) {
        printf("[ ");
        for (int j = 0; j < n; j++) {
            printf("%3d", matriz[i][j]);
            if (j < n - 1) printf(", ");
        }
        printf(" ]\n");
    }
    printf("\n");
}

static void mostrarResumoTeorico(int m) {
    printMensagemColoridaFormatted(CYAN, "Resumo da alocacao dinamica:\n");
    printf("- 1 chamada a malloc para o vetor de ponteiros (linhas)\n");
    printf("- %d chamadas a malloc para as %d linhas\n", m, m);
    printf("Total: 1 + %d chamadas a malloc\n\n", m);

    printf("Liberacao:\n");
    printf("- %d chamadas a free (uma por linha)\n", m);
    printf("- 1 chamada a free para o vetor de ponteiros\n");
    printf("Total: %d + 1 chamadas a free\n\n", m);
}

static void executarDemonstracao(int m, int n) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Ponteiros - Questao 09 ===\n\n");

    printMensagemColoridaFormatted(CYAN, "Demonstracao com matriz %dx%d\n", m, n);

    printComAnimacao("Alocando matriz dinamicamente");
    int **matriz = alocarMatriz(m, n);

    if (matriz == NULL) {
        printMensagemColoridaFormatted(RED, "Erro ao alocar matriz!\n");
        pausar();
        return;
    }

    printMensagemColoridaFormatted(GREEN, "Matriz alocada com sucesso. Total de mallocs: 1 + %d = %d", m, 1 + m);

    printComAnimacao("Preenchendo matriz com valores aleatorios");
    preencherMatriz(matriz, m, n);

    imprimirMatriz(matriz, m, n);
    mostrarResumoTeorico(m);

    printComAnimacao("Liberando memoria");
    liberarMatriz(matriz, m);
    printMensagemColoridaFormatted(GREEN, "Memoria liberada com sucesso. Total de frees: %d + 1 = %d", m, m + 1);

    pausar();
}

static void fluxoInterativo(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Ponteiros - Questao 09 ===\n\n");

    int m, n;
    printf("Digite o numero de linhas (m): ");
    if (scanf("%d", &m) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }

    printf("Digite o numero de colunas (n): ");
    if (scanf("%d", &n) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (m <= 0 || n <= 0) {
        printMensagemColoridaFormatted(RED, "\nDimensoes invalidas!");
        pausar();
        return;
    }

    printComAnimacao("Alocando matriz");
    int **matriz = alocarMatriz(m, n);

    if (matriz == NULL) {
        printMensagemColoridaFormatted(RED, "\nErro ao alocar memoria!");
        pausar();
        return;
    }

    printMensagemColoridaFormatted(GREEN, "Matriz alocada! (%d mallocs usados)", 1 + m);

    int escolha;
    printf("\nPreencher com valores aleatorios (1) ou digitar manualmente (2)? ");
    if (scanf("%d", &escolha) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        liberarMatriz(matriz, m);
        pausar();
        return;
    }
    limparBufferTeclado();

    if (escolha == 1) {
        printComAnimacao("Preenchendo com valores aleatorios");
        preencherMatriz(matriz, m, n);
    } else {
        printf("\nDigite os valores linha a linha:\n");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                printf("Elemento [%d][%d]: ", i, j);
                if (scanf("%d", &matriz[i][j]) != 1) {
                    limparBufferTeclado();
                    matriz[i][j] = 0;
                }
                limparBufferTeclado();
            }
        }
    }

    imprimirMatriz(matriz, m, n);
    mostrarResumoTeorico(m);

    printComAnimacao("Liberando memoria");
    liberarMatriz(matriz, m);
    printMensagemColoridaFormatted(GREEN, "Memoria liberada com sucesso!\n");

    pausar();
}

void executarQuestaoPonteiros9(void) {
    executarQuestaoPonteiros9Predefinido();
}

void executarQuestaoPonteiros9Predefinido(void) {
    executarDemonstracao(3, 4);
}

void executarQuestaoPonteiros9EntradaManual(void) {
    fluxoInterativo();
}
