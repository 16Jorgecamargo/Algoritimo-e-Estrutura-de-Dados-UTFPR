#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../headlers/5.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"


int inverte_vetor(int *v1, int *v2, int n)
{
    printf("Vetor original: {");
    for (int i = 0; i < n; i++) {
        v1[i] = (rand() % 20) + 1; 
        printf("%d", v1[i]);
        if (i < n - 1) printf(", ");
    }
    printf("}\n");
    printf("Vetor invertido: {");
    for (int i = 0; i < n; i++) {
        v2[i] = v1[n - 1 - i];
        printf("%d", v2[i]);
        if (i < n - 1) printf(", ");
    }
    printf("}\n");
    int aux = v1[0]; 
    for (int i = 1; i < n; i++) {
        if (v1[i] > aux) aux = v1[i];
    }       
    printf("O maior numero do vetor: %d\n", aux);

    return 0;
}

int mostrarMenuQuestaoPonteiros5(void)
{
    int op;
    do
    {
        limparTela();
        setColor(YELLOW);
        printf("=== Ponteiros ===\n");
        printf("=== Executando a Questao 5 ===\n\n");
        resetColor();
        printf("Escolha uma opcao:\n");
        printMenuItem(1, "Executar com numero pre definido");
        printMenuItem(2, "Escolher o tamanho do vetor");
        printMenuItem(0, "Voltar");
        setColor(YELLOW);
        printf("> ");

        if (scanf("%d", &op) != 1)
        {
            setColor(RED);
            printf("Entrada invalida! Digite apenas numeros.\n");
            resetColor();
            while (getchar() != '\n')
                ;
            printf("\n\nPressione Enter para continuar...");
            getchar();
            continue;
        }
        resetColor();
        processarOpcaoQuestaoPonteiros5(op);
    } while (op != 0);
    return (op == 0) ? 0 : 1;
}

void processarOpcaoQuestaoPonteiros5(int op)
{
    int n = (rand() % 25) + 1, *v1, *v2;
    srand((unsigned)time(NULL));
    switch (op)
    {
    case 1:
        printf("Tamanho do vetor pre definido: %d\n", n);
        v1 = (int*)malloc(n * sizeof(int));
        v2 = (int*)malloc(n * sizeof(int));
        inverte_vetor(v1, v2, n);
        free(v1);
        free(v2);
        pausar();
        break;
    case 2:
        setColor(YELLOW);
        printf("Digite um tamanho para o vetor (numero inteiro): ");
        scanf("%d", &n);
        v1 = (int*)malloc(n * sizeof(int));
        v2 = (int*)malloc(n * sizeof(int));
        inverte_vetor(v1, v2, n);
        free(v1);
        free(v2);
        resetColor();
        pausar();
        break;
    case 0:
        return;
    default:
        setColor(RED);
        printf("Opcao invalida! Digite um numero entre 0 e 2.\n");
        resetColor();
        printf("\n\nPressione Enter para continuar...");
        while (getchar() != '\n');
        getchar();
        limparTela();
        break;
    }
}

void executarQuestaoPonteiros5(void)
{
    mostrarMenuQuestaoPonteiros5();
    ungetc('\n', stdin);
}
