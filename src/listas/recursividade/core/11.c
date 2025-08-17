#include <stdio.h>
#include "../headlers/11.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"


void ocorrenciaParDecrescente(int n) {
    if (n < 0) return;
	if (n%2 == 0) printf("%d ", n);
    ocorrenciaParDecrescente(n - 1);
}

int mostrarMenuQuestaoRecursividade11(void)
{
    int op;
    do
    {
        limparTela();
        setColor(YELLOW);
        printf("=== Recursividade ===\n");
        printf("=== Executando a Questao 11 ===\n\n");
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
        processarOpcaoQuestaoRecursividade11(op);
    } while (op != 0);
    return (op == 0) ? 0 : 1;
}

void processarOpcaoQuestaoRecursividade11(int op)
{
    int n;
    switch (op)
    {
    case 1:
        printf("Numeros escolhido: 10\n");
        printf("Numeros pares em ordem decrescente: ");
        ocorrenciaParDecrescente(10);
        pausar();
        break;
    case 2:
        setColor(YELLOW);
        printf("Digite um numero inteiro: ");
        scanf("%d", &n);
        resetColor();
        if (n < 0 || n % 2 != 0) printf("\nO numero deve ser um inteiro par positivo!");
        else {
            printf("Numeros pares em ordem decrescente: ");
            ocorrenciaParDecrescente(n);
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

void executarQuestaoRecursividade11(void)
{
    mostrarMenuQuestaoRecursividade11();
    ungetc('\n', stdin);
}
