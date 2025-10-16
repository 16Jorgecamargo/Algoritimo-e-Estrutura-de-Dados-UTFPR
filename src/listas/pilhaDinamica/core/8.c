#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../../../shared/headlers/colorPrint.h"
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/clean.h"
#include "pilha_char_utils.h"

static int validarSequencia(const char *sequencia) {
    char limpo[512];
    size_t len = 0;
    int qtdC = 0;

    for (const char *p = sequencia; *p != '\0'; ++p) {
        if (*p == ' ') {
            continue;
        }
        char c = (char)toupper((unsigned char)*p);
        if (c == 'C') {
            qtdC++;
        }
        if (c != 'A' && c != 'B' && c != 'C') {
            return 0;
        }
        if (len >= sizeof(limpo) - 1) {
            return 0;
        }
        limpo[len++] = c;
    }
    limpo[len] = '\0';

    if (qtdC != 1) {
        return 0;
    }

    char *posC = strchr(limpo, 'C');
    size_t idxC = (size_t)(posC - limpo);

    PilhaChar pilha;
    pilhaCharInit(&pilha);

    for (size_t i = 0; i < idxC; ++i) {
        pilhaCharPush(&pilha, limpo[i]);
    }

    for (size_t i = idxC + 1; limpo[i] != '\0'; ++i) {
        char topo;
        if (!pilhaCharPop(&pilha, &topo) || topo != limpo[i]) {
            pilhaCharFree(&pilha);
            return 0;
        }
    }

    int valido = pilha.topo == NULL;
    pilhaCharFree(&pilha);
    return valido;
}

static void demonstrarCasos(void) {
    const char *validos[] = {
        "ABBA C ABBA",
        "ABABBA CBABAAB",
        " C "
    };
    const char *invalidos[] = {
        "ABAC",
        "AB C BA",
        "ABCD",
        "ABBA CABAB"
    };

    printMensagemColoridaInline(CYAN, "");
    for (size_t i = 0; i < sizeof(validos)/sizeof(validos[0]); ++i) {
        printf("'%s' -> %s\n", validos[i], validarSequencia(validos[i]) ? "valido" : "invalido");
    }

    printf("\n");
    printMensagemColoridaInline(CYAN, "");
    for (size_t i = 0; i < sizeof(invalidos)/sizeof(invalidos[0]); ++i) {
        printf("'%s' -> %s\n", invalidos[i], validarSequencia(invalidos[i]) ? "valido" : "invalido");
    }

    pausar();
}

static void fluxoManual(void) {
    char entrada[512];
    printf("Digite a cadeia a ser testada (use apenas A, B e uma letra C separando as partes):\n");
    if (!fgets(entrada, sizeof(entrada), stdin)) {
        printMensagemColoridaFormatted(RED, "Erro ao ler entrada!\n");
        pausar();
        return;
    }

    size_t len = strlen(entrada);
    if (len > 0 && entrada[len - 1] == '\n') {
        entrada[len - 1] = '\0';
    }

    int resultado = validarSequencia(entrada);
    printf("\nResultado: %s\n", resultado ? "cadeia valida" : "cadeia invalida");
    pausar();
}

static void cabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Pilha Dinamica - Questao 08 ===");
    printf("\n");
}

void executarQuestaoPilhaDinamica8(void) {
    executarQuestaoPilhaDinamica8Predefinido();
}

void executarQuestaoPilhaDinamica8Predefinido(void) {
    cabecalho();
    demonstrarCasos();
}

void executarQuestaoPilhaDinamica8EntradaManual(void) {
    cabecalho();
    fluxoManual();
}