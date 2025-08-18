#include <stdio.h>
#include "../headlers/12.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

int fatorialDuplo(int n, int aux) {
    if (n == 1) return aux;
    if (n % 2 == 1) return fatorialDuplo(n - 2, aux * n);
    else return fatorialDuplo(n - 1, aux);
}

int mostrarMenuQuestaoRecursividade12(void)
{
    int op;
    do
    {
        limparTela();
        setColor(YELLOW);
        printf("=== Recursividade ===\n");
        printf("=== Executando a Questao 12 ===\n\n");
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
        processarOpcaoQuestaoRecursividade12(op);
    } while (op != 0);
    return (op == 0) ? 0 : 1;
}

void processarOpcaoQuestaoRecursividade12(int op)
{
    int n;
    switch (op)
    {
    case 1:
        printf("Numero escolhido: 7\n");
        printf("Fatorial duplo de 7: %d\n", fatorialDuplo(7, 1));
        pausar();
        break;
    case 2:
        setColor(YELLOW);
        printf("Digite um numero inteiro: ");
        scanf("%d", &n);
        resetColor();
        printf("Fatorial duplo de %d: %d\n", n, fatorialDuplo(n, 1));
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

void executarQuestaoRecursividade12(void)
{
    mostrarMenuQuestaoRecursividade12();
    ungetc('\n', stdin);
}
