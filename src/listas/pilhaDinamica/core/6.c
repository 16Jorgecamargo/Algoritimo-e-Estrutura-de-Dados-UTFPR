#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "../../../shared/headlers/colorPrint.h"
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/clean.h"
#include "../../../shared/headlers/animacao.h"
#include "pilha_char_utils.h"

static void inverterTexto(const char *texto, char *saida) {
    PilhaChar pilha;
    pilhaCharInit(&pilha);

    for (const char *p = texto; *p != '\0'; ++p) {
        pilhaCharPush(&pilha, *p);
    }

    size_t i = 0;
    char c;
    while (pilhaCharPop(&pilha, &c)) {
        saida[i++] = c;
    }
    saida[i] = '\0';

    pilhaCharFree(&pilha);
}

static void sanitizarTexto(const char *origem, char *destino) {
    size_t i = 0;
    for (const char *p = origem; *p != '\0'; ++p) {
        if (*p == ' ' || *p == '.') {
            continue;
        }
        destino[i++] = (char)toupper((unsigned char)*p);
    }
    destino[i] = '\0';
}

static int verificarPalindromo(const char *texto) {
    char filtrado[1024];
    sanitizarTexto(texto, filtrado);

    PilhaChar pilha;
    pilhaCharInit(&pilha);

    for (size_t i = 0; filtrado[i] != '\0'; ++i) {
        pilhaCharPush(&pilha, filtrado[i]);
    }

    size_t i = 0;
    char c;
    int palindromo = 1;
    while (palindromo && pilhaCharPop(&pilha, &c)) {
        if (c != filtrado[i++]) {
            palindromo = 0;
        }
    }

    pilhaCharFree(&pilha);
    return palindromo;
}

static void demonstrarTexto(const char *texto) {
    char invertido[1024];

    printMensagemColoridaInline(CYAN, "Texto original: ");
    printf("%s\n\n", texto);

    printComAnimacao("Invertendo texto usando pilha");
    inverterTexto(texto, invertido);

    printMensagemColoridaInline(CYAN, "Texto invertido: ");
    printf("%s\n\n", invertido);

    printComAnimacao("Verificando se e palindromo");
    int resultado = verificarPalindromo(texto);
    printMensagemColoridaFormatted(GREEN, "Resultado: %s\n", resultado ? "SIM, e palindromo!" : "NAO e palindromo");
}

static void cabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Pilha Dinamica - Questao 06 ===");
    printf("\n");
}

static void demonstracaoPredefinida(void) {
    const char *texto = "Socorram-me subi no onibus em Marrocos";
    demonstrarTexto(texto);
    pausar();
}

static void fluxoManual(void) {
    char texto[1024];
    printf("Digite um texto (ate 1023 caracteres):\n");
    if (!fgets(texto, sizeof(texto), stdin)) {
        printMensagemColoridaFormatted(RED, "Erro ao ler a string!\n");
        pausar();
        return;
    }

    size_t len = strlen(texto);
    if (len > 0 && texto[len - 1] == '\n') {
        texto[len - 1] = '\0';
    }

    demonstrarTexto(texto);
    pausar();
}

void executarQuestaoPilhaDinamica6(void) {
    executarQuestaoPilhaDinamica6Predefinido();
}

void executarQuestaoPilhaDinamica6Predefinido(void) {
    cabecalho();
    demonstracaoPredefinida();
}

void executarQuestaoPilhaDinamica6EntradaManual(void) {
    cabecalho();
    fluxoManual();
}