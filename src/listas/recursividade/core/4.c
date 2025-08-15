#include <stdio.h>
#include "../headlers/4.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

int potencia(int k, int n)
{
	if (n == 0) return 1;
	else return k * potencia(k, n - 1);
}

int mostrarMenuQuestaoRecursividade4(void)
{
    int op;
    do
    {
        limparTela();
        setColor(YELLOW);
        printf("=== Recursividade ===\n");
        printf("=== Executando a Questao 04 ===\n\n");
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
        processarOpcaoQuestaoRecursividade4(op);
    } while (op != 0);
    return (op == 0) ? 0 : 1;
}

void processarOpcaoQuestaoRecursividade4(int op)
{
    int k, n;
    switch (op)
    {
    case 1:
        printf("Numero original: 5 e 3\n");
        printf("Potencia: %d\n", potencia(5, 3));
        pausar();
        break;
    case 2:
        setColor(YELLOW);
        printf("Digite um numero inteiro positivo: ");
        scanf("%d", &k);
        printf("Digite um numero inteiro positivo: ");
        scanf("%d", &n);
        resetColor();
        printf("Numero original: %d e %d\n", k, n);
        printf("Potencia: %d\n", potencia(k, n));
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

void executarQuestaoRecursividade4(void)
{
    mostrarMenuQuestaoRecursividade4();
    ungetc('\n', stdin);
}
