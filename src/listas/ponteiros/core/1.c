#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

// Questao 1: Diferencas entre p++, (*p)++, *(p++), *(p+10)

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Ponteiros - Questao 01 ===");
    printf("\n");
}

static void imprimirArray(const int *valores, int tamanho) {
    printf("{ ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d", valores[i]);
        if (i < tamanho - 1) {
            printf(", ");
        }
    }
    printf(" }");
}

static void demonstrarOperacoes(int *arr, int tamanho) {
    imprimirCabecalho();

    if (tamanho <= 0) {
        printMensagemColoridaFormatted(RED, "Erro: vetor vazio!\n");
        pausar();
        return;
    }

    printMensagemColoridaInline(CYAN, "Vetor de trabalho: ");
    imprimirArray(arr, tamanho);
    printf("\n\n");

    int *p = arr;

    // Demonstração 1: p++
    printf("1. p++  (incrementa o ENDERECO do ponteiro)\n");
    printf("   Antes: p aponta para %d (endereco: %p)\n", *p, (void*)p);
    if (tamanho > 1) {
        int *p1 = arr;
        p1++;
        printf("   Depois: p aponta para %d (endereco: %p)\n", *p1, (void*)p1);
        printMensagemColoridaFormatted(GREEN, "   >>> Move o ponteiro para o proximo elemento\n");
    } else {
        printMensagemColoridaFormatted(RED, "   >>> Vetor com apenas um elemento - nao ha proximo endereco valido\n");
    }

    // Demonstração 2: (*p)++
    printf("2. (*p)++  (incrementa o VALOR apontado)\n");
    int valor = arr[0];
    int *p2 = &valor;
    printf("   Antes: *p = %d\n", *p2);
    (*p2)++;
    printf("   Depois: *p = %d\n", *p2);
    printMensagemColoridaFormatted(GREEN, "   >>> Incrementa o conteudo, nao o endereco\n\n");

    // Demonstração 3: *(p++)
    printf("3. *(p++)  (retorna valor atual, DEPOIS incrementa endereco)\n");
    int *p3 = arr;
    printf("   Valor retornado: %d\n", *(p3++));
    if (p3 < arr + tamanho) {
        printf("   Proximo valor (apos incremento): %d\n", *p3);
    } else {
        printf("   Proximo endereco ultrapassa o vetor (incremento causou overflow de indice).\n");
    }
    printMensagemColoridaFormatted(GREEN, "   >>> Usa valor atual, depois move ponteiro\n\n");

    // Demonstração 4: *(p+10)
    printf("4. *(p+10)  (acessa elemento 10 posicoes a frente)\n");
    printf("   arr[0] = %d\n", arr[0]);
    if (tamanho > 10) {
        printf("   *(arr+10) = %d\n", *(arr + 10));
    } else {
        printMensagemColoridaFormatted(RED, "   AVISO: Vetor nao tem 10 elementos!\n");
        if (tamanho > 2) {
            printf("   *(arr+2) = %d (exemplo seguro)\n", *(arr + 2));
        }
    }
    printMensagemColoridaFormatted(GREEN, "   >>> Acessa memoria diretamente via aritmetica de ponteiros\n");

    pausar();
}

void executarQuestaoPonteiros1(void) {
    executarQuestaoPonteiros1Predefinido();
}

void executarQuestaoPonteiros1Predefinido(void) {
    int arr[] = {10, 20, 30, 40, 50};
    demonstrarOperacoes(arr, (int)(sizeof(arr) / sizeof(arr[0])));
}

void executarQuestaoPonteiros1EntradaManual(void) {
    imprimirCabecalho();

    int tamanho;
    printf("Informe quantos elementos deseja inserir (1 a 20): ");
    if (scanf("%d", &tamanho) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (tamanho < 1 || tamanho > 20) {
        printMensagemColoridaFormatted(RED, "\nInforme um valor entre 1 e 20.");
        pausar();
        return;
    }

    int *arr = (int*)malloc((size_t)tamanho * sizeof(int));
    if (!arr) {
        printMensagemColoridaFormatted(RED, "\nFalha ao alocar memoria.");
        pausar();
        return;
    }

    printMensagemColoridaFormatted(CYAN, "\nDigite os %d valores:", tamanho);
    for (int i = 0; i < tamanho; i++) {
        printf("Elemento %d: ", i + 1);
        if (scanf("%d", &arr[i]) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "\nEntrada invalida! Encerrando demonstracao.");
            free(arr);
            pausar();
            return;
        }
        limparBufferTeclado();
    }

    demonstrarOperacoes(arr, tamanho);

    free(arr);
}
