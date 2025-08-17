#include <stdio.h>
#include "../headlers/8.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"


int Multip_Rec(int n1, int n2) {
	if (n2 == 0) return 0;
	else return n1 + Multip_Rec(n1, n2 - 1);
}

int mostrarMenuQuestaoRecursividade8(void)
{
    int op;
    do
    {
        limparTela();
        setColor(YELLOW);
        printf("=== Recursividade ===\n");
        printf("=== Executando a Questao 08 ===\n\n");
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
        processarOpcaoQuestaoRecursividade8(op);
    } while (op != 0);
    return (op == 0) ? 0 : 1;
}

void processarOpcaoQuestaoRecursividade8(int op)
{
    int n1 = 5, n2 = 6;

    switch (op)
    {
    case 1:
        printf("Numero 1: %d\nNumero 2: %d\nResultado: %d\n", n1, n2, Multip_Rec(n1, n2));
        pausar();
        break;
    case 2:
        setColor(YELLOW);
        printf("Digite o primeiro numero: ");
        scanf("%d", &n1);
        printf("Digite o segundo numero: ");
        scanf("%d", &n2);
        resetColor();
        if (n2 <= 0) printf("O segundo numero nao pode ser menor ou igual a zero!");
        else printf("Resultado: %d\n", Multip_Rec(n1, n2));
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

void executarQuestaoRecursividade8(void)
{
    mostrarMenuQuestaoRecursividade8();
    ungetc('\n', stdin);
}
