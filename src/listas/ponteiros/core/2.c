#include <stdio.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/clean.h"
#include "../../../shared/headlers/colorPrint.h"

// Questao 2: Rastrear execucao de codigo com ponteiros

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Ponteiros - Questao 02 ===");
    printf("\n");
}

static void executarRastreamento(int valorInicialY, int valorAtribuidoX) {
    imprimirCabecalho();

    printMensagemColoridaFormatted(CYAN, "RASTREAMENTO PASSO A PASSO:\n");

    int y = valorInicialY;
    int *p = NULL;
    int x;

    printf("Linha 1: int y, *p, x;\n");
    printf("         Declaracao de variaveis (valores indefinidos)\n\n");

    printf("Linha 2: y = %d;\n", valorInicialY);
    printMensagemColoridaFormatted(GREEN, "         >>> y = %d\n", y);

    printf("Linha 3: p = &y;\n");
    p = &y;
    printf("         >>> p aponta para y (endereco: %p)\n", (void*)p);
    printf("         >>> *p = %d (valor de y)\n\n", *p);

    printf("Linha 4: x = *p;\n");
    x = *p;
    printMensagemColoridaFormatted(GREEN, "         >>> x = %d (copia o valor de y via ponteiro)\n", x);

    printf("Linha 5: x = %d;\n", valorAtribuidoX);
    x = valorAtribuidoX;
    printf("         >>> x = %d\n", x);
    printf("         >>> y ainda = %d (nao foi modificado)\n\n", y);

    printf("Linha 6: (*p)++;\n");
    (*p)++;
    printf("         >>> Incrementa o valor apontado por p (y)\n");
    printf("         >>> y = %d  (era %d, agora %d)\n", y, valorInicialY, y);
    printf("         >>> x = %d  (nao foi afetado)\n\n", x);

    printf("Linha 7: x--;\n");
    x--;
    printf("         >>> x = %d  (decrementado em 1)\n", x);
    printf("         >>> y = %d  (nao mudou)\n\n", y);

    printf("Linha 8: (*p) += x;\n");
    (*p) += x;
    printf("         >>> y = y + x = %d + %d = %d\n", y - x, x, y);
    printf("         >>> y = %d\n\n", y);

    printf("Linha 9: printf(\"y = %%d\\n\", y);\n");
    printMensagemColoridaFormatted(CYAN, "         Saida: y = %d\n", y);

    printMensagemColoridaInline(YELLOW, "IMPORTANTE: ");
    printf("p aponta para y, entao modificar *p modifica y!\n");

    pausar();
}

void executarQuestaoPonteiros2(void) {
    executarQuestaoPonteiros2Predefinido();
}

void executarQuestaoPonteiros2Predefinido(void) {
    executarRastreamento(0, 4);
}

void executarQuestaoPonteiros2EntradaManual(void) {
    imprimirCabecalho();

    int valorInicial, valorAtribuido;

    printf("Digite o valor inicial para y: ");
    if (scanf("%d", &valorInicial) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }

    printf("Digite o valor atribuido a x na linha 5: ");
    if (scanf("%d", &valorAtribuido) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    executarRastreamento(valorInicial, valorAtribuido);
}
