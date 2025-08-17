#include <stdio.h>
#include "../headlers/9.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"


void ocorrenciaParCrescente(int n, int aux) {
    if (aux > n) return;
	if (aux%2 == 0) printf("%d ", aux);
    ocorrenciaParCrescente(n, aux + 1);
}

int mostrarMenuQuestaoRecursividade9(void)
{
    int op;
    do
    {
        limparTela();
        setColor(YELLOW);
        printf("=== Recursividade ===\n");
        printf("=== Executando a Questao 09 ===\n\n");
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
        processarOpcaoQuestaoRecursividade9(op);
    } while (op != 0);
    return (op == 0) ? 0 : 1;
}

void processarOpcaoQuestaoRecursividade9(int op)
{
    int n;
    switch (op)
    {
    case 1:
        printf("Numeros escolhido: 10\n");
        printf("Numeros pares em ordem crescente: ");
        ocorrenciaParCrescente(10, 0);
        pausar();
        break;
    case 2:
        setColor(YELLOW);
        printf("Digite um numero inteiro: ");
        scanf("%d", &n);
        resetColor();
        if (n < 0 ) printf("O numero deve ser um inteiro positivo!");
        else { 
            printf("Numeros pares em ordem crescente: ");
            ocorrenciaParCrescente(n, 0);
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

void executarQuestaoRecursividade9(void)
{
    mostrarMenuQuestaoRecursividade9();
    ungetc('\n', stdin);
}
