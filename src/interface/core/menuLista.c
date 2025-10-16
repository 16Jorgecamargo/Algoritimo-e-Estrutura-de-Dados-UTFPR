#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headlers/menuLista.h"
#include "../headlers/menuQuestao.h"
#include "../../shared/headlers/clean.h"
#include "../../shared/headlers/color.h"
#include "../../shared/headlers/menuGenerico.h"

#ifdef _WIN32
    #include <io.h>
    #include <direct.h>
    #define ACCESS _access
#else
    #include <unistd.h>
    #define ACCESS access
#endif

// Variável global para passar contexto aos callbacks
static int g_tipoLista = 0;

const char* obterNomeLista(int tipoLista) {
    switch(tipoLista) {
        case 1: return "Recursividade";
        case 2: return "Ponteiros";
        case 3: return "Pilha Dinamica";
        case 4: return "Filas";
        case 5: return "Listas";
        case 6: return "Listas Duplamente Encadeadas";
        case 7: return "Arvores I";
        case 8: return "Arvores Binarias";
        case 9: return "Arvores AVL";
        case 10: return "Grafos";
        default: return "Lista Desconhecida";
    }
}

int contarQuestoes(int tipoLista) {
    const char *caminhoLista = obterCaminhoLista(tipoLista);
    if (caminhoLista == NULL) return 0;

    int contador = 0;
    for (int i = 1; i <= 15; i++) {
        char caminhoArquivo[300];
        sprintf(caminhoArquivo, "%s/core/%d.c", caminhoLista, i);

        if (ACCESS(caminhoArquivo, 0) == 0) {
            contador = i;
        }
    }

    return contador;
}

// Callbacks para cada questão (até 15 questões)
static int abrirQuestao1(void) { return mostrarMenuQuestao(g_tipoLista, 1); }
static int abrirQuestao2(void) { return mostrarMenuQuestao(g_tipoLista, 2); }
static int abrirQuestao3(void) { return mostrarMenuQuestao(g_tipoLista, 3); }
static int abrirQuestao4(void) { return mostrarMenuQuestao(g_tipoLista, 4); }
static int abrirQuestao5(void) { return mostrarMenuQuestao(g_tipoLista, 5); }
static int abrirQuestao6(void) { return mostrarMenuQuestao(g_tipoLista, 6); }
static int abrirQuestao7(void) { return mostrarMenuQuestao(g_tipoLista, 7); }
static int abrirQuestao8(void) { return mostrarMenuQuestao(g_tipoLista, 8); }
static int abrirQuestao9(void) { return mostrarMenuQuestao(g_tipoLista, 9); }
static int abrirQuestao10(void) { return mostrarMenuQuestao(g_tipoLista, 10); }
static int abrirQuestao11(void) { return mostrarMenuQuestao(g_tipoLista, 11); }
static int abrirQuestao12(void) { return mostrarMenuQuestao(g_tipoLista, 12); }
static int abrirQuestao13(void) { return mostrarMenuQuestao(g_tipoLista, 13); }
static int abrirQuestao14(void) { return mostrarMenuQuestao(g_tipoLista, 14); }
static int abrirQuestao15(void) { return mostrarMenuQuestao(g_tipoLista, 15); }

// Array de callbacks
static FuncaoCallback callbacks[15] = {
    abrirQuestao1, abrirQuestao2, abrirQuestao3, abrirQuestao4, abrirQuestao5,
    abrirQuestao6, abrirQuestao7, abrirQuestao8, abrirQuestao9, abrirQuestao10,
    abrirQuestao11, abrirQuestao12, abrirQuestao13, abrirQuestao14, abrirQuestao15
};

int mostrarMenuLista(int tipoLista) {
    g_tipoLista = tipoLista;
    int numQuestoes = contarQuestoes(tipoLista);

    if (numQuestoes == 0) {
        limparTela();
        setColor(YELLOW);
        printf("=== %s ===\n", obterNomeLista(tipoLista));
        resetColor();
        setColor(RED);
        printf("\nNenhuma questao encontrada para esta lista.\n");
        resetColor();
        printf("Crie arquivos .c na pasta core/ para adicionar questoes.\n");
        pausar();
        return 1;
    }

    // Criar opções dinamicamente
    OpcaoMenu* opcoes = (OpcaoMenu*)malloc(sizeof(OpcaoMenu) * numQuestoes);

    for (int i = 0; i < numQuestoes; i++) {
        char* texto = (char*)malloc(50);
        sprintf(texto, "Questao %02d", i + 1);
        opcoes[i].texto = texto;
        opcoes[i].tipo = ACAO_EXECUTAR_FUNCAO;
        opcoes[i].funcao = callbacks[i];
    }

    // Criar título do menu
    char titulo[100];
    sprintf(titulo, "%s - %d questoes disponiveis", obterNomeLista(tipoLista), numQuestoes);

    // Criar e executar o menu
    MenuGenerico* menu = criarMenu(titulo, opcoes, numQuestoes);
    int resultado = 1;
    if (menu) {
        resultado = executarMenu(menu);
        destruirMenu(menu);
    }

    // Liberar memória das strings de texto alocadas
    for (int i = 0; i < numQuestoes; i++) {
        free(opcoes[i].texto);
    }
    free(opcoes);

    return resultado;
}
