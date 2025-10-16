#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headlers/menuQuestao.h"
#include "../headlers/menuLista.h"
#include "../../shared/headlers/clean.h"
#include "../../shared/headlers/color.h"
#include "../../shared/headlers/menuGenerico.h"
#include "../../shared/headlers/pathUtils.h"
#include "../../listas/recursividade/index.h"
#include "../../listas/ponteiros/index.h"
#include "../../listas/pilhaDinamica/index.h"
#include "../../listas/filas/index.h"
#include "../../listas/listas/index.h"
#include "../../listas/listasDuplamenteEncadeadas/index.h"
#include "../../listas/arvoresI/index.h"
#include "../../listas/arvoresBinarias/index.h"
#include "../../listas/arvoresAVL/index.h"
#include "../../listas/grafos/index.h"

// Variáveis globais para contexto do menu de questão
static int g_tipoListaQuestao = 0;
static int g_numeroQuestaoAtual = 0;

static char caminhoListaBuffer[512];

const char *obterCaminhoLista(int tipoLista)
{
    char diretorioRaiz[512];
    obterDiretorioRaiz(diretorioRaiz, sizeof(diretorioRaiz));

    if (diretorioRaiz[0] == '\0') {
        // Se nao encontrou a raiz, usa caminho relativo como fallback
        switch (tipoLista)
        {
        case 1: return "src/listas/recursividade";
        case 2:
            return "src/listas/ponteiros";
        case 3:
            return "src/listas/pilhaDinamica";
        case 4:
            return "src/listas/filas";
        case 5:
            return "src/listas/listas";
        case 6:
            return "src/listas/listasDuplamenteEncadeadas";
        case 7:
            return "src/listas/arvoresI";
        case 8:
            return "src/listas/arvoresBinarias";
        case 9:
            return "src/listas/arvoresAVL";
        case 10:
            return "src/listas/grafos";
        default:
            return NULL;
        }
    }

    const char *caminhoRelativo = NULL;
    switch (tipoLista)
    {
    case 1:
        caminhoRelativo = "src/listas/recursividade";
        break;
    case 2:
        caminhoRelativo = "src/listas/ponteiros";
        break;
    case 3:
        caminhoRelativo = "src/listas/pilhaDinamica";
        break;
    case 4:
        caminhoRelativo = "src/listas/filas";
        break;
    case 5:
        caminhoRelativo = "src/listas/listas";
        break;
    case 6:
        caminhoRelativo = "src/listas/listasDuplamenteEncadeadas";
        break;
    case 7:
        caminhoRelativo = "src/listas/arvoresI";
        break;
    case 8:
        caminhoRelativo = "src/listas/arvoresBinarias";
        break;
    case 9:
        caminhoRelativo = "src/listas/arvoresAVL";
        break;
    case 10:
        caminhoRelativo = "src/listas/grafos";
        break;
    default:
        return NULL;
    }

    snprintf(caminhoListaBuffer, sizeof(caminhoListaBuffer), "%s/%s", diretorioRaiz, caminhoRelativo);
    return caminhoListaBuffer;
}

void mostrarDescricaoQuestao(int tipoLista, int numeroQuestao) {
    limparTela();

    setColor(YELLOW);
    printf("=== %s ===\n", obterNomeLista(tipoLista));
    printf("=== Questao %02d ===\n\n", numeroQuestao);
    resetColor();

    const char *caminhoLista = obterCaminhoLista(tipoLista);
    if (caminhoLista != NULL)
    {
        char caminhoArquivo[300];
        sprintf(caminhoArquivo, "%s/lista.txt", caminhoLista);

        FILE *arquivo = fopen(caminhoArquivo, "r");
        if (arquivo != NULL)
        {
            char linha[1000];
            int questaoAtual = 0;
            int encontrouQuestao = 0;

            while (fgets(linha, sizeof(linha), arquivo) && !encontrouQuestao)
            {
                if (strncmp(linha, "QUESTAO", 7) == 0)
                {
                    char numStr[10];
                    if (sscanf(linha, "QUESTAO %s:", numStr) == 1)
                    {
                        questaoAtual = atoi(numStr);
                        if (questaoAtual == numeroQuestao)
                        {
                            encontrouQuestao = 1;
                            while (fgets(linha, sizeof(linha), arquivo))
                            {
                                if (strncmp(linha, "Logica utilizada:", 17) == 0 || strncmp(linha, "---", 3) == 0)
                                {
                                    break;
                                }
                                if (strlen(linha) > 1)
                                {
                                    printf("%s", linha);
                                }
                            }
                            break;
                        }
                    }
                }
            }

            if (!encontrouQuestao)
            {
                setColor(RED);
                printf("Esta questao ainda nao foi implementada.\n");
                resetColor();
                printf("Para adicionar o conteudo da questao:\n");
                printf("1. Edite o arquivo lista.txt na pasta da lista correspondente\n");
                printf("2. Crie os arquivos %d.h e %d.c nas pastas headlers e core\n", numeroQuestao, numeroQuestao);
            }

            fclose(arquivo);
        }
        else
        {
            setColor(RED);
            printf("Arquivo lista.txt nao encontrado.\n");
            resetColor();
            printf("Crie o arquivo %s para adicionar questoes.\n", caminhoArquivo);
        }
    }

    pausar();
}

void mostrarLogicaQuestao(int tipoLista, int numeroQuestao)
{
    limparTela();

    setColor(YELLOW);
    printf("=== %s ===\n", obterNomeLista(tipoLista));
    printf("=== Logica Utilizada - Questao %02d ===\n\n", numeroQuestao);
    resetColor();

    const char *caminhoLista = obterCaminhoLista(tipoLista);
    if (caminhoLista == NULL)
    {
        setColor(RED);
        printf("Lista invalida!\n");
        resetColor();
        pausar();
        return;
    }

    char caminhoArquivo[300];
    sprintf(caminhoArquivo, "%s/lista.txt", caminhoLista);

    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL)
    {
        setColor(RED);
        printf("Arquivo lista.txt nao encontrado em: %s\n", caminhoArquivo);
        printf("Crie o arquivo para adicionar o conteudo das questoes.\n\n");
        resetColor();
    }
    else
    {
        char linha[1000];
        int questaoAtual = 0;
        int encontrouQuestao = 0;
        int dentroLogica = 0;

        while (fgets(linha, sizeof(linha), arquivo))
        {
            if (strncmp(linha, "QUESTAO", 7) == 0)
            {
                char numStr[10];
                if (sscanf(linha, "QUESTAO %s:", numStr) == 1)
                {
                    questaoAtual = atoi(numStr);
                    if (questaoAtual == numeroQuestao)
                    {
                        encontrouQuestao = 1;
                        setColor(GREEN);
                        printf("Descricao da Questao:\n");
                        resetColor();
                    }
                    else if (encontrouQuestao)
                    {
                        break;
                    }
                }
            }
            else if (encontrouQuestao)
            {
                if (strncmp(linha, "Logica utilizada:", 17) == 0)
                {
                    dentroLogica = 1;
                    setColor(CYAN);
                    printf("\n=== LOGICA UTILIZADA ===\n");
                    resetColor();
                }
                else if (strncmp(linha, "---", 3) == 0)
                {
                    break;
                }
                else if (dentroLogica && strlen(linha) > 1)
                {
                    printf("%s", linha);
                }
                else if (!dentroLogica && strlen(linha) > 1)
                {
                    printf("%s", linha);
                }
            }
        }

        if (!encontrouQuestao)
        {
            setColor(RED);
            printf("Questao %02d nao encontrada no arquivo lista.txt\n", numeroQuestao);
            printf("Adicione o conteudo da questao no arquivo.\n\n");
            resetColor();
        }

        fclose(arquivo);
    }

    pausar();
}

static char* anexarTexto(char* buffer, size_t* tamanhoAtual, const char* texto) {
    size_t adicionar = strlen(texto);
    char* novo = realloc(buffer, (*tamanhoAtual) + adicionar + 1);
    if (!novo) {
        free(buffer);
        return NULL;
    }
    memcpy(novo + *tamanhoAtual, texto, adicionar);
    *tamanhoAtual += adicionar;
    novo[*tamanhoAtual] = '\0';
    return novo;
}

static char* carregarDescricaoQuestao(int tipoLista, int numeroQuestao) {
    const char* caminhoLista = obterCaminhoLista(tipoLista);
    if (!caminhoLista) {
        char* mensagem = (char*)malloc(32);
        if (mensagem) {
            strcpy(mensagem, "Descricao indisponivel.");
        }
        return mensagem;
    }

    char caminhoArquivo[300];
    sprintf(caminhoArquivo, "%s/lista.txt", caminhoLista);

    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        char* mensagem = (char*)malloc(60);
        if (mensagem) {
            strcpy(mensagem, "lista.txt nao encontrado para esta lista.");
        }
        return mensagem;
    }

    char linha[1000];
    int questaoAtual = 0;
    int encontrouQuestao = 0;

    char* descricao = NULL;
    size_t tamanhoDescricao = 0;

    descricao = anexarTexto(descricao, &tamanhoDescricao, "Descricao da questao:\n");
    if (!descricao) {
        fclose(arquivo);
        return NULL;
    }

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strncmp(linha, "QUESTAO", 7) == 0) {
            char numStr[10];
            if (sscanf(linha, "QUESTAO %s:", numStr) == 1) {
                questaoAtual = atoi(numStr);
                if (questaoAtual == numeroQuestao) {
                    encontrouQuestao = 1;
                } else if (encontrouQuestao) {
                    break;
                }
            }
        } else if (encontrouQuestao) {
            if (strncmp(linha, "Logica utilizada:", 17) == 0) {
                break;
            }
            if (strncmp(linha, "---", 3) == 0) {
                break;
            }
            if (strlen(linha) > 1) {
                descricao = anexarTexto(descricao, &tamanhoDescricao, linha);
                if (!descricao) {
                    fclose(arquivo);
                    return NULL;
                }
            }
        }
    }

    fclose(arquivo);

    if (!encontrouQuestao) {
        free(descricao);
        descricao = (char*)malloc(64);
        if (descricao) {
            sprintf(descricao, "Questao %02d nao encontrada em lista.txt.", numeroQuestao);
        }
    }

    return descricao;
}

typedef void (*FuncaoQuestao)(void);

// Quantidade de questões por categoria
// {0, Recur, Pont, Pilha, Filas, Listas, ListasDupl, ArvI, ArvBin, ArvAVL, Grafos}
static int quantidadeQuestoes[] = {0, 12, 9, 9, 8, 9, 5, 5, 11, 8, 17};

static FuncaoQuestao* todasFuncoes[11] = {NULL};
static FuncaoQuestao* funcoesEntrada[11] = {NULL};
static int inicializado = 0;

void inicializarFuncoes() {
    if (inicializado) return;

    todasFuncoes[1] = malloc(12 * sizeof(FuncaoQuestao));
    todasFuncoes[1][0] = executarQuestaoRecursividade1;
    todasFuncoes[1][1] = executarQuestaoRecursividade2;
    todasFuncoes[1][2] = executarQuestaoRecursividade3;
    todasFuncoes[1][3] = executarQuestaoRecursividade4;
    todasFuncoes[1][4] = executarQuestaoRecursividade5;
    todasFuncoes[1][5] = executarQuestaoRecursividade6;
    todasFuncoes[1][6] = executarQuestaoRecursividade7;
    todasFuncoes[1][7] = executarQuestaoRecursividade8;
    todasFuncoes[1][8] = executarQuestaoRecursividade9;
    todasFuncoes[1][9] = executarQuestaoRecursividade10;
    todasFuncoes[1][10] = executarQuestaoRecursividade11;
    todasFuncoes[1][11] = executarQuestaoRecursividade12;

    funcoesEntrada[1] = malloc(12 * sizeof(FuncaoQuestao));
    funcoesEntrada[1][0] = executarQuestaoRecursividade1EntradaManual;
    funcoesEntrada[1][1] = executarQuestaoRecursividade2EntradaManual;
    funcoesEntrada[1][2] = executarQuestaoRecursividade3EntradaManual;
    funcoesEntrada[1][3] = executarQuestaoRecursividade4EntradaManual;
    funcoesEntrada[1][4] = executarQuestaoRecursividade5EntradaManual;
    funcoesEntrada[1][5] = executarQuestaoRecursividade6EntradaManual;
    funcoesEntrada[1][6] = executarQuestaoRecursividade7EntradaManual;
    funcoesEntrada[1][7] = executarQuestaoRecursividade8EntradaManual;
    funcoesEntrada[1][8] = executarQuestaoRecursividade9EntradaManual;
    funcoesEntrada[1][9] = executarQuestaoRecursividade10EntradaManual;
    funcoesEntrada[1][10] = executarQuestaoRecursividade11EntradaManual;
    funcoesEntrada[1][11] = executarQuestaoRecursividade12EntradaManual;

    todasFuncoes[2] = malloc(9 * sizeof(FuncaoQuestao));
    todasFuncoes[2][0] = executarQuestaoPonteiros1;
    todasFuncoes[2][1] = executarQuestaoPonteiros2;
    todasFuncoes[2][2] = executarQuestaoPonteiros3;
    todasFuncoes[2][3] = executarQuestaoPonteiros4;
    todasFuncoes[2][4] = executarQuestaoPonteiros5;
    todasFuncoes[2][5] = executarQuestaoPonteiros6;
    todasFuncoes[2][6] = executarQuestaoPonteiros7;
    todasFuncoes[2][7] = executarQuestaoPonteiros8;
    todasFuncoes[2][8] = executarQuestaoPonteiros9;

    funcoesEntrada[2] = malloc(9 * sizeof(FuncaoQuestao));
    funcoesEntrada[2][0] = executarQuestaoPonteiros1EntradaManual;
    funcoesEntrada[2][1] = executarQuestaoPonteiros2EntradaManual;
    funcoesEntrada[2][2] = executarQuestaoPonteiros3EntradaManual;
    funcoesEntrada[2][3] = executarQuestaoPonteiros4EntradaManual;
    funcoesEntrada[2][4] = executarQuestaoPonteiros5EntradaManual;
    funcoesEntrada[2][5] = executarQuestaoPonteiros6EntradaManual;
    funcoesEntrada[2][6] = executarQuestaoPonteiros7EntradaManual;
    funcoesEntrada[2][7] = executarQuestaoPonteiros8EntradaManual;
    funcoesEntrada[2][8] = executarQuestaoPonteiros9EntradaManual;

    todasFuncoes[3] = malloc(9 * sizeof(FuncaoQuestao));
    todasFuncoes[3][0] = executarQuestaoPilhaDinamica1;
    todasFuncoes[3][1] = executarQuestaoPilhaDinamica2;
    todasFuncoes[3][2] = executarQuestaoPilhaDinamica3;
    todasFuncoes[3][3] = executarQuestaoPilhaDinamica4;
    todasFuncoes[3][4] = executarQuestaoPilhaDinamica5;
    todasFuncoes[3][5] = executarQuestaoPilhaDinamica6;
    todasFuncoes[3][6] = executarQuestaoPilhaDinamica7;
    todasFuncoes[3][7] = executarQuestaoPilhaDinamica8;
    todasFuncoes[3][8] = executarQuestaoPilhaDinamica9;

    funcoesEntrada[3] = malloc(9 * sizeof(FuncaoQuestao));
    funcoesEntrada[3][0] = executarQuestaoPilhaDinamica1EntradaManual;
    funcoesEntrada[3][1] = executarQuestaoPilhaDinamica2EntradaManual;
    funcoesEntrada[3][2] = executarQuestaoPilhaDinamica3EntradaManual;
    funcoesEntrada[3][3] = executarQuestaoPilhaDinamica4EntradaManual;
    funcoesEntrada[3][4] = executarQuestaoPilhaDinamica5EntradaManual;
    funcoesEntrada[3][5] = executarQuestaoPilhaDinamica6EntradaManual;
    funcoesEntrada[3][6] = executarQuestaoPilhaDinamica7EntradaManual;
    funcoesEntrada[3][7] = executarQuestaoPilhaDinamica8EntradaManual;
    funcoesEntrada[3][8] = executarQuestaoPilhaDinamica9EntradaManual;

    // Lista 4: Filas (8 questões)
    todasFuncoes[4] = malloc(8 * sizeof(FuncaoQuestao));
    todasFuncoes[4][0] = executarQuestaoFilas1;
    todasFuncoes[4][1] = executarQuestaoFilas2;
    todasFuncoes[4][2] = executarQuestaoFilas3;
    todasFuncoes[4][3] = executarQuestaoFilas4;
    todasFuncoes[4][4] = executarQuestaoFilas5;
    todasFuncoes[4][5] = executarQuestaoFilas6;
    todasFuncoes[4][6] = executarQuestaoFilas7;
    todasFuncoes[4][7] = executarQuestaoFilas8;

    funcoesEntrada[4] = malloc(8 * sizeof(FuncaoQuestao));
    funcoesEntrada[4][0] = executarQuestaoFilas1EntradaManual;
    funcoesEntrada[4][1] = executarQuestaoFilas2EntradaManual;
    funcoesEntrada[4][2] = executarQuestaoFilas3EntradaManual;
    funcoesEntrada[4][3] = executarQuestaoFilas4EntradaManual;
    funcoesEntrada[4][4] = executarQuestaoFilas5EntradaManual;
    funcoesEntrada[4][5] = executarQuestaoFilas6EntradaManual;
    funcoesEntrada[4][6] = executarQuestaoFilas7EntradaManual;
    funcoesEntrada[4][7] = executarQuestaoFilas8EntradaManual;

    funcoesEntrada[5] = malloc(9 * sizeof(FuncaoQuestao));
    funcoesEntrada[5][0] = executarQuestaoListas1EntradaManual;
    funcoesEntrada[5][1] = executarQuestaoListas2EntradaManual;
    funcoesEntrada[5][2] = executarQuestaoListas3EntradaManual;
    funcoesEntrada[5][3] = executarQuestaoListas4EntradaManual;
    funcoesEntrada[5][4] = executarQuestaoListas5EntradaManual;
    funcoesEntrada[5][5] = executarQuestaoListas6EntradaManual;
    funcoesEntrada[5][6] = executarQuestaoListas7EntradaManual;
    funcoesEntrada[5][7] = executarQuestaoListas8EntradaManual;
    funcoesEntrada[5][8] = executarQuestaoListas9EntradaManual;

    funcoesEntrada[6] = malloc(5 * sizeof(FuncaoQuestao));
    funcoesEntrada[6][0] = executarQuestaoListasDuplamenteEncadeadas1EntradaManual;
    funcoesEntrada[6][1] = executarQuestaoListasDuplamenteEncadeadas2EntradaManual;
    funcoesEntrada[6][2] = executarQuestaoListasDuplamenteEncadeadas3EntradaManual;
    funcoesEntrada[6][3] = executarQuestaoListasDuplamenteEncadeadas4EntradaManual;
    funcoesEntrada[6][4] = executarQuestaoListasDuplamenteEncadeadas5EntradaManual;

    funcoesEntrada[7] = malloc(5 * sizeof(FuncaoQuestao));
    funcoesEntrada[7][0] = executarQuestaoArvoresI1EntradaManual;
    funcoesEntrada[7][1] = executarQuestaoArvoresI2EntradaManual;
    funcoesEntrada[7][2] = executarQuestaoArvoresI3EntradaManual;
    funcoesEntrada[7][3] = executarQuestaoArvoresI4EntradaManual;
    funcoesEntrada[7][4] = executarQuestaoArvoresI5EntradaManual;

    // Lista 5: Listas (9 questões)
    todasFuncoes[5] = malloc(9 * sizeof(FuncaoQuestao));
    todasFuncoes[5][0] = executarQuestaoListas1;
    todasFuncoes[5][1] = executarQuestaoListas2;
    todasFuncoes[5][2] = executarQuestaoListas3;
    todasFuncoes[5][3] = executarQuestaoListas4;
    todasFuncoes[5][4] = executarQuestaoListas5;
    todasFuncoes[5][5] = executarQuestaoListas6;
    todasFuncoes[5][6] = executarQuestaoListas7;
    todasFuncoes[5][7] = executarQuestaoListas8;
    todasFuncoes[5][8] = executarQuestaoListas9;

    // Lista 6: Listas Duplamente Encadeadas (5 questões)
    todasFuncoes[6] = malloc(5 * sizeof(FuncaoQuestao));
    todasFuncoes[6][0] = executarQuestaoListasDuplamenteEncadeadas1;
    todasFuncoes[6][1] = executarQuestaoListasDuplamenteEncadeadas2;
    todasFuncoes[6][2] = executarQuestaoListasDuplamenteEncadeadas3;
    todasFuncoes[6][3] = executarQuestaoListasDuplamenteEncadeadas4;
    todasFuncoes[6][4] = executarQuestaoListasDuplamenteEncadeadas5;

    // Lista 7: Árvores I (5 questões)
    todasFuncoes[7] = malloc(5 * sizeof(FuncaoQuestao));
    todasFuncoes[7][0] = executarQuestaoArvoresI1;
    todasFuncoes[7][1] = executarQuestaoArvoresI2;
    todasFuncoes[7][2] = executarQuestaoArvoresI3;
    todasFuncoes[7][3] = executarQuestaoArvoresI4;
    todasFuncoes[7][4] = executarQuestaoArvoresI5;

    // Lista 8: Árvores Binárias (11 questões - inclui 9a, 9b, 9c)
    todasFuncoes[8] = malloc(11 * sizeof(FuncaoQuestao));
    todasFuncoes[8][0] = executarQuestaoArvoresBinarias1;
    todasFuncoes[8][1] = executarQuestaoArvoresBinarias2;
    todasFuncoes[8][2] = executarQuestaoArvoresBinarias3;
    todasFuncoes[8][3] = executarQuestaoArvoresBinarias4;
    todasFuncoes[8][4] = executarQuestaoArvoresBinarias5;
    todasFuncoes[8][5] = executarQuestaoArvoresBinarias6;
    todasFuncoes[8][6] = executarQuestaoArvoresBinarias7;
    todasFuncoes[8][7] = executarQuestaoArvoresBinarias8;
    todasFuncoes[8][8] = executarQuestaoArvoresBinarias9a;
    todasFuncoes[8][9] = executarQuestaoArvoresBinarias9b;
    todasFuncoes[8][10] = executarQuestaoArvoresBinarias9c;

    // Lista 9: Árvores AVL (8 questões)
    todasFuncoes[9] = malloc(8 * sizeof(FuncaoQuestao));
    todasFuncoes[9][0] = executarQuestaoArvoresAVL1;
    todasFuncoes[9][1] = executarQuestaoArvoresAVL2;
    todasFuncoes[9][2] = executarQuestaoArvoresAVL3;
    todasFuncoes[9][3] = executarQuestaoArvoresAVL4;
    todasFuncoes[9][4] = executarQuestaoArvoresAVL5;
    todasFuncoes[9][5] = executarQuestaoArvoresAVL6;
    todasFuncoes[9][6] = executarQuestaoArvoresAVL7;
    todasFuncoes[9][7] = executarQuestaoArvoresAVL8;

    // Lista 10: Grafos (17 questões)
    todasFuncoes[10] = malloc(17 * sizeof(FuncaoQuestao));
    todasFuncoes[10][0] = executarQuestaoGrafos1a;
    todasFuncoes[10][1] = executarQuestaoGrafos1b;
    todasFuncoes[10][2] = executarQuestaoGrafos2a;
    todasFuncoes[10][3] = executarQuestaoGrafos2b;
    todasFuncoes[10][4] = executarQuestaoGrafos2c;
    todasFuncoes[10][5] = executarQuestaoGrafos2d;
    todasFuncoes[10][6] = executarQuestaoGrafos2e;
    todasFuncoes[10][7] = executarQuestaoGrafos2f;
    todasFuncoes[10][8] = executarQuestaoGrafos2g;
    todasFuncoes[10][9] = executarQuestaoGrafos3a;
    todasFuncoes[10][10] = executarQuestaoGrafos3b;
    todasFuncoes[10][11] = executarQuestaoGrafos3c;
    todasFuncoes[10][12] = executarQuestaoGrafos3d;
    todasFuncoes[10][13] = executarQuestaoGrafos4;
    todasFuncoes[10][14] = executarQuestaoGrafos5;
    todasFuncoes[10][15] = executarQuestaoGrafos6a;
    todasFuncoes[10][16] = executarQuestaoGrafos6b;

    inicializado = 1;
}

static FuncaoQuestao obterFuncaoPrincipal(int tipoLista, int numeroQuestao) {
    inicializarFuncoes();
    if (tipoLista < 1 || tipoLista > 10) return NULL;
    if (todasFuncoes[tipoLista] == NULL) return NULL;
    if (numeroQuestao < 1 || numeroQuestao > quantidadeQuestoes[tipoLista]) return NULL;
    return todasFuncoes[tipoLista][numeroQuestao - 1];
}

static FuncaoQuestao obterFuncaoEntradaManual(int tipoLista, int numeroQuestao) {
    inicializarFuncoes();
    if (tipoLista < 1 || tipoLista > 10) return NULL;
    if (funcoesEntrada[tipoLista] == NULL) return NULL;
    if (numeroQuestao < 1 || numeroQuestao > quantidadeQuestoes[tipoLista]) return NULL;
    return funcoesEntrada[tipoLista][numeroQuestao - 1];
}

void mostrarInstrucoesImplementacao(int tipoLista, int numeroQuestao, const char* caminhoLista) {
    setColor(YELLOW);
    printf("Questao %d encontrada mas ainda nao implementada.\n", numeroQuestao);
    printf("Para executar:\n");
    printf("1. Implemente a funcao executarQuestao%02d() em %s/core/%d.c\n", numeroQuestao,
           caminhoLista ? caminhoLista : "src/listas/[lista]", numeroQuestao);
    printf("2. Declare executarQuestao%02d em %s/index.h\n", numeroQuestao,
           caminhoLista ? caminhoLista : "src/listas/[lista]");
    printf("3. Registre a funcao em menuQuestao.c (inicializarFuncoes)\n");
    printf("Localizacao: menuQuestao.c -> case %d -> case %d\n", tipoLista, numeroQuestao);
    resetColor();
}

void executarQuestaoNaoImplementada(int tipoLista, int numeroQuestao, const char* caminhoLista) {
    mostrarInstrucoesImplementacao(tipoLista, numeroQuestao, caminhoLista);
}

static void executarQuestaoComAcao(int tipoLista, int numeroQuestao, FuncaoQuestao acao, const char* contexto) {
    if (!acao) {
        setColor(RED);
        printf("Opcao '%s' ainda nao esta disponivel para esta questao.\n", contexto ? contexto : "acao");
        resetColor();
        pausar();
        return;
    }

    limparTela();

    setColor(YELLOW);
    printf("=== %s ===\n", obterNomeLista(tipoLista));
    printf("=== Executando a Questao %02d (%s) ===\n\n", numeroQuestao, contexto ? contexto : "execucao");
    resetColor();

    const char *caminhoLista = obterCaminhoLista(tipoLista);
    if (caminhoLista == NULL) {
        setColor(RED);
        printf("Lista invalida!\n");
        resetColor();
        pausar();
        return;
    }

    char caminhoSource[300];
    sprintf(caminhoSource, "%s/core/%d.c", caminhoLista, numeroQuestao);

    FILE *testeSource = fopen(caminhoSource, "r");

    if (testeSource == NULL) {
        setColor(RED);
        printf("Arquivos da questao nao encontrados!\n");
        printf("Certifique-se de que exista:\n- %s\n", caminhoSource);
        printf("\nPara implementar esta questao:\n");
        printf("1. Crie o arquivo %d.c na pasta core\n", numeroQuestao);
        printf("2. Declare as funcoes em index.h conforme o padrao atual\n");
        printf("3. Registre a funcao em menuQuestao.c (inicializarFuncoes)\n\n");
        resetColor();

        if (testeSource) {
            fclose(testeSource);
        }
        pausar();
        return;
    }

    fclose(testeSource);

    setColor(GREEN);
    printf("Executando questao implementada...\n\n");
    resetColor();

    acao();
}

void executarQuestao(int tipoLista, int numeroQuestao)
{
    FuncaoQuestao acao = obterFuncaoPrincipal(tipoLista, numeroQuestao);
    executarQuestaoComAcao(tipoLista, numeroQuestao, acao, "valores pre-definidos");
}

//
// Callbacks para o menu de questão
static int executarPreDefinido(void) {
    FuncaoQuestao acao = obterFuncaoPrincipal(g_tipoListaQuestao, g_numeroQuestaoAtual);
    executarQuestaoComAcao(g_tipoListaQuestao, g_numeroQuestaoAtual, acao, "valores pre-definidos");
    return 1;
}

static int executarEntradaPersonalizada(void) {
    FuncaoQuestao acao = obterFuncaoEntradaManual(g_tipoListaQuestao, g_numeroQuestaoAtual);
    executarQuestaoComAcao(g_tipoListaQuestao, g_numeroQuestaoAtual, acao, "valores informados");
    return 1;
}

static int mostrarLogicaDescricao(void) {
    mostrarLogicaQuestao(g_tipoListaQuestao, g_numeroQuestaoAtual);
    return 1;
}

int mostrarMenuQuestao(int tipoLista, int numeroQuestao)
{
    g_tipoListaQuestao = tipoLista;
    g_numeroQuestaoAtual = numeroQuestao;

    OpcaoMenu opcoes[] = {
        {"Executar com valores pre-definidos", ACAO_EXECUTAR_FUNCAO, executarPreDefinido},
        {"Executar informando valores", ACAO_EXECUTAR_FUNCAO, executarEntradaPersonalizada},
        {"Mostrar logica utilizada", ACAO_EXECUTAR_FUNCAO, mostrarLogicaDescricao}
    };

    char titulo[100];
    sprintf(titulo, "%s - Questao %02d", obterNomeLista(tipoLista), numeroQuestao);

    MenuGenerico* menu = criarMenu(titulo, opcoes, 3);
    int resultado = 1;
    if (menu) {
        char* descricao = carregarDescricaoQuestao(tipoLista, numeroQuestao);
        if (descricao) {
            definirDescricaoMenu(menu, descricao);
            free(descricao);
        }

        resultado = executarMenu(menu);
        destruirMenu(menu);
    }

    return resultado;
}
