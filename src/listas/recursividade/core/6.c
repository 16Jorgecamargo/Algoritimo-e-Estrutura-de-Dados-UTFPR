#include <stdio.h>
#include "../headlers/6.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

int MDC(int x, int y) {
	if(y == 0) {
        printf("%2d, %2d |  <--\n", x, y);
        printf("MDC: %d\n", x);
        return x;
    } else {
        printf("%2d, %2d |\n", x, y);
	    return MDC(y, x%y);
    }
}

int mostrarMenuQuestaoRecursividade6(void)
{
    int op;
    do
    {
        limparTela();
        setColor(YELLOW);
        printf("=== Recursividade ===\n");
        printf("=== Executando a Questao 06 ===\n\n");
        resetColor();
        printf("Escolha uma opcao:\n");
        printMenuItem(1, "Executar com numeros pre definidos");
        printMenuItem(2, "Escolher os numeros");
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
        processarOpcaoQuestaoRecursividade6(op);
    } while (op != 0);
    return (op == 0) ? 0 : 1;
}

void processarOpcaoQuestaoRecursividade6(int op)
{
    int x, y;
    switch (op)
    {
    case 1:
        printf("Numero original: 48 e 18\n");
        MDC(48, 18);
        pausar();
        break;
    case 2:
        setColor(YELLOW);
        printf("Digite o primeiro inteiro positivo: ");
        scanf("%d", &x);
        printf("Digite o segundo inteiro positivo: ");
        scanf("%d", &y);
        resetColor();
        printf("Numero original: %2d e %2d\n", x, y);
        MDC(x, y);
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

void executarQuestaoRecursividade6(void)
{
    mostrarMenuQuestaoRecursividade6();
    ungetc('\n', stdin);
}
