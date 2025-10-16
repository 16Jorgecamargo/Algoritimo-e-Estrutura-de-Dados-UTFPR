#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

typedef struct {
    int matricula;
    char nome[64];
    float nota;
} Aluno;

typedef struct NoDuploAluno {
    Aluno dado;
    struct NoDuploAluno* ant;
    struct NoDuploAluno* prox;
} NoDuploAluno;

typedef struct {
    NoDuploAluno* inicio;
    NoDuploAluno* fim;
} ListaDuplaAluno;

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Listas Duplamente Encadeadas - Questao 02 ===");
    printf("\n");
}

static void inicializarLista(ListaDuplaAluno* lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

static NoDuploAluno* criarNoAluno(int matricula, const char* nome, float nota) {
    NoDuploAluno* novo = (NoDuploAluno*)malloc(sizeof(NoDuploAluno));
    if (!novo) {
        return NULL;
    }
    novo->dado.matricula = matricula;
    novo->dado.nota = nota;
    strncpy(novo->dado.nome, nome, sizeof(novo->dado.nome) - 1);
    novo->dado.nome[sizeof(novo->dado.nome) - 1] = '\0';
    novo->ant = NULL;
    novo->prox = NULL;
    return novo;
}

static bool inserirOrdenado(ListaDuplaAluno* lista, int matricula, const char* nome, float nota) {
    NoDuploAluno* novo = criarNoAluno(matricula, nome, nota);
    if (!novo) {
        return false;
    }

    if (lista->inicio == NULL) {
        lista->inicio = novo;
        lista->fim = novo;
        return true;
    }

    NoDuploAluno* atual = lista->inicio;
    while (atual && atual->dado.matricula < matricula) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        novo->ant = lista->fim;
        lista->fim->prox = novo;
        lista->fim = novo;
        return true;
    }

    novo->prox = atual;
    novo->ant = atual->ant;

    if (atual->ant) {
        atual->ant->prox = novo;
    } else {
        lista->inicio = novo;
    }
    atual->ant = novo;
    return true;
}

static void imprimirLista(const ListaDuplaAluno* lista) {
    printMensagemColoridaInline(CYAN, "Lista ordenada: ");
    printf("[ ");
    for (NoDuploAluno* atual = lista->inicio; atual; atual = atual->prox) {
        printf("{mat:%d, nome:%s, nota:%.1f}", atual->dado.matricula, atual->dado.nome, atual->dado.nota);
        if (atual->prox) {
            printf(" <-> ");
        }
    }
    printf(" ]\n");
}

static void liberarLista(ListaDuplaAluno* lista) {
    NoDuploAluno* atual = lista->inicio;
    while (atual) {
        NoDuploAluno* proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    lista->inicio = NULL;
    lista->fim = NULL;
}

static bool preencherListaOrdenadaManual(ListaDuplaAluno* lista, int quantidade) {
    char nome[64];
    int matricula;
    float nota;

    for (int i = 0; i < quantidade; i++) {
        printMensagemColoridaInline(YELLOW, "\nAluno ");
        printf("%d - matricula: ", i + 1);
        if (scanf("%d", &matricula) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "Entrada invalida. Abortando preenchimento.");
            return false;
        }
        limparBufferTeclado();

        printMensagemColoridaInline(YELLOW, "Aluno ");
        printf("%d - nome: ", i + 1);
        if (!fgets(nome, (int)sizeof(nome), stdin)) {
            printMensagemColoridaFormatted(RED, "Falha ao ler o nome. Abortando preenchimento.");
            return false;
        }
        nome[strcspn(nome, "\n")] = '\0';

        printMensagemColoridaInline(YELLOW, "Aluno ");
        printf("%d - nota N1: ", i + 1);
        if (scanf("%f", &nota) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "Entrada invalida. Abortando preenchimento.");
            return false;
        }
        limparBufferTeclado();

        if (!inserirOrdenado(lista, matricula, nome, nota)) {
            printMensagemColoridaFormatted(RED, "Falha ao inserir aluno de forma ordenada.");
            return false;
        }
    }
    return true;
}

void executarQuestaoListasDuplamenteEncadeadas2(void) {
    executarQuestaoListasDuplamenteEncadeadas2Predefinido();
}

void executarQuestaoListasDuplamenteEncadeadas2Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: insercao ordenada por matricula.");
    printf("\n");

    ListaDuplaAluno lista;
    inicializarLista(&lista);

    inserirOrdenado(&lista, 2023004, "Bruno Dias", 82.5f);
    inserirOrdenado(&lista, 2023001, "Ana Lima", 75.0f);
    inserirOrdenado(&lista, 2023010, "Diego Martins", 68.5f);
    inserirOrdenado(&lista, 2023007, "Carla Souza", 91.0f);

    printMensagemColoridaFormatted(CYAN, "Lista apos insercoes ordenadas iniciais:");
    imprimirLista(&lista);

    inserirOrdenado(&lista, 2023006, "Eduarda Silva", 88.0f);
    printMensagemColoridaFormatted(GREEN, "\nNovo aluno com matricula 2023006 inserido mantendo a ordem.");

    printMensagemColoridaFormatted(CYAN, "Lista final ordenada:");
    imprimirLista(&lista);

    liberarLista(&lista);
    pausar();
}

void executarQuestaoListasDuplamenteEncadeadas2EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: construa a lista via insercao ordenada.");
    printf("\n");

    int quantidade;
    printMensagemColoridaInline(YELLOW, "Informe quantos alunos deseja cadastrar inicialmente (0 a 20): ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (quantidade < 0 || quantidade > 20) {
        printMensagemColoridaFormatted(RED, "Quantidade fora do intervalo permitido.");
        pausar();
        return;
    }

    ListaDuplaAluno lista;
    inicializarLista(&lista);

    if (!preencherListaOrdenadaManual(&lista, quantidade)) {
        liberarLista(&lista);
        pausar();
        return;
    }

    printf("\n");
    printMensagemColoridaFormatted(CYAN, "Lista atual (ordenada):");
    imprimirLista(&lista);

    int matricula;
    float nota;
    char nome[64];

    printMensagemColoridaInline(YELLOW, "\nInforme a matricula do novo aluno: ");
    if (scanf("%d", &matricula) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        liberarLista(&lista);
        pausar();
        return;
    }
    limparBufferTeclado();

    printMensagemColoridaInline(YELLOW, "Informe o nome do novo aluno: ");
    if (!fgets(nome, (int)sizeof(nome), stdin)) {
        printMensagemColoridaFormatted(RED, "Falha ao ler o nome.");
        liberarLista(&lista);
        pausar();
        return;
    }
    nome[strcspn(nome, "\n")] = '\0';

    printMensagemColoridaInline(YELLOW, "Informe a nota N1: ");
    if (scanf("%f", &nota) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        liberarLista(&lista);
        pausar();
        return;
    }
    limparBufferTeclado();

    printf("\n");
    if (inserirOrdenado(&lista, matricula, nome, nota)) {
        printMensagemColoridaFormatted(GREEN, "Aluno inserido mantendo a ordem crescente de matricula.");
    } else {
        printMensagemColoridaFormatted(RED, "Nao foi possivel inserir o aluno.");
    }

    printMensagemColoridaFormatted(CYAN, "Lista final:");
    imprimirLista(&lista);

    liberarLista(&lista);
    pausar();
}
