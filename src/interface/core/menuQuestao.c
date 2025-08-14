#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headlers/menuQuestao.h"
#include "../headlers/menuLista.h"
#include "../../shared/headlers/clean.h"
#include "../../shared/headlers/color.h"
#include "../../shared/headlers/colorPrint.h"
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

const char *obterCaminhoLista(int tipoLista)
{
    switch (tipoLista)
    {
    case 1:
        return "../src/listas/recursividade";
    case 2:
        return "../src/listas/ponteiros";
    case 3:
        return "../src/listas/pilhaDinamica";
    case 4:
        return "../src/listas/filas";
    case 5:
        return "../src/listas/listas";
    case 6:
        return "../src/listas/listasDuplamenteEncadeadas";
    case 7:
        return "../src/listas/arvoresI";
    case 8:
        return "../src/listas/arvoresBinarias";
    case 9:
        return "../src/listas/arvoresAVL";
    case 10:
        return "../src/listas/grafos";
    default:
        return NULL;
    }
}

void mostrarInstrucoesImplementacao(int tipoLista, int numeroQuestao, const char* caminhoLista) {
    (void)caminhoLista;
    setColor(YELLOW);
    printf("Questao %d encontrada mas ainda nao implementada.\n", numeroQuestao);
    printf("Para executar:\n");
    printf("1. Implemente a funcao executarQuestao%d() no arquivo %d.c\n", numeroQuestao, numeroQuestao);
    printf("2. Inclua o header: #include \"../../listas/[lista]/headlers/%d.h\"\n", numeroQuestao);
    printf("3. Adicione a chamada no switch case %d\n", numeroQuestao);
    printf("Localizacao: menuQuestao.c -> case %d -> case %d\n", tipoLista, numeroQuestao);
    resetColor();
}

// Função auxiliar para execução padrão de questões não implementadas
void executarQuestaoNaoImplementada(int tipoLista, int numeroQuestao, const char* caminhoLista) {
    mostrarInstrucoesImplementacao(tipoLista, numeroQuestao, caminhoLista);
}

int mostrarMenuQuestao(int tipoLista, int numeroQuestao)
{
    int opcao;

    do
    {
        limparTela();

        setColor(YELLOW);
        printf("=== %s ===\n", obterNomeLista(tipoLista));
        printf("=== Questao %02d ===\n\n", numeroQuestao);
        resetColor();

        // Tentar mostrar o enunciado da questao do arquivo lista.txt
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
                                // Ler e mostrar as proximas linhas ate encontrar "Logica utilizada" ou "---"
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
                    printf("2. Crie os arquivos %d.h e %d.c nas pastas headlers e core", numeroQuestao, numeroQuestao);
                }

                fclose(arquivo);
            }
            else
            {
                setColor(RED);
                printf("Arquivo lista.txt nao encontrado.\n");
                resetColor();
                printf("Crie o arquivo %s para adicionar questoes.\n\n", caminhoArquivo);
            }
        }

        setColor(CYAN);
        printf("\n\n=== Menu da Questao ===\n");
        resetColor();
        printf("Escolha uma opcao a seguir:\n");
        printMenuItem(1, "Ver logica utilizada para resolver");
        printMenuItem(2, "Executar a questao");
        printMenuItemFormatted(3, "Voltar a lista de questoes de %s", obterNomeLista(tipoLista));
        printMenuItem(0, "Voltar ao menu principal");
        setColor(YELLOW);
        printf("> ");

        if (scanf("%d", &opcao) != 1)
        {
            setColor(RED);
            printf("Entrada invalida! Digite apenas numeros.\n");
            resetColor();
            while (getchar() != '\n')
                ;
            printf("Pressione Enter para continuar...");
            getchar();
            continue;
        }

        resetColor();
        processarOpcaoQuestao(tipoLista, numeroQuestao, opcao);

    } while (opcao != 0 && opcao != 3);
    
    // Retorna 0 se deve voltar ao menu principal, 1 se deve voltar ao menu da lista
    return (opcao == 0) ? 0 : 1;
}

void processarOpcaoQuestao(int tipoLista, int numeroQuestao, int opcao)
{
    switch (opcao)
    {
    case 0:
        return;
    case 1:
        mostrarLogicaQuestao(tipoLista, numeroQuestao);
        break;
    case 2:
        executarQuestao(tipoLista, numeroQuestao);
        break;
    case 3:
        return;
    default:
        setColor(RED);
        printf("Opcao invalida! Digite um numero entre 0 e 3.\n");
        resetColor();
        printf("Pressione Enter para continuar...");
        while (getchar() != '\n')
            ;
        getchar();
        break;
    }
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
        printf("Pressione Enter para continuar...");
        while (getchar() != '\n')
            ;
        getchar();
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

    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n')
        ;
    getchar();
}

void executarQuestao(int tipoLista, int numeroQuestao)
{
    limparTela();

    setColor(YELLOW);
    printf("=== %s ===\n", obterNomeLista(tipoLista));
    printf("=== Executando a Questao %02d ===\n\n", numeroQuestao);
    resetColor();

    const char *caminhoLista = obterCaminhoLista(tipoLista);
    if (caminhoLista == NULL)
    {
        setColor(RED);
        printf("Lista invalida!\n");
        resetColor();
        printf("Pressione Enter para continuar...");
        while (getchar() != '\n')
            ;
        getchar();
        return;
    }

    // Verifica se os arquivos .h e .c existem
    char caminhoHeader[300];
    char caminhoSource[300];
    sprintf(caminhoHeader, "%s/headlers/%d.h", caminhoLista, numeroQuestao);
    sprintf(caminhoSource, "%s/core/%d.c", caminhoLista, numeroQuestao);

    FILE *testeHeader = fopen(caminhoHeader, "r");
    FILE *testeSource = fopen(caminhoSource, "r");

    if (testeHeader == NULL || testeSource == NULL)
    {
        setColor(RED);
        printf("Arquivos da questao nao encontrados!\n");
        printf("Certifique-se de que existem:\n");
        printf("- %s\n", caminhoHeader);
        printf("- %s\n", caminhoSource);
        printf("\nPara implementar esta questao:\n");
        printf("1. Crie o arquivo %d.h na pasta headlers\n", numeroQuestao);
        printf("2. Crie o arquivo %d.c na pasta core\n", numeroQuestao);
        printf("3. Implemente a funcao executarQuestao%d()\n\n", numeroQuestao);
        resetColor();

        if (testeHeader)
            fclose(testeHeader);
        if (testeSource)
            fclose(testeSource);
    }
    else
    {
        fclose(testeHeader);
        fclose(testeSource);
        // Para cada lista/questao, chama a funcao executar correspondente

        // Executar a funcao especifica da questao
        setColor(GREEN);
        printf("Executando questao implementada...\n\n");
        resetColor();

        switch (tipoLista)
        {
        case 1: // Recursividade
            switch (numeroQuestao)
            {
            case 1:
                executarQuestaoRecursividade1();
                break;
            case 2:
                executarQuestaoRecursividade2();
                break;
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            default:
                executarQuestaoNaoImplementada(tipoLista, numeroQuestao, caminhoLista);
                break;
            }
            break;

        case 2: // Ponteiros
            switch (numeroQuestao)
            {
            case 1:
                executarQuestaoPonteiros1();
                break;
            default:
                executarQuestaoNaoImplementada(tipoLista, numeroQuestao, caminhoLista);
                break;
            }
            break;

        case 3:  // Pilha Dinamica
        case 4:  // Filas
        case 5:  // Listas
        case 6:  // Listas Duplamente Encadeadas
        case 7:  // Arvores I
        case 8:  // Arvores Binarias
        case 9:  // Arvores AVL
        case 10: // Grafos
        default:
            // Para todas as outras listas, usar função padrão
            executarQuestaoNaoImplementada(tipoLista, numeroQuestao, caminhoLista);
            break;
        }
    }

    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n')
        ;
    getchar();
}