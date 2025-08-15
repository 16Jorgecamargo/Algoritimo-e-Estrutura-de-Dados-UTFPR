#include <stdio.h>
#include "../headlers/3.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

int somatorio(int n)
{
	if (n == 0) return 0;
	else return n + somatorio(n - 1);
}

int mostrarMenuQuestaoRecursividade3(void)
{
    int op;
    do
    {
        limparTela();
        setColor(YELLOW);
        printf("=== Recursividade ===\n");
        printf("=== Executando a Questao 03 ===\n\n");
        resetColor();
        printf("Escolha uma opcao:\n");
        printMenuItem(1, "Executar com um numero pre definido");
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
        processarOpcaoQuestaoRecursividade3(op);
    } while (op != 0);
    return (op == 0) ? 0 : 1;
}

void processarOpcaoQuestaoRecursividade3(int op)
{
    int numero;
    switch (op)
    {
    case 1:
        printf("Numero original: 30\n");
        printf("Soma dos digitos: %d\n", somatorio(30));
        pausar();
        break;
    case 2:
        setColor(YELLOW);
        printf("Digite um numero inteiro positivo: ");
        scanf("%d", &numero);
        resetColor();
        printf("Numero original: %d\n", numero);
        printf("Soma dos digitos: %d\n", somatorio(numero));
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

void executarQuestaoRecursividade3(void)
{
    mostrarMenuQuestaoRecursividade3();
    ungetc('\n', stdin);
}
