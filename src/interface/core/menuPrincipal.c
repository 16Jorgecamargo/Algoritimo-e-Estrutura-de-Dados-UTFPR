#include <stdio.h>
#include <stdlib.h>
#include "../headlers/menuPrincipal.h"
#include "../headlers/menuLista.h"
#include "../../shared/headlers/clean.h"
#include "../../shared/headlers/color.h"
#include "../../shared/headlers/colorPrint.h"
#include "../../shared/headlers/menuGenerico.h"

// Funções de callback para cada lista
int abrirRecursividade(void) { return mostrarMenuLista(1); }
int abrirPonteiros(void) { return mostrarMenuLista(2); }
int abrirPilhaDinamica(void) { return mostrarMenuLista(3); }
int abrirFilas(void) { return mostrarMenuLista(4); }
int abrirListas(void) { return mostrarMenuLista(5); }
int abrirListasDuplas(void) { return mostrarMenuLista(6); }
int abrirArvoresI(void) { return mostrarMenuLista(7); }
int abrirArvoresBinarias(void) { return mostrarMenuLista(8); }
int abrirArvoresAVL(void) { return mostrarMenuLista(9); }
int abrirGrafos(void) { return mostrarMenuLista(10); }

void mostrarMenuPrincipal(void) {
    // Definir opções do menu principal
    OpcaoMenu opcoes[] = {
        {"Recursividade - Exercicios sobre programacao recursiva", ACAO_EXECUTAR_FUNCAO, abrirRecursividade},
        {"Ponteiros - Exercicios sobre manipulacao de ponteiros", ACAO_EXECUTAR_FUNCAO, abrirPonteiros},
        {"Pilha Dinamica - Exercicios sobre implementacao e uso de pilhas dinamicas", ACAO_EXECUTAR_FUNCAO, abrirPilhaDinamica},
        {"Filas - Exercicios sobre implementacao e uso de filas", ACAO_EXECUTAR_FUNCAO, abrirFilas},
        {"Listas - Exercicios sobre listas ligadas simples", ACAO_EXECUTAR_FUNCAO, abrirListas},
        {"Listas Duplamente Encadeadas - Exercicios sobre listas duplamente ligadas", ACAO_EXECUTAR_FUNCAO, abrirListasDuplas},
        {"Arvores I - Exercicios introdutorios sobre arvores", ACAO_EXECUTAR_FUNCAO, abrirArvoresI},
        {"Arvores Binarias - Exercicios sobre arvores binarias", ACAO_EXECUTAR_FUNCAO, abrirArvoresBinarias},
        {"Arvores AVL - Exercicios sobre arvores AVL balanceadas", ACAO_EXECUTAR_FUNCAO, abrirArvoresAVL},
        {"Grafos - Exercicios sobre teoria dos grafos e algoritmos", ACAO_EXECUTAR_FUNCAO, abrirGrafos}
    };

    // Criar e executar o menu
    MenuGenerico* menu = criarMenu("Listas de Exercicios Disponiveis", opcoes, 10);
    if (menu) {
        executarMenu(menu);
        destruirMenu(menu);
    }
}

