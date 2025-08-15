#include <stdio.h>
#include <stdlib.h>
#include "../headlers/menuPrincipal.h"
#include "../headlers/menuLista.h"
#include "../../shared/headlers/clean.h"
#include "../../shared/headlers/color.h"
#include "../../shared/headlers/colorPrint.h"

void mostrarMenuPrincipal(void) {
    int opcao;
    
    do {
        limparTela();
        
        setColor(YELLOW);
        printf("=== Listas de Exercicios Disponiveis ===\n");
        resetColor();
        
        printMenuItem(1, "Recursividade - Exercicios sobre programacao recursiva");
        printMenuItem(2, "Ponteiros - Exercicios sobre manipulacao de ponteiros");
        printMenuItem(3, "Pilha Dinamica - Exercicios sobre implementacao e uso de pilhas dinamicas");
        printMenuItem(4, "Filas - Exercicios sobre implementacao e uso de filas");
        printMenuItem(5, "Listas - Exercicios sobre listas ligadas simples");
        printMenuItem(6, "Listas Duplamente Encadeadas - Exercicios sobre listas duplamente ligadas");
        printMenuItem(7, "Arvores I - Exercicios introdutorios sobre arvores");
        printMenuItem(8, "Arvores Binarias - Exercicios sobre arvores binarias");
        printMenuItem(9, "Arvores AVL - Exercicios sobre arvores AVL balanceadas");
        printMenuItem(10, "Grafos - Exercicios sobre teoria dos grafos e algoritmos");
        printf("\n");
        
        setColor(CYAN);
        printf("=== Sistema de Listas de Exercicios ===\n");
        resetColor();
        printf("Digite o numero da lista que deseja ou 0 para sair\n");
        setColor(YELLOW);
        printf("> ");
        
        if (scanf("%d", &opcao) != 1) {
            setColor(RED);
            printf("Entrada invalida! Digite apenas numeros.\n");
            resetColor();
            while (getchar() != '\n');
            printf("Pressione Enter para continuar...");
            getchar();
            continue;
        }
        
        resetColor();
        processarOpcaoPrincipal(opcao);
        
    } while (opcao != 0);
}

void processarOpcaoPrincipal(int opcao) {
    switch(opcao) {
        case 0:
            setColor(GREEN);
            printf("Encerrando o sistema...\n");
            resetColor();
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            mostrarMenuLista(opcao);
            break;
        default:
            setColor(RED);
            printf("Opcao invalida! Digite um numero entre 0 e 10.\n");
            resetColor();
            printf("Pressione Enter para continuar...");
            while (getchar() != '\n');
            getchar();
            break;
    }
}