#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

typedef struct {
    int id;
    char companhia[32];
    char destino[32];
} Aviao;

typedef struct NoAviao {
    Aviao dado;
    struct NoAviao *prox;
} NoAviao;

typedef struct {
    NoAviao *inicio;
    NoAviao *fim;
    size_t tamanho;
} FilaAviao;

static void filaAviaoInicializar(FilaAviao *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

static void filaAviaoLiberar(FilaAviao *fila) {
    NoAviao *atual = fila->inicio;
    while (atual) {
        NoAviao *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

static int filaAviaoEnfileirar(FilaAviao *fila, const Aviao *dados) {
    NoAviao *novo = (NoAviao *)malloc(sizeof(NoAviao));
    if (!novo) {
        return 0;
    }
    novo->dado = *dados;
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

static int filaAviaoDesenfileirar(FilaAviao *fila, Aviao *saida) {
    if (!fila->inicio) {
        return 0;
    }
    NoAviao *removido = fila->inicio;
    if (saida) {
        *saida = removido->dado;
    }
    fila->inicio = removido->prox;
    if (!fila->inicio) {
        fila->fim = NULL;
    }
    fila->tamanho--;
    free(removido);
    return 1;
}

static int filaAviaoPrimeiro(const FilaAviao *fila, Aviao *saida) {
    if (!fila->inicio || !saida) {
        return 0;
    }
    *saida = fila->inicio->dado;
    return 1;
}

static void filaAviaoListar(const FilaAviao *fila) {
    if (!fila->inicio) {
        printMensagemColoridaFormatted(YELLOW, "  Nenhum aviao aguardando.\n");
        return;
    }

    const NoAviao *atual = fila->inicio;
    size_t pos = 1;
    while (atual) {
        printf("  %zu) #%d - %s -> %s\n",
               pos,
               atual->dado.id,
               atual->dado.companhia,
               atual->dado.destino);
        atual = atual->prox;
        pos++;
    }
}

static void executarSimulacaoAutomatica(void) {
    printMensagemColoridaFormatted(YELLOW, "=== Filas - Questao 05 ===");
    printf("\nSimulacao automatizada da fila de decolagem.\n\n");

    FilaAviao fila;
    filaAviaoInicializar(&fila);

    const Aviao iniciais[] = {
        {101, "AZUL", "Curitiba"},
        {202, "GOL", "Sao Paulo"},
        {303, "LATAM", "Brasilia"}
    };

    for (size_t i = 0; i < sizeof(iniciais) / sizeof(iniciais[0]); i++) {
        filaAviaoEnfileirar(&fila, &iniciais[i]);
    }

    printMensagemColoridaFormatted(CYAN, "Fila inicial:\n");
    filaAviaoListar(&fila);
    printf("\n");

    Aviao autorizado;
    if (filaAviaoDesenfileirar(&fila, &autorizado)) {
        printMensagemColoridaFormatted(GREEN,
            "Decolagem autorizada: #%d - %s com destino a %s\n\n",
            autorizado.id,
            autorizado.companhia,
            autorizado.destino);
    }

    const Aviao novo = {404, "AZUL", "Porto Alegre"};
    filaAviaoEnfileirar(&fila, &novo);
    printMensagemColoridaFormatted(CYAN, "Fila apos nova aeronave entrar na espera:\n");
    filaAviaoListar(&fila);
    printf("\n");

    Aviao primeiro;
    if (filaAviaoPrimeiro(&fila, &primeiro)) {
        printMensagemColoridaFormatted(GREEN,
            "Proximo a decolar: #%d - %s -> %s\n",
            primeiro.id,
            primeiro.companhia,
            primeiro.destino);
    }

    printMensagemColoridaFormatted(CYAN,
        "Avioes aguardando: %zu\n",
        fila.tamanho);

    filaAviaoLiberar(&fila);
    pausar();
}

static void lerString(const char *rotulo, char *destino, size_t tamanho) {
    printMensagemColoridaInline(GREEN, rotulo);
    printf(": ");
    if (!fgets(destino, (int)tamanho, stdin)) {
        destino[0] = '\0';
        return;
    }
    destino[strcspn(destino, "\n")] = '\0';
}

static void adicionarAviao(FilaAviao *fila) {
    Aviao novo;
    printMensagemColoridaInline(GREEN, "\nCodigo do aviao");
    printf(": ");
    if (scanf("%d", &novo.id) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nCodigo invalido. Operacao cancelada.\n");
        return;
    }
    limparBufferTeclado();

    lerString("Companhia", novo.companhia, sizeof(novo.companhia));
    lerString("Destino", novo.destino, sizeof(novo.destino));

    if (!filaAviaoEnfileirar(fila, &novo)) {
        printMensagemColoridaFormatted(RED, "\nFalha ao adicionar aviao.\n");
    } else {
        printMensagemColoridaFormatted(GREEN, "\nAviao adicionado com sucesso!\n");
    }
}

static void autorizarDecolagem(FilaAviao *fila) {
    Aviao autorizado;
    if (!filaAviaoDesenfileirar(fila, &autorizado)) {
        printMensagemColoridaFormatted(RED, "\nNenhum aviao aguardando.\n");
        return;
    }

    printMensagemColoridaFormatted(GREEN,
        "\nDecolagem autorizada: #%d - %s com destino a %s\n",
        autorizado.id,
        autorizado.companhia,
        autorizado.destino);
}

static void listarFilaCompleta(const FilaAviao *fila) {
    printf("\nAvioes em espera:\n");
    filaAviaoListar(fila);
}

static void exibirPrimeiro(const FilaAviao *fila) {
    Aviao primeiro;
    if (!filaAviaoPrimeiro(fila, &primeiro)) {
        printMensagemColoridaFormatted(YELLOW, "\nFila vazia.\n");
        return;
    }
    printMensagemColoridaFormatted(CYAN,
        "\nProximo da fila: #%d - %s -> %s\n",
        primeiro.id,
        primeiro.companhia,
        primeiro.destino);
}

static void menuControleAeroportoInterativo(void) {
    FilaAviao fila;
    filaAviaoInicializar(&fila);

    const Aviao iniciais[] = {
        {101, "AZUL", "Curitiba"},
        {202, "GOL", "Sao Paulo"},
        {303, "LATAM", "Brasilia"}
    };
    for (size_t i = 0; i < sizeof(iniciais) / sizeof(iniciais[0]); i++) {
        filaAviaoEnfileirar(&fila, &iniciais[i]);
    }

    int opcao = -1;
    do {
        limparTela();
        printMensagemColoridaFormatted(YELLOW, "=== Filas - Questao 05 (Valores informados) ===");
        printf("\nControle de pista de decolagem - selecione uma acao.\n\n");
        printf("1) Listar numero de avioes aguardando\n");
        printf("2) Autorizar decolagem do primeiro aviao\n");
        printf("3) Adicionar um aviao a fila\n");
        printf("4) Listar todos os avioes na fila\n");
        printf("5) Detalhar o primeiro aviao da fila\n");
        printf("0) Voltar ao menu anterior\n\n");
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
            case 1:
                printMensagemColoridaFormatted(CYAN,
                    "\nAvioes aguardando: %zu\n",
                    fila.tamanho);
                break;
            case 2:
                autorizarDecolagem(&fila);
                break;
            case 3:
                adicionarAviao(&fila);
                break;
            case 4:
                listarFilaCompleta(&fila);
                break;
            case 5:
                exibirPrimeiro(&fila);
                break;
            case 0:
                printMensagemColoridaFormatted(GREEN, "\nEncerrando simulacao.\n");
                break;
            default:
                printMensagemColoridaFormatted(RED, "\nOpcao desconhecida.\n");
                break;
        }

        if (opcao != 0) {
            printf("\n");
            pausar();
        }
    } while (opcao != 0);

    filaAviaoLiberar(&fila);
}

void executarQuestaoFilas5Predefinido(void) {
    limparTela();
    executarSimulacaoAutomatica();
}

void executarQuestaoFilas5EntradaManual(void) {
    menuControleAeroportoInterativo();
    pausar();
}

void executarQuestaoFilas5(void) {
    executarQuestaoFilas5Predefinido();
}
