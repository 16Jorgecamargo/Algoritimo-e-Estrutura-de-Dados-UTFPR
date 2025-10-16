#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

typedef struct FilaNo {
    int info;
    struct FilaNo* prox;
    struct FilaNo* ant;
} FilaNo;

typedef struct nodesc {
    FilaNo* ini;
    FilaNo* fim;
} *NoDesc;

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Listas Duplamente Encadeadas - Questao 05 ===");
    printf("\n");
}

static int inicializa_noDesc(NoDesc* no) {
    *no = (NoDesc)malloc(sizeof(struct nodesc));
    if (!(*no)) {
        return 0;
    }
    (*no)->ini = NULL;
    (*no)->fim = NULL;
    return 1;
}

static int enfileirar(NoDesc* desc, int elem) {
    if (!desc || !*desc) {
        return 0;
    }

    FilaNo* novo = (FilaNo*)malloc(sizeof(FilaNo));
    if (!novo) {
        return 0;
    }

    novo->info = elem;
    novo->prox = NULL;
    novo->ant = (*desc)->fim;

    if ((*desc)->fim) {
        (*desc)->fim->prox = novo;
    } else {
        (*desc)->ini = novo;
    }

    (*desc)->fim = novo;
    return 1;
}

static int desenfileirar(NoDesc* desc, int* elem) {
    if (!desc || !*desc || !(*desc)->ini) {
        return 0;
    }

    FilaNo* primeiro = (*desc)->ini;
    if (elem) {
        *elem = primeiro->info;
    }

    (*desc)->ini = primeiro->prox;
    if ((*desc)->ini) {
        (*desc)->ini->ant = NULL;
    } else {
        (*desc)->fim = NULL;
    }

    free(primeiro);
    return 1;
}

static void imprimirFila(NoDesc desc) {
    printMensagemColoridaInline(CYAN, "Fila (ini -> fim): ");
    printf("[ ");
    for (FilaNo* atual = desc ? desc->ini : NULL; atual; atual = atual->prox) {
        printf("%d", atual->info);
        if (atual->prox) {
            printf(" | ");
        }
    }
    printf(" ]\n");
}

static void liberarFila(NoDesc* desc) {
    if (!desc || !*desc) {
        return;
    }

    FilaNo* atual = (*desc)->ini;
    while (atual) {
        FilaNo* proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    free(*desc);
    *desc = NULL;
}

void executarQuestaoListasDuplamenteEncadeadas5(void) {
    executarQuestaoListasDuplamenteEncadeadas5Predefinido();
}

void executarQuestaoListasDuplamenteEncadeadas5Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: fila com no descritor baseada em lista duplamente encadeada.");
    printf("\n");

    NoDesc descritor = NULL;
    if (!inicializa_noDesc(&descritor)) {
        printMensagemColoridaFormatted(RED, "Falha ao inicializar o no descritor.");
        pausar();
        return;
    }

    enfileirar(&descritor, 10);
    enfileirar(&descritor, 20);
    enfileirar(&descritor, 30);
    printMensagemColoridaFormatted(CYAN, "Fila apos enfileirar 10, 20 e 30:");
    imprimirFila(descritor);

    int removido;
    if (desenfileirar(&descritor, &removido)) {
        printMensagemColoridaFormatted(GREEN, "Desenfileirado: %d", removido);
    }
    if (desenfileirar(&descritor, &removido)) {
        printMensagemColoridaFormatted(GREEN, "Desenfileirado: %d", removido);
    }

    printMensagemColoridaFormatted(CYAN, "Fila restante:");
    imprimirFila(descritor);

    enfileirar(&descritor, 40);
    printMensagemColoridaFormatted(CYAN, "Fila apos enfileirar 40:");
    imprimirFila(descritor);

    liberarFila(&descritor);
    pausar();
}

void executarQuestaoListasDuplamenteEncadeadas5EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: manipule uma fila utilizando no descritor.");
    printf("\n");

    NoDesc descritor = NULL;
    if (!inicializa_noDesc(&descritor)) {
        printMensagemColoridaFormatted(RED, "Falha ao inicializar o no descritor.");
        pausar();
        return;
    }

    int quantidade;
    printMensagemColoridaInline(YELLOW, "Quantidade inicial de elementos para enfileirar (0 a 20): ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        liberarFila(&descritor);
        pausar();
        return;
    }
    limparBufferTeclado();

    if (quantidade < 0 || quantidade > 20) {
        printMensagemColoridaFormatted(RED, "Quantidade fora do intervalo permitido.");
        liberarFila(&descritor);
        pausar();
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        int valor;
        printMensagemColoridaInline(YELLOW, "Valor ");
        printf("%d: ", i + 1);
        if (scanf("%d", &valor) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "Entrada invalida. Abortando preenchimento.");
            liberarFila(&descritor);
            pausar();
            return;
        }
        limparBufferTeclado();

        if (!enfileirar(&descritor, valor)) {
            printMensagemColoridaFormatted(RED, "Falha ao enfileirar o valor informado.");
            liberarFila(&descritor);
            pausar();
            return;
        }
    }

    printf("\n");
    imprimirFila(descritor);

    int opcao = 0;
    do {
        printMensagemColoridaFormatted(CYAN, "\nEscolha uma operacao:");
        printMensagemColoridaFormatted(CYAN, "1 - Enfileirar novo elemento");
        printMensagemColoridaFormatted(CYAN, "2 - Desenfileirar elemento");
        printMensagemColoridaFormatted(CYAN, "0 - Encerrar");
        printMensagemColoridaInline(YELLOW, "Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "Entrada invalida. Encerrando interacao.");
            break;
        }
        limparBufferTeclado();

        if (opcao == 1) {
            int valor;
            printMensagemColoridaInline(YELLOW, "Valor para enfileirar: ");
            if (scanf("%d", &valor) != 1) {
                limparBufferTeclado();
                printMensagemColoridaFormatted(RED, "Entrada invalida.");
            } else {
                limparBufferTeclado();
                if (enfileirar(&descritor, valor)) {
                    printMensagemColoridaFormatted(GREEN, "Elemento %d inserido no fim da fila.", valor);
                } else {
                    printMensagemColoridaFormatted(RED, "Falha ao enfileirar.");
                }
            }
        } else if (opcao == 2) {
            int valor;
            if (desenfileirar(&descritor, &valor)) {
                printMensagemColoridaFormatted(GREEN, "Elemento removido da frente: %d", valor);
            } else {
                printMensagemColoridaFormatted(RED, "Fila vazia - nada a remover.");
            }
        }

        if (opcao == 1 || opcao == 2) {
            imprimirFila(descritor);
        }
    } while (opcao != 0);

    liberarFila(&descritor);
    pausar();
}
