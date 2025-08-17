#include <stdio.h>
#include "../headlers/10.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

void numerosNaturais(int n, int aux)
{
    if(aux <= n) {
        printf("%d ", aux); 
        numerosNaturais(n, aux + 1);
    }
}

int mostrarMenuQuestaoRecursividade10(void)
{
    int op;
    do
    {
        limparTela();
        setColor(YELLOW);
        printf("=== Recursividade ===\n");
        printf("=== Executando a Questao 10 ===\n\n");
        resetColor();
        printf("Escolha uma opcao:\n");
        printMenuItem(1, "Executar com numero pre definido");
        printMenuItem(2, "Escolher o numero");
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
            printf("Pressione Enter para continuar...");
            getchar();
            continue;
        }
        resetColor();
        processarOpcaoQuestaoRecursividade10(op);
    } while (op != 0);
    return (op == 0) ? 0 : 1;
}

void processarOpcaoQuestaoRecursividade10(int op)
{
    int n;
    switch (op)
    {
    case 1:
        printf("Numeros escolhido: 15\n");
        printf("Numeros naturais: ");
        numerosNaturais(15, 0);
        pausar();
        break;
    case 2:
        setColor(YELLOW);
        printf("Digite um numero inteiro: ");
        scanf("%d", &n);
        resetColor();
        if (n < 0 ) printf("O numero deve ser um inteiro positivo!");
        else { 
            printf("Numeros naturais: ");
            numerosNaturais(n, 0);
        }
        pausar();
        break;
    case 0:
        return;
    default:
        setColor(RED);
        printf("Opcao invalida! Digite um numero entre 0 e 2.\n");
        resetColor();
        printf("Pressione Enter para continuar...");
        while (getchar() != '\n');
        getchar();
        limparTela();
        break;
    }
}

void executarQuestaoRecursividade10(void)
{
    mostrarMenuQuestaoRecursividade10();
    ungetc('\n', stdin);
}
