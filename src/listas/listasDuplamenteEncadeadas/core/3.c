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
    int nota;
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
    printMensagemColoridaFormatted(YELLOW, "=== Listas Duplamente Encadeadas - Questao 03 ===");
    printf("\n");
}

static void inicializarLista(ListaDuplaAluno* lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

static NoDuploAluno* criarNoAluno(int matricula, const char* nome, int nota) {
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

static bool inserirFim(ListaDuplaAluno* lista, int matricula, const char* nome, int nota) {
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

static void imprimirLista(const ListaDuplaAluno* lista) {
    printMensagemColoridaInline(CYAN, "Lista: ");
    printf("[ ");
    for (NoDuploAluno* atual = lista->inicio; atual; atual = atual->prox) {
        printf("{mat:%d, nome:%s, n1:%d}", atual->dado.matricula, atual->dado.nome, atual->dado.nota);
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

static int contaListaNota(NoDuploAluno** referencia, int notaAlvo) {
    if (!referencia || !*referencia) {
        return 0;
    }

    NoDuploAluno* atual = *referencia;
    int contador = 0;

    while (atual) {
        if (atual->dado.nota == notaAlvo) {
            contador++;
        }

        if (atual->prox == NULL) {
            *referencia = atual;
            break;
        }

        atual = atual->prox;
    }

    while ((*referencia)->ant) {
        *referencia = (*referencia)->ant;
    }

    return contador;
}

static bool preencherListaManual(ListaDuplaAluno* lista, int quantidade) {
    char nome[64];
    int matricula;
    int nota;

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
        printf("%d - nota N1 (inteiro): ", i + 1);
        if (scanf("%d", &nota) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "Entrada invalida. Abortando preenchimento.");
            return false;
        }
        limparBufferTeclado();

        if (!inserirFim(lista, matricula, nome, nota)) {
            printMensagemColoridaFormatted(RED, "Falha ao inserir aluno.");
            return false;
        }
    }
    return true;
}

void executarQuestaoListasDuplamenteEncadeadas3(void) {
    executarQuestaoListasDuplamenteEncadeadas3Predefinido();
}

void executarQuestaoListasDuplamenteEncadeadas3Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: contar alunos com mesma nota N1 utilizando apenas o ponteiro da lista.");
    printf("\n");

    ListaDuplaAluno lista;
    inicializarLista(&lista);

    inserirFim(&lista, 2023001, "Ana Lima", 80);
    inserirFim(&lista, 2023004, "Bruno Dias", 75);
    inserirFim(&lista, 2023007, "Carla Souza", 80);
    inserirFim(&lista, 2023010, "Diego Martins", 68);

    printMensagemColoridaFormatted(CYAN, "Lista original:");
    imprimirLista(&lista);

    NoDuploAluno* ponteiroLista = lista.inicio;
    int valorBusca = 80;
    int quantidade = contaListaNota(&ponteiroLista, valorBusca);

    printf("\n");
    printMensagemColoridaFormatted(GREEN, "Quantidade de alunos com nota %d: %d", valorBusca, quantidade);
    if (ponteiroLista == lista.inicio) {
        printMensagemColoridaFormatted(GREEN, "Ponteiro li reposicionado para a cabeca da lista conforme exigido.");
    } else {
        printMensagemColoridaFormatted(RED, "Atencao: ponteiro li nao voltou para a cabeca.");
    }

    liberarLista(&lista);
    pausar();
}

void executarQuestaoListasDuplamenteEncadeadas3EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: informe alunos e conte quantos possuem uma nota especifica.");
    printf("\n");

    int quantidade;
    printMensagemColoridaInline(YELLOW, "Quantidade de alunos (1 a 25): ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (quantidade < 1 || quantidade > 25) {
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
    printMensagemColoridaFormatted(CYAN, "Lista registrada:");
    imprimirLista(&lista);

    int notaBusca;
    printMensagemColoridaInline(YELLOW, "\nInforme a nota N1 desejada (inteiro): ");
    if (scanf("%d", &notaBusca) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida.");
        liberarLista(&lista);
        pausar();
        return;
    }
    limparBufferTeclado();

    NoDuploAluno* ponteiroLista = lista.inicio;
    int quantidadeEncontrada = contaListaNota(&ponteiroLista, notaBusca);

    printf("\n");
    if (quantidadeEncontrada > 0) {
        printMensagemColoridaFormatted(GREEN, "%d aluno(s) possuem nota %d.", quantidadeEncontrada, notaBusca);
    } else {
        printMensagemColoridaFormatted(RED, "Nenhum aluno possui nota %d.", notaBusca);
    }

    if (ponteiroLista == lista.inicio) {
        printMensagemColoridaFormatted(GREEN, "Verificacao: ponteiro li permanece na cabeca da lista.");
    } else {
        printMensagemColoridaFormatted(RED, "Ponteiro li nao retornou para a cabeca da lista.");
    }

    liberarLista(&lista);
    pausar();
}
