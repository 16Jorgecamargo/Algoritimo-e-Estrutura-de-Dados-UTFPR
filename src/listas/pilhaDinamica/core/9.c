#include <stdio.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"
#include "pilha_int_utils.h"

static void converterDecimalParaBinario(int numero) {
    if (numero < 0) {
        printMensagemColorida(RED, "Numero negativo nao suportado nesta demonstracao.");
        return;
    }

    if (numero == 0) {
        printf("0\n");
        return;
    }

    PilhaInt restos;
    pilhaIntInicializar(&restos);

    while (numero > 0) {
        pilhaIntPush(&restos, numero % 2);
        numero /= 2;
    }

    int bit;
    while (pilhaIntPop(&restos, &bit)) {
        printf("%d", bit);
    }
    printf("\n");
}

static void menuInterativo(void) {
    PilhaInt pilha;
    pilhaIntInicializar(&pilha);
    int pilhaInicializada = 0;

    int opcao = -1;
    while (opcao != 0) {
        limparTela();
        printf("\n");
        printMensagemColorida(CYAN, "Estado atual da pilha:");
        if (!pilhaInicializada) {
            printf("(Pilha ainda nao inicializada)\n");
        } else {
            pilhaIntImprimir(&pilha);
        }

        printf("\n1-Inicializa pilha.\n");
        printf("2-Verifica se a pilha e vazia.\n");
        printf("3-Verifica se a pilha e cheia.\n");
        printf("4-Empilha o elemento na pilha.\n");
        printf("5-Desempilha elemento da pilha.\n");
        printf("6-Le topo de uma pilha.\n");
        printf("7-Converte um numero decimal em binario.\n");
        printf("0-Sair.\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limparBufferTeclado();
            printMensagemColorida(RED, "Entrada invalida!");
            continue;
        }
        limparBufferTeclado();

        switch (opcao) {
        case 1:
            pilhaIntLiberar(&pilha);
            pilhaIntInicializar(&pilha);
            pilhaInicializada = 1;
            printMensagemColorida(GREEN, "Pilha inicializada com sucesso.");
            pausar();
            break;
        case 2:
            if (!pilhaInicializada) {
                printMensagemColorida(RED, "Inicialize a pilha primeiro.");
            } else {
                printf("Pilha %s vazia.\n", pilhaIntVazia(&pilha) ? "esta" : "nao esta");
            }
            pausar();
            break;
        case 3:
            printf("Pilha dinamica nunca fica cheia (limitada apenas por memoria).\n");
            pausar();
            break;
        case 4: {
            if (!pilhaInicializada) {
                printMensagemColorida(RED, "Inicialize a pilha primeiro.");
                break;
            }
            int valor;
            printf("Valor a empilhar: ");
            if (scanf("%d", &valor) != 1) {
                limparBufferTeclado();
                printMensagemColorida(RED, "Entrada invalida!");
                pausar();
                break;
            }
            limparBufferTeclado();
            if (pilhaIntPush(&pilha, valor)) {
                printMensagemColoridaFormatted(GREEN, "Valor %d empilhado.", valor);
            } else {
                printMensagemColorida(RED, "Falha ao empilhar valor.");
            }
            pausar();
            break;
        }
        case 5: {
            if (!pilhaInicializada) {
                printMensagemColorida(RED, "Inicialize a pilha primeiro.");
                pausar();
                break;
            }
            int valor;
            if (pilhaIntPop(&pilha, &valor)) {
                printMensagemColoridaFormatted(GREEN, "Valor %d removido do topo.", valor);
            } else {
                printMensagemColorida(RED, "Pilha vazia, nada a remover.");
            }
            pausar();
            break;
        }
        case 6: {
            if (!pilhaInicializada) {
                printMensagemColorida(RED, "Inicialize a pilha primeiro.");
                pausar();
                break;
            }
            int topo;
            if (pilhaIntTopo(&pilha, &topo)) {
                printf("Topo da pilha: %d\n", topo);
            } else {
                printf("Pilha vazia.\n");
            }
            pausar();
            break;
        }
        case 7: {
            int numero;
            printf("Digite o numero decimal: ");
            if (scanf("%d", &numero) != 1) {
                limparBufferTeclado();
                printMensagemColorida(RED, "Entrada invalida!");
                pausar();
                break;
            }
            limparBufferTeclado();
            printf("Representacao binaria: ");
            converterDecimalParaBinario(numero);
            pausar();
            break;
        }
        case 0:
            pausar();
            break;
        default:
            printMensagemColorida(RED, "Opcao invalida!");
            pausar();
            break;
        }
    }

    pilhaIntLiberar(&pilha);
}

static void demonstracaoPredefinida(void) {
    PilhaInt pilha;
    pilhaIntInicializar(&pilha);

    printMensagemColorida(GREEN, "Inicializando pilha e empilhando 3 valores...");
    pilhaIntPush(&pilha, 10);
    pilhaIntPush(&pilha, 20);
    pilhaIntPush(&pilha, 30);
    pilhaIntImprimir(&pilha);

    int topo;
    if (pilhaIntTopo(&pilha, &topo)) {
        printf("Topo atual: %d\n", topo);
    }

    int removido;
    pilhaIntPop(&pilha, &removido);
    printf("\nDesempilhando um valor (%d) e mostrando pilha:\n", removido);
    pilhaIntImprimir(&pilha);

    printf("\nConvertendo 42 para binario usando pilha auxiliar:\n");
    converterDecimalParaBinario(42);

    pilhaIntLiberar(&pilha);
    pausar();
}

static void cabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Pilha Dinamica - Questao 09 ===");
    printf("\n");
}

void executarQuestaoPilhaDinamica9(void) {
    executarQuestaoPilhaDinamica9Predefinido();
}

void executarQuestaoPilhaDinamica9Predefinido(void) {
    cabecalho();
    demonstracaoPredefinida();
}

void executarQuestaoPilhaDinamica9EntradaManual(void) {
    cabecalho();
    menuInterativo();
    pausar();
}
