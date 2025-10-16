#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

typedef struct NoAluno {
    int matricula;
    char nome[40];
    struct NoAluno *prox;
} NoAluno;

typedef struct {
    NoAluno *inicio;
    NoAluno *fim;
    size_t tamanho;
} FilaAluno;

static void filaAlunoInicializar(FilaAluno *fila) {
    if (!fila) {
        return;
    }
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

static void filaAlunoLiberar(FilaAluno *fila) {
    if (!fila) {
        return;
    }

    NoAluno *atual = fila->inicio;
    while (atual) {
        NoAluno *prox = atual->prox;
        free(atual);
        atual = prox;
    }

    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

static int filaAlunoEnfileirar(FilaAluno *fila, int matricula, const char *nome) {
    if (!fila) {
        return 0;
    }

    NoAluno *novo = (NoAluno *)malloc(sizeof(NoAluno));
    if (!novo) {
        return 0;
    }

    novo->matricula = matricula;
    strncpy(novo->nome, nome ? nome : "", sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';
    novo->prox = NULL;

    if (fila->fim) {
        fila->fim->prox = novo;
    } else {
        fila->inicio = novo;
    }

    fila->fim = novo;
    fila->tamanho++;
    return 1;
}

static void filaAlunoImprimir(const FilaAluno *fila, const char *titulo) {
    if (titulo) {
        printMensagemColoridaInline(CYAN, titulo);
        printf("\n");
    }

    if (!fila || !fila->inicio) {
        printMensagemColoridaFormatted(YELLOW, "  (fila vazia)\n");
        return;
    }

    const NoAluno *atual = fila->inicio;
    size_t pos = 1;
    while (atual) {
        printf("  %zu) Matricula %d - %s\n", pos, atual->matricula, atual->nome);
        atual = atual->prox;
        pos++;
    }
    printf("\n");
}

static int separaFilaPorMatricula(FilaAluno *original, FilaAluno *dividida, int matriculaCorte) {
    if (!original || !dividida || !original->inicio) {
        return 0;
    }

    NoAluno *atual = original->inicio;
    while (atual && atual->matricula != matriculaCorte) {
        atual = atual->prox;
    }

    if (!atual) {
        return 0;
    }

    NoAluno *inicioNova = atual->prox;
    if (!inicioNova) {
        filaAlunoInicializar(dividida);
        original->fim = atual;
        return 1;
    }

    NoAluno *ultimoNova = inicioNova;
    size_t tamanhoNova = 1;
    while (ultimoNova->prox) {
        ultimoNova = ultimoNova->prox;
        tamanhoNova++;
    }

    dividida->inicio = inicioNova;
    dividida->fim = ultimoNova;
    dividida->tamanho = tamanhoNova;

    atual->prox = NULL;
    original->fim = atual;
    if (original->tamanho >= tamanhoNova) {
        original->tamanho -= tamanhoNova;
    } else {
        original->tamanho = 0;
    }

    return 1;
}

static void executarQuestaoFilas1ComDados(const int *matriculas,
                                          const char nomes[][40],
                                          size_t quantidade,
                                          int matriculaCorte) {
    FilaAluno filaOriginal;
    FilaAluno filaSeparada;
    filaAlunoInicializar(&filaOriginal);
    filaAlunoInicializar(&filaSeparada);

    for (size_t i = 0; i < quantidade; i++) {
        if (!filaAlunoEnfileirar(&filaOriginal, matriculas[i], nomes[i])) {
            printMensagemColoridaFormatted(RED, "Falha ao enfileirar aluno de matricula %d.\n", matriculas[i]);
            filaAlunoLiberar(&filaOriginal);
            filaAlunoLiberar(&filaSeparada);
            pausar();
            return;
        }
    }

    filaAlunoImprimir(&filaOriginal, "Fila original:");

    if (!separaFilaPorMatricula(&filaOriginal, &filaSeparada, matriculaCorte)) {
        printMensagemColoridaFormatted(RED,
            "\nMatricula %d nao encontrada. Nenhuma divisao realizada.\n",
            matriculaCorte);
        filaAlunoLiberar(&filaOriginal);
        filaAlunoLiberar(&filaSeparada);
        pausar();
        return;
    }

    printMensagemColoridaFormatted(GREEN,
        "\nFila dividida apos a primeira ocorrencia da matricula %d.\n\n",
        matriculaCorte);
    filaAlunoImprimir(&filaOriginal, "Primeira fila:");
    filaAlunoImprimir(&filaSeparada, "Segunda fila:");

    filaAlunoLiberar(&filaOriginal);
    filaAlunoLiberar(&filaSeparada);
    pausar();
}

void executarQuestaoFilas1Predefinido(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Filas - Questao 01 ===");
    printf("\nDividir a fila no primeiro ponto apos a matricula informada.\n\n");

    const int matriculas[] = {2023001, 2023002, 2023003, 2023004, 2023005};
    const char nomes[][40] = {"Ana", "Bruno", "Carlos", "Diana", "Eduardo"};

    executarQuestaoFilas1ComDados(matriculas, nomes,
                                  sizeof(matriculas) / sizeof(matriculas[0]),
                                  2023003);
}

void executarQuestaoFilas1EntradaManual(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Filas - Questao 01 (Valores informados) ===");
    printf("\nInforme os alunos em ordem de chegada na fila.\n\n");

    int quantidade = 0;
    printMensagemColoridaInline(GREEN, "Quantos alunos estarao na fila");
    printf(" (1 a 20): ");
    if (scanf("%d", &quantidade) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida.\n");
        pausar();
        return;
    }
    limparBufferTeclado();

    if (quantidade < 1 || quantidade > 20) {
        printMensagemColoridaFormatted(RED, "\nQuantidade fora do intervalo permitido.\n");
        pausar();
        return;
    }

    int *matriculas = (int *)malloc((size_t)quantidade * sizeof(int));
    char (*nomes)[40] = (char (*)[40])calloc((size_t)quantidade, sizeof(*nomes));
    if (!matriculas || !nomes) {
        printMensagemColoridaFormatted(RED, "\nFalha ao alocar memoria.\n");
        free(matriculas);
        free(nomes);
        pausar();
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        printf("\nAluno %d\n", i + 1);
        printMensagemColoridaInline(GREEN, "Matricula");
        printf(": ");
        if (scanf("%d", &matriculas[i]) != 1) {
            limparBufferTeclado();
            printMensagemColoridaFormatted(RED, "\nEntrada invalida.\n");
            free(matriculas);
            free(nomes);
            pausar();
            return;
        }
        limparBufferTeclado();

        printMensagemColoridaInline(GREEN, "Nome");
        printf(": ");
        if (!fgets(nomes[i], (int)sizeof(nomes[i]), stdin)) {
            printMensagemColoridaFormatted(RED, "\nFalha ao ler o nome.\n");
            free(matriculas);
            free(nomes);
            pausar();
            return;
        }
        nomes[i][strcspn(nomes[i], "\n")] = '\0';
    }

    int matriculaCorte = 0;
    printf("\n");
    printMensagemColoridaInline(GREEN, "Matricula que marcara o ponto de corte");
    printf(": ");
    if (scanf("%d", &matriculaCorte) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida.\n");
        free(matriculas);
        free(nomes);
        pausar();
        return;
    }
    limparBufferTeclado();

    executarQuestaoFilas1ComDados(matriculas, nomes, (size_t)quantidade, matriculaCorte);

    free(matriculas);
    free(nomes);
}

void executarQuestaoFilas1(void) {
    executarQuestaoFilas1Predefinido();
}
