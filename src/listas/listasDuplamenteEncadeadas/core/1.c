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
    printMensagemColoridaFormatted(YELLOW, "=== Listas Duplamente Encadeadas - Questao 01 ===");
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

static bool inserirAlunoFim(ListaDuplaAluno* lista, int matricula, const char* nome, float nota) {
    NoDuploAluno* novo = criarNoAluno(matricula, nome, nota);
    if (!novo) {
        return false;
    }
    if (lista->fim == NULL) {
        lista->inicio = novo;
        lista->fim = novo;
        return true;
    }

    novo->ant = lista->fim;
    lista->fim->prox = novo;
    lista->fim = novo;
    return true;
}

static bool removerPorMatricula(ListaDuplaAluno* lista, int matricula, Aluno* removido) {
    NoDuploAluno* atual = lista->inicio;
    while (atual) {
        if (atual->dado.matricula == matricula) {
            if (removido) {
                *removido = atual->dado;
            }

            if (atual->ant) {
                atual->ant->prox = atual->prox;
            } else {
                lista->inicio = atual->prox;
            }

            if (atual->prox) {
                atual->prox->ant = atual->ant;
            } else {
                lista->fim = atual->ant;
            }

            free(atual);
            return true;
        }
        atual = atual->prox;
    }
    return false;
}

static void imprimirLista(const ListaDuplaAluno* lista) {
    printMensagemColoridaInline(CYAN, "Lista: ");
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

static bool preencherListaManual(ListaDuplaAluno* lista, int quantidade) {
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

        if (!inserirAlunoFim(lista, matricula, nome, nota)) {
            printMensagemColoridaFormatted(RED, "Falha ao alocar memoria para o aluno.");
            return false;
        }
    }
    return true;
}

void executarQuestaoListasDuplamenteEncadeadas1(void) {
    executarQuestaoListasDuplamenteEncadeadas1Predefinido();
}

void executarQuestaoListasDuplamenteEncadeadas1Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: remover aluno por matricula em lista duplamente encadeada.");
    printf("\n");

    ListaDuplaAluno lista;
    inicializarLista(&lista);

    inserirAlunoFim(&lista, 2023001, "Ana Lima", 75.0f);
    inserirAlunoFim(&lista, 2023004, "Bruno Dias", 82.5f);
    inserirAlunoFim(&lista, 2023008, "Carla Souza", 91.0f);
    inserirAlunoFim(&lista, 2023010, "Diego Martins", 68.5f);

    printMensagemColoridaFormatted(CYAN, "Lista original:");
    imprimirLista(&lista);

    Aluno removido;
    bool sucesso = removerPorMatricula(&lista, 2023008, &removido);
    printf("\n");
    if (sucesso) {
        printMensagemColoridaFormatted(GREEN, "Aluno removido: %s (matricula %d).", removido.nome, removido.matricula);
    } else {
        printMensagemColoridaFormatted(RED, "Matricula nao encontrada na lista.");
    }

    printMensagemColoridaFormatted(CYAN, "Lista apos remocao:");
    imprimirLista(&lista);

    liberarLista(&lista);
    pausar();
}

void executarQuestaoListasDuplamenteEncadeadas1EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: cadastre alunos e remova pela matricula informada.");
    printf("\n");

    int quantidade;
    printMensagemColoridaInline(YELLOW, "Informe a quantidade de alunos (1 a 20): ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (quantidade < 1 || quantidade > 20) {
        printMensagemColoridaFormatted(RED, "Quantidade fora do intervalo permitido.");
        pausar();
        return;
    }

    ListaDuplaAluno lista;
    inicializarLista(&lista);

    if (!preencherListaManual(&lista, quantidade)) {
        liberarLista(&lista);
        pausar();
        return;
    }

    printf("\n");
    printMensagemColoridaFormatted(CYAN, "Lista cadastrada:");
    imprimirLista(&lista);

    int matricula;
    printMensagemColoridaInline(YELLOW, "\nInforme a matricula a ser removida: ");
    if (scanf("%d", &matricula) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        liberarLista(&lista);
        pausar();
        return;
    }
    limparBufferTeclado();

    Aluno removido;
    printf("\n");
    if (removerPorMatricula(&lista, matricula, &removido)) {
        printMensagemColoridaFormatted(GREEN, "Aluno %s removido com sucesso.", removido.nome);
    } else {
        printMensagemColoridaFormatted(RED, "Nenhum aluno com matricula %d foi encontrado.", matricula);
    }

    printMensagemColoridaFormatted(CYAN, "Estado final da lista:");
    imprimirLista(&lista);

    liberarLista(&lista);
    pausar();
}
