#include <stdio.h>
#include "../headlers/1.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

void inverterNumero(int numero) {
	if (numero > 0)
	{
		printf("%d", numero % 10);
		inverterNumero(numero / 10);
	}
}


int mostrarMenuQuestaoRecursividade1(void)
{
    int op;
    do
    {
        limparTela();
        setColor(YELLOW);
        printf("=== Recursividade ===\n");
        printf("=== Executando a Questao 01 ===\n\n");
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
        processarOpcaoQuestaoRecursividade1(op);
    } while (op != 0);
    return (op == 0) ? 0 : 1;
}

void processarOpcaoQuestaoRecursividade1(int op)
{
    int numero;
    switch (op)
    {
    case 1:
        printf("Numero original: 12345\n");
        printf("Numero invertido: ");
        inverterNumero(12345);
        printf("\n");
        pausar();
        break;
    case 2:
        setColor(YELLOW);
        printf("Digite um numero inteiro positivo: ");
        scanf("%d", &numero);
        resetColor();
        printf("Numero original: %d\n", numero);
        printf("Numero invertido: ");
        inverterNumero(numero);
        printf("\n");
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
void executarQuestaoRecursividade1(void)
{
    mostrarMenuQuestaoRecursividade1();
    ungetc('\n', stdin);
}
