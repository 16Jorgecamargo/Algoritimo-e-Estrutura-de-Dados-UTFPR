#include <stdio.h>
#include <stdlib.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

typedef struct NoFloat {
    float valor;
    struct NoFloat* proximo;
} NoFloat;

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Listas - Questao 04 ===");
    printf("\n");
}

static NoFloat* criarNo(float valor) {
    NoFloat* novo = (NoFloat*)malloc(sizeof(NoFloat));
    if (!novo) {
        return NULL;
    }
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

static NoFloat* construirListaPorVetor(const float* valores, size_t quantidade) {
    NoFloat* inicio = NULL;
    NoFloat* fim = NULL;

    for (size_t i = 0; i < quantidade; i++) {
        NoFloat* novo = criarNo(valores[i]);
        if (!novo) {
            printMensagemColoridaFormatted(RED, "Falha ao alocar memoria para o no %.2f.", valores[i]);
            // desalocar o que ja foi criado
            NoFloat* atual = inicio;
            while (atual) {
                NoFloat* temp = atual->proximo;
                free(atual);
                atual = temp;
            }
            return NULL;
        }
        if (!inicio) {
            inicio = novo;
            fim = novo;
        } else {
            fim->proximo = novo;
            fim = novo;
        }
    }

    return inicio;
}

static void liberarLista(NoFloat** inicio) {
    NoFloat* atual = *inicio;
    while (atual) {
        NoFloat* temp = atual->proximo;
        free(atual);
        atual = temp;
    }
    *inicio = NULL;
}

static void imprimirLista(const NoFloat* inicio) {
    printf("[ ");
    for (const NoFloat* atual = inicio; atual; atual = atual->proximo) {
        printf("%.2f", atual->valor);
        if (atual->proximo) {
            printf(" -> ");
        }
    }
    printf(" ]\n");
}

static void imprimirArray(const float* valores, size_t quantidade) {
    printf("{ ");
    for (size_t i = 0; i < quantidade; i++) {
        printf("%.2f", valores[i]);
        if (i + 1 < quantidade) {
            printf(", ");
        }
    }
    printf(" }");
}

void executarQuestaoListas4(void) {
    executarQuestaoListas4Predefinido();
}

void executarQuestaoListas4Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: converter vetor em lista preservando a ordem.");
    printf("\n");

    float valores[] = {5.5f, 8.0f, 9.1f, 25.0f};
    size_t quantidade = sizeof(valores) / sizeof(valores[0]);

    printMensagemColoridaInline(CYAN, "Vetor de entrada: ");
    imprimirArray(valores, quantidade);
    printf("\n\n");

    NoFloat* lista = construirListaPorVetor(valores, quantidade);
    if (!lista) {
        printMensagemColoridaFormatted(RED, "Nao foi possivel construir a lista encadeada.");
        pausar();
        return;
    }

    printMensagemColoridaFormatted(GREEN, "Lista encadeada resultante:");
    imprimirLista(lista);

    liberarLista(&lista);
    pausar();
}

void executarQuestaoListas4EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: informe um vetor de floats para gerar a lista.");
    printf("\n");

    int quantidade;
    printMensagemColoridaInline(YELLOW, "Informe a quantidade de elementos do vetor (1 a 30): ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (quantidade < 1 || quantidade > 30) {
        printMensagemColoridaFormatted(RED, "Quantidade fora do intervalo permitido.");
        pausar();
        return;
    }

    float* valores = (float*)malloc((size_t)quantidade * sizeof(float));
    if (!valores) {
        printMensagemColoridaFormatted(RED, "Falha ao alocar memoria para o vetor.");
        pausar();
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        printMensagemColoridaInline(YELLOW, "Valor ");
        printf("%d: ", i + 1);
        if (scanf("%f", &valores[i]) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "Entrada invalida. Abortando fluxo.");
            free(valores);
            pausar();
            return;
        }
        limparBufferTeclado();
    }

    printf("\n");
    printMensagemColoridaInline(CYAN, "Vetor informado: ");
    imprimirArray(valores, (size_t)quantidade);
    printf("\n\n");

    NoFloat* lista = construirListaPorVetor(valores, (size_t)quantidade);
    free(valores);

    if (!lista) {
        printMensagemColoridaFormatted(RED, "Nao foi possivel construir a lista encadeada.");
        pausar();
        return;
    }

    printMensagemColoridaFormatted(GREEN, "Lista encadeada resultante:");
    imprimirLista(lista);

    liberarLista(&lista);
    pausar();
}
