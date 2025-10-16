#include <stdio.h>
#include <string.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

// Questao 6: Imprimir string inversa usando ponteiros e recursao

static void imprimirInverso(const char *cptr) {
    if (*cptr != '\0') {
        imprimirInverso(cptr + 1);
        putchar(*cptr);
    }
}

static void executarComString(const char *entrada) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Ponteiros - Questao 06 ===\n\n");

    printMensagemColoridaInline(CYAN, "String original: ");
    printf("\"%s\"\n\n", entrada);

    printMensagemColoridaInline(CYAN, "String inversa: ");
    printf("\"");
    imprimirInverso(entrada);
    printf("\"\n\n");

    printMensagemColoridaInline(GREEN, "Explicacao: ");
    printf("O ponteiro avanca ate o terminador (\\0) e imprime na volta da recursao.\n");

    pausar();
}

void executarQuestaoPonteiros6(void) {
    executarQuestaoPonteiros6Predefinido();
}

void executarQuestaoPonteiros6Predefinido(void) {
    executarComString("abcde");
}

void executarQuestaoPonteiros6EntradaManual(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Ponteiros - Questao 06 ===\n\n");

    char s[100];
    printMensagemColoridaInline(YELLOW, "Digite uma string (max 99 caracteres): ");

    if (fgets(s, sizeof(s), stdin) == NULL) {
        printMensagemColoridaFormatted(RED, "\nNao foi possivel ler a string.");
        pausar();
        return;
    }

    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    }

    executarComString(s);
}
