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
} Aluno;

typedef struct NoAluno {
    Aluno dado;
    struct NoAluno* proximo;
} NoAluno;

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Listas - Questao 01 ===");
    printf("\n");
}

static NoAluno* criarNoAluno(int matricula, const char* nome) {
    NoAluno* novo = (NoAluno*)malloc(sizeof(NoAluno));
    if (!novo) {
        return NULL;
    }
    novo->dado.matricula = matricula;
    strncpy(novo->dado.nome, nome, sizeof(novo->dado.nome) - 1);
    novo->dado.nome[sizeof(novo->dado.nome) - 1] = '\0';
    novo->proximo = NULL;
    return novo;
}

static bool inserirAlunoFim(NoAluno** inicio, int matricula, const char* nome) {
    NoAluno* novo = criarNoAluno(matricula, nome);
    if (!novo) {
        return false;
    }
    if (*inicio == NULL) {
        *inicio = novo;
        return true;
    }

    NoAluno* atual = *inicio;
    while (atual->proximo) {
        atual = atual->proximo;
    }
    atual->proximo = novo;
    return true;
}

static void liberarListaAlunos(NoAluno** inicio) {
    NoAluno* atual = *inicio;
    while (atual) {
        NoAluno* temp = atual->proximo;
        free(atual);
        atual = temp;
    }
    *inicio = NULL;
}

static NoAluno* buscarPorMatricula(NoAluno* inicio, int matricula) {
    for (NoAluno* atual = inicio; atual; atual = atual->proximo) {
        if (atual->dado.matricula == matricula) {
            return atual;
        }
    }
    return NULL;
}

static NoAluno* buscarPorPosicao(NoAluno* inicio, int posicao) {
    if (posicao < 1) {
        return NULL;
    }
    int contador = 1;
    for (NoAluno* atual = inicio; atual; atual = atual->proximo, contador++) {
        if (contador == posicao) {
            return atual;
        }
    }
    return NULL;
}

static void imprimirLista(NoAluno* inicio) {
    printf("[ ");
    for (NoAluno* atual = inicio; atual; atual = atual->proximo) {
        printf("{mat:%d, nome:%s}", atual->dado.matricula, atual->dado.nome);
        if (atual->proximo) {
            printf(" -> ");
        }
    }
    printf(" ]\n");
}

static void demonstrarBuscas(NoAluno* lista, int matricula, int posicao) {
    printMensagemColoridaFormatted(CYAN, "Lista cadastrada:");
    imprimirLista(lista);
    printf("\n");

    printMensagemColoridaFormatted(CYAN, "Buscando matricula %d:", matricula);
    NoAluno* porMatricula = buscarPorMatricula(lista, matricula);
    if (porMatricula) {
        printMensagemColoridaFormatted(GREEN, "Aluno encontrado: %s (matricula %d)", porMatricula->dado.nome, porMatricula->dado.matricula);
    } else {
        printMensagemColoridaFormatted(RED, "Nenhum aluno com matricula %d foi encontrado.", matricula);
    }
    printf("\n");

    printMensagemColoridaFormatted(CYAN, "Buscando posicao %d:", posicao);
    NoAluno* porPosicao = buscarPorPosicao(lista, posicao);
    if (porPosicao) {
        printMensagemColoridaFormatted(GREEN, "Aluno na posicao %d: %s (matricula %d)", posicao, porPosicao->dado.nome, porPosicao->dado.matricula);
    } else {
        printMensagemColoridaFormatted(RED, "Posicao %d invalida para a lista atual.", posicao);
    }
}

void executarQuestaoListas1(void) {
    executarQuestaoListas1Predefinido();
}

void executarQuestaoListas1Predefinido(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo predefinido: lista com 4 alunos.");
    printf("\n");

    NoAluno* lista = NULL;

    if (!inserirAlunoFim(&lista, 2023001, "Ana Lima")
        || !inserirAlunoFim(&lista, 2023002, "Bruno Alves")
        || !inserirAlunoFim(&lista, 2023003, "Carla Souza")
        || !inserirAlunoFim(&lista, 2023010, "Diego Martins")) {
        printMensagemColoridaFormatted(RED, "Falha ao montar a lista de alunos. Encerrando demonstracao.");
        liberarListaAlunos(&lista);
        pausar();
        return;
    }

    demonstrarBuscas(lista, 2023003, 2);

    liberarListaAlunos(&lista);
    pausar();
}

void executarQuestaoListas1EntradaManual(void) {
    imprimirCabecalho();
    printMensagemColoridaFormatted(CYAN, "Fluxo manual: cadastre e consulte alunos por matricula e posicao.");
    printf("\n");

    int quantidade;
    printMensagemColoridaInline(YELLOW, "Informe a quantidade de alunos (1 a 20): ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida. Abortando fluxo manual.");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (quantidade < 1 || quantidade > 20) {
        printMensagemColoridaFormatted(RED, "Quantidade fora do intervalo permitido.");
        pausar();
        return;
    }

    NoAluno* lista = NULL;
    char nome[64];
    int matricula;

    for (int i = 0; i < quantidade; i++) {
        printf("\n");
        printMensagemColoridaInline(YELLOW, "Aluno ");
        printf("%d - matricula: ", i + 1);
        if (scanf("%d", &matricula) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "Entrada invalida. Encerrando fluxo manual.");
            liberarListaAlunos(&lista);
            pausar();
            return;
        }
        limparBufferTeclado();

        printMensagemColoridaInline(YELLOW, "Aluno ");
        printf("%d - nome: ", i + 1);
        if (!fgets(nome, (int)sizeof(nome), stdin)) {
            printMensagemColoridaFormatted(RED, "Falha ao ler o nome. Encerrando fluxo manual.");
            liberarListaAlunos(&lista);
            pausar();
            return;
        }
        nome[strcspn(nome, "\n")] = '\0';

        if (!inserirAlunoFim(&lista, matricula, nome)) {
            printMensagemColoridaFormatted(RED, "Falha ao alocar memoria para o aluno. Encerrando fluxo manual.");
            liberarListaAlunos(&lista);
            pausar();
            return;
        }
    }

    printf("\n");
    printMensagemColoridaFormatted(CYAN, "Lista final cadastrada:");
    imprimirLista(lista);
    printf("\n");

    printMensagemColoridaInline(YELLOW, "Informe a matricula que deseja localizar: ");
    if (scanf("%d", &matricula) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida. Abortando consulta.");
        liberarListaAlunos(&lista);
        pausar();
        return;
    }
    limparBufferTeclado();

    printMensagemColoridaInline(YELLOW, "Informe a posicao desejada ");
    printf("(1 a %d): ", quantidade);
    int posicao;
    if (scanf("%d", &posicao) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "Entrada invalida. Abortando consulta.");
        liberarListaAlunos(&lista);
        pausar();
        return;
    }
    limparBufferTeclado();

    printf("\n");
    demonstrarBuscas(lista, matricula, posicao);

    liberarListaAlunos(&lista);
    pausar();
}
