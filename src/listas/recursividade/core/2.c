#include <stdio.h>
#include "../headlers/2.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"
#include "../../../shared/headlers/color.h"

int somarVetorInteiro(int *n, int tamanho)
{
    if (tamanho == 0) return 0;
    else return n[0] + somarVetorInteiro(&n[1], tamanho - 1);
}

int mostrarMenuQuestaoRecursividade2(void)
{
    int op;
    do
    {
        limparTela();
        setColor(YELLOW);
        printf("=== Recursividade ===\n");
        printf("=== Executando a Questao 02 ===\n\n");
        resetColor();
        printf("Escolha uma opcao:\n");
        printMenuItem(1, "Executar com vetor pre definido");
        printMenuItem(2, "Escolher vetor");
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
        processarOpcaoQuestaoRecursividade2(op);
    } while (op != 0);
    return (op == 0) ? 0 : 1;
}

void processarOpcaoQuestaoRecursividade2(int op)
{
    int vetorInt[] = {1, 2, 3, 4, 7, 9, 10};
    int tamanho = sizeof(vetorInt) / sizeof(vetorInt[0]);
    int vetorIntCase2[100];
    int tamanhoCase2;

    switch (op)
    {
    case 1:
        printf("Vetor original: {1, 2, 3, 4, 7, 9, 10}\n");
        printf("Resultado: %d\n", somarVetorInteiro(&vetorInt[0], tamanho));
        pausar();
        limparTela();
        break;
    case 2:
        setColor(YELLOW);
        printf("Digite o tamanho do vetor: ");
        scanf("%d", &tamanhoCase2);
        printf("Digite os elementos do vetor:\n");
        resetColor();
        for (int i = 0; i < tamanhoCase2; i++)
        {
            scanf("%d", &vetorIntCase2[i]);
        }
        printf("Vetor original: {");
        for (int i = 0; i < tamanhoCase2; i++)
        {
            printf("%d", vetorIntCase2[i]);
            if (i < tamanhoCase2 - 1)
            {
                printf(", ");
            }
        }
        printf("}\n");
        printf("Resultado: %d\n", somarVetorInteiro(&vetorIntCase2[0], tamanhoCase2));
        pausar();
        limparTela();
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
void executarQuestaoRecursividade2(void)
{
    mostrarMenuQuestaoRecursividade2();
    ungetc('\n', stdin);
}
