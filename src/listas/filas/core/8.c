#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "fila_circular.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

static void imprimirFila(const FilaCircular *fila, const char *nome) {
    printMensagemColoridaInline(CYAN, nome);
    printf(": ");
    if (!fila->dados) {
        printf("[nao inicializada]\n");
        return;
    }
    if (filaCircularVazia(fila)) {
        printf("[ ] (vazia)\n");
        return;
    }

    printf("[ ");
    for (int i = 0; i < fila->tamanho; i++) {
        int indice = (fila->inicio + i) % fila->capacidade;
        printf("%.2f", fila->dados[indice]);
        if (i < fila->tamanho - 1) {
            printf(", ");
        }
    }
    printf(" ]\n");
}

static void demonstrarMenuAutomatico(void) {
    printMensagemColoridaFormatted(YELLOW, "=== Filas - Questao 08 ===");
    printf("\nExecucao automatica das principais operacoes.\n\n");

    FilaCircular filaA = {0};
    FilaCircular filaB = {0};

    filaCircularInicializar(&filaA, 5);
    filaCircularInicializar(&filaB, 4);

    filaCircularEnfileirar(&filaA, 1.5f);
    filaCircularEnfileirar(&filaA, 2.0f);
    filaCircularEnfileirar(&filaB, 10.0f);

    imprimirFila(&filaA, "Fila A inicial");
    imprimirFila(&filaB, "Fila B inicial");
    printf("\n");

    printMensagemColoridaFormatted(CYAN, "Verificando estado da fila A:\n");
    printf("  Vazia? %s\n", filaCircularVazia(&filaA) ? "Sim" : "Nao");
    printf("  Cheia? %s\n\n", filaCircularCheia(&filaA) ? "Sim" : "Nao");

    printMensagemColoridaFormatted(CYAN, "Aplicando FuraFila em A com valor 99.0:\n");
    filaCircularFuraFila(&filaA, 99.0f);
    imprimirFila(&filaA, "Fila A apos FuraFila");
    printf("\n");

    float primeiro = 0.0f;
    if (filaCircularPrimeiro(&filaA, &primeiro)) {
        printMensagemColoridaFormatted(GREEN, "Primeiro elemento da fila A: %.2f\n\n", primeiro);
    }

    printMensagemColoridaFormatted(CYAN, "Comparando tamanhos:\n");
    if (filaA.tamanho > filaB.tamanho) {
        printf("  Fila A possui mais elementos (%d > %d).\n\n", filaA.tamanho, filaB.tamanho);
    } else if (filaB.tamanho > filaA.tamanho) {
        printf("  Fila B possui mais elementos (%d > %d).\n\n", filaB.tamanho, filaA.tamanho);
    } else {
        printf("  Ambas possuem a mesma quantidade (%d).\n\n", filaA.tamanho);
    }

    float removido = 0.0f;
    if (filaCircularDesenfileirar(&filaA, &removido)) {
        printMensagemColoridaFormatted(GREEN, "Desenfileirando A: %.2f removido.\n", removido);
    }
    imprimirFila(&filaA, "Fila A apos desenfileirar");

    filaCircularLiberar(&filaA);
    filaCircularLiberar(&filaB);
    pausar();
}

static FilaCircular *selecionarFila(FilaCircular *filaA, FilaCircular *filaB) {
    printMensagemColoridaInline(GREEN, "Selecione a fila (A/B)");
    printf(": ");
    char escolha = 'A';
    if (scanf(" %c", &escolha) != 1) {
        limparBufferTeclado();
        return NULL;
    }
    limparBufferTeclado();

    if (escolha == 'A' || escolha == 'a') {
        return filaA;
    }
    if (escolha == 'B' || escolha == 'b') {
        return filaB;
    }
    return NULL;
}

static void inicializarFilaInterativa(FilaCircular *fila) {
    int capacidade = 0;
    printMensagemColoridaInline(GREEN, "Capacidade desejada (1 a 30)");
    printf(": ");
    if (scanf("%d", &capacidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida.\n");
        return;
    }
    limparBufferTeclado();

    if (capacidade < 1 || capacidade > 30) {
        printMensagemColoridaFormatted(RED, "\nCapacidade fora da faixa permitida.\n");
        return;
    }

    filaCircularLiberar(fila);
    if (!filaCircularInicializar(fila, capacidade)) {
        printMensagemColoridaFormatted(RED, "\nFalha ao alocar fila.\n");
    } else {
        printMensagemColoridaFormatted(GREEN, "\nFila inicializada com capacidade %d.\n", capacidade);
    }
}

static void enfileirarValor(FilaCircular *fila) {
    if (!fila->dados) {
        printMensagemColoridaFormatted(RED, "\nFila nao inicializada.\n");
        return;
    }
    if (filaCircularCheia(fila)) {
        printMensagemColoridaFormatted(RED, "\nFila cheia.\n");
        return;
    }

    float valor = 0.0f;
    printMensagemColoridaInline(GREEN, "Valor (float)");
    printf(": ");
    if (scanf("%f", &valor) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida.\n");
        return;
    }
    limparBufferTeclado();

    filaCircularEnfileirar(fila, valor);
    printMensagemColoridaFormatted(GREEN, "\nValor inserido no final da fila.\n");
}

static void desenfileirarValor(FilaCircular *fila) {
    if (!fila->dados) {
        printMensagemColoridaFormatted(RED, "\nFila nao inicializada.\n");
        return;
    }
    float valor = 0.0f;
    if (!filaCircularDesenfileirar(fila, &valor)) {
        printMensagemColoridaFormatted(YELLOW, "\nFila vazia.\n");
        return;
    }
    printMensagemColoridaFormatted(GREEN, "\nValor removido: %.2f\n", valor);
}

static void mostrarPrimeiro(const FilaCircular *fila) {
    if (!fila->dados) {
        printMensagemColoridaFormatted(RED, "\nFila nao inicializada.\n");
        return;
    }
    float valor = 0.0f;
    if (!filaCircularPrimeiro(fila, &valor)) {
        printMensagemColoridaFormatted(YELLOW, "\nFila vazia.\n");
        return;
    }
    printMensagemColoridaFormatted(CYAN, "\nPrimeiro elemento: %.2f\n", valor);
}

static void furarFila(FilaCircular *fila) {
    if (!fila->dados) {
        printMensagemColoridaFormatted(RED, "\nFila nao inicializada.\n");
        return;
    }
    if (filaCircularCheia(fila)) {
        printMensagemColoridaFormatted(RED, "\nFila cheia. Nao ha espaco para furar.\n");
        return;
    }

    float valor = 0.0f;
    printMensagemColoridaInline(GREEN, "Valor para inserir no inicio");
    printf(": ");
    if (scanf("%f", &valor) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida.\n");
        return;
    }
    limparBufferTeclado();

    filaCircularFuraFila(fila, valor);
    printMensagemColoridaFormatted(GREEN, "\nValor inserido no inicio da fila.\n");
}

static void finalizarFilas(FilaCircular *filaA, FilaCircular *filaB) {
    filaCircularLiberar(filaA);
    filaCircularLiberar(filaB);
}

static void menuInterativo(void) {
    FilaCircular filaA = {0};
    FilaCircular filaB = {0};

    int opcao = -1;
    do {
        limparTela();
        printMensagemColoridaFormatted(YELLOW, "=== Filas - Questao 08 (Valores informados) ===");
        printf("\n");
        printf("Fila A: %s | tamanho: %d | capacidade: %d\n",
               filaA.dados ? (filaCircularVazia(&filaA) ? "vazia" : "ocupada") : "nao inicializada",
               filaA.tamanho,
               filaA.capacidade);
        printf("Fila B: %s | tamanho: %d | capacidade: %d\n\n",
               filaB.dados ? (filaCircularVazia(&filaB) ? "vazia" : "ocupada") : "nao inicializada",
               filaB.tamanho,
               filaB.capacidade);

        imprimirFila(&filaA, "Conteudo da fila A");
        imprimirFila(&filaB, "Conteudo da fila B");
        printf("\n");

        printf("1 - Inicializa fila\n");
        printf("2 - Verifica se a fila e vazia\n");
        printf("3 - Verifica se a fila e cheia\n");
        printf("4 - Enfileira elemento\n");
        printf("5 - Desenfileira elemento\n");
        printf("6 - Consulta o primeiro elemento\n");
        printf("7 - Compara quantidade de elementos das filas\n");
        printf("8 - Fura a fila\n");
        printf("9 - Sair\n\n");

        printMensagemColoridaInline(GREEN, "Opcao");
        printf(": ");
        if (scanf("%d", &opcao) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "\nEntrada invalida.\n");
            pausar();
            opcao = -1;
            continue;
        }
        limparBufferTeclado();

        switch (opcao) {
            case 1: {
                FilaCircular *fila = selecionarFila(&filaA, &filaB);
                if (!fila) {
                    printMensagemColoridaFormatted(RED, "\nFila desconhecida.\n");
                } else {
                    inicializarFilaInterativa(fila);
                }
                break;
            }
            case 2: {
                FilaCircular *fila = selecionarFila(&filaA, &filaB);
                if (!fila) {
                    printMensagemColoridaFormatted(RED, "\nFila desconhecida.\n");
                } else if (!fila->dados) {
                    printMensagemColoridaFormatted(RED, "\nFila nao inicializada.\n");
                } else {
                    printMensagemColoridaFormatted(CYAN,
                        "\nFila %s vazia: %s\n",
                        (fila == &filaA) ? "A" : "B",
                        filaCircularVazia(fila) ? "Sim" : "Nao");
                }
                break;
            }
            case 3: {
                FilaCircular *fila = selecionarFila(&filaA, &filaB);
                if (!fila) {
                    printMensagemColoridaFormatted(RED, "\nFila desconhecida.\n");
                } else if (!fila->dados) {
                    printMensagemColoridaFormatted(RED, "\nFila nao inicializada.\n");
                } else {
                    printMensagemColoridaFormatted(CYAN,
                        "\nFila %s cheia: %s\n",
                        (fila == &filaA) ? "A" : "B",
                        filaCircularCheia(fila) ? "Sim" : "Nao");
                }
                break;
            }
            case 4: {
                FilaCircular *fila = selecionarFila(&filaA, &filaB);
                if (!fila) {
                    printMensagemColoridaFormatted(RED, "\nFila desconhecida.\n");
                } else {
                    enfileirarValor(fila);
                }
                break;
            }
            case 5: {
                FilaCircular *fila = selecionarFila(&filaA, &filaB);
                if (!fila) {
                    printMensagemColoridaFormatted(RED, "\nFila desconhecida.\n");
                } else {
                    desenfileirarValor(fila);
                }
                break;
            }
            case 6: {
                FilaCircular *fila = selecionarFila(&filaA, &filaB);
                if (!fila) {
                    printMensagemColoridaFormatted(RED, "\nFila desconhecida.\n");
                } else {
                    mostrarPrimeiro(fila);
                }
                break;
            }
            case 7: {
                int tamanhoA = filaA.dados ? filaA.tamanho : 0;
                int tamanhoB = filaB.dados ? filaB.tamanho : 0;
                if (tamanhoA > tamanhoB) {
                    printMensagemColoridaFormatted(GREEN,
                        "\nFila A possui mais elementos (%d > %d).\n",
                        tamanhoA, tamanhoB);
                } else if (tamanhoB > tamanhoA) {
                    printMensagemColoridaFormatted(GREEN,
                        "\nFila B possui mais elementos (%d > %d).\n",
                        tamanhoB, tamanhoA);
                } else {
                    printMensagemColoridaFormatted(CYAN,
                        "\nAs filas possuem a mesma quantidade (%d).\n",
                        tamanhoA);
                }
                break;
            }
            case 8: {
                FilaCircular *fila = selecionarFila(&filaA, &filaB);
                if (!fila) {
                    printMensagemColoridaFormatted(RED, "\nFila desconhecida.\n");
                } else {
                    furarFila(fila);
                }
                break;
            }
            case 9:
                printMensagemColoridaFormatted(GREEN, "\nEncerrando menu interativo.\n");
                break;
            default:
                printMensagemColoridaFormatted(RED, "\nOpcao invalida.\n");
                break;
        }

        if (opcao != 9) {
            printf("\n");
            pausar();
        }
    } while (opcao != 9);

    finalizarFilas(&filaA, &filaB);
}

void executarQuestaoFilas8Predefinido(void) {
    limparTela();
    demonstrarMenuAutomatico();
}

void executarQuestaoFilas8EntradaManual(void) {
    menuInterativo();
    pausar();
}

void executarQuestaoFilas8(void) {
    executarQuestaoFilas8Predefinido();
}
