#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headlers/menuLista.h"
#include "../headlers/menuQuestao.h"
#include "../../shared/headlers/clean.h"
#include "../../shared/headlers/color.h"
#include "../../shared/headlers/colorPrint.h"

#ifdef _WIN32
    #include <io.h>
    #include <direct.h>
    #define ACCESS _access
#else
    #include <unistd.h>
    #define ACCESS access
#endif

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

int mostrarMenuLista(int tipoLista) {
    int opcao;
    int numQuestoes = contarQuestoes(tipoLista);
    
    do {
        limparTela();
        
        setColor(YELLOW);
        printf("=== %s ===\n", obterNomeLista(tipoLista));
        resetColor();
        
        if (numQuestoes > 0) {
            printf("Exercicios disponiveis (%d questoes):\n", numQuestoes);
            for(int i = 1; i <= numQuestoes; i++) {
                char questaoDesc[50];
                sprintf(questaoDesc, "Questao %02d", i);
                printMenuItem(i, questaoDesc);
            }
        } else {
            setColor(RED);
            printf("Nenhuma questao encontrada para esta lista.\n");
            resetColor();
            printf("Crie arquivos .c na pasta core/ para adicionar questoes.\n");
        }
        
        printf("\n");
        setColor(CYAN);
        printf("=== Sistema de Listas de Exercicios ===\n");
        resetColor();
        printf("Digite o numero do exercicio que deseja ou 0 para voltar\n");
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
        int resultado = processarOpcaoLista(tipoLista, opcao, numQuestoes);
        
        if (resultado == 0) {
            return 0;
        }
        
    } while (opcao != 0);
    
    return 1;  
}

int processarOpcaoLista(int tipoLista, int opcao, int numQuestoes) {
    if (opcao == 0) {
        return 1; 
    } else if (opcao >= 1 && opcao <= numQuestoes) {
        int resultado = mostrarMenuQuestao(tipoLista, opcao);
        return resultado;
    } else {
        setColor(RED);
        if (numQuestoes > 0) {
            printf("Opcao invalida! Digite um numero entre 0 e %d.\n", numQuestoes);
        } else {
            printf("Nenhuma questao disponivel! Digite 0 para voltar.\n");
        }
        resetColor();
        printf("Pressione Enter para continuar...");
        while (getchar() != '\n');
        getchar();
        return 1; 
    }
}