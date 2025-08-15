#include <stdio.h>
#include <stdlib.h>
#include "../headlers/5.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

void criarVetor(double vetorReais[], int tamanho)
{   
	for (int i = 0; i < tamanho; i++)
	{
		vetorReais[i] = i * 1.1;
		printf("%-3.1f | ", vetorReais[i]);
	}
	printf("\n\n");
}

void inverterReais(double vetorReais[], int inicio, int fim)
{
	if (inicio < fim)
	{
		double temp = vetorReais[inicio];
		vetorReais[inicio] = vetorReais[fim];
		vetorReais[fim] = temp;
		inverterReais(vetorReais, inicio + 1, fim - 1);
	}
}


int mostrarMenuQuestaoRecursividade5(void)
{
    int op;
    do
    {
        limparTela();
        setColor(YELLOW);
        printf("=== Recursividade ===\n");
        printf("=== Executando a Questao 05 ===\n\n");
        resetColor();
        printf("Escolha uma opcao:\n");
        printMenuItem(1, "Executar com o vetor de 100 numeros reais pre definido");
        printMenuItem(2, "Escolher o tamanho e valores do vetor de numeros reais");
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
        processarOpcaoQuestaoRecursividade5(op);
    } while (op != 0);
    return (op == 0) ? 0 : 1;
}

void processarOpcaoQuestaoRecursividade5(int op)
{
    int tamanho;
    double vetorReais[100];
    
    switch (op)
    {
    case 1:
        criarVetor(vetorReais, 100);
        inverterReais(vetorReais, 0, 99);
        for (int i = 0; i < 100; i++) printf("%-3.1f | ", vetorReais[i]);
        printf("\n");
        pausar();
        break;
    case 2:
        setColor(YELLOW);
        printf("Digite o tamanho do vetor: ");
        scanf("%d", &tamanho);
        double *vetorReais = (double *)malloc(tamanho * sizeof(double));
        printf("Digite os elementos do vetor:\n");
        for (int i = 0; i < tamanho; i++)
        {
            printf("Elemento %d: ", i + 1);
            scanf("%lf", &vetorReais[i]);
        }
        resetColor();
        printf("\nVetor original:\n");
        for (int i = 0; i < tamanho; i++) printf("%-3.1f | ", vetorReais[i]);
        printf("\n\n Vetor invertido:\n");
        inverterReais(vetorReais, 0, tamanho - 1);
        for (int i = 0; i < tamanho; i++) printf("%-3.1f | ", vetorReais[i]);
        printf("\n");
        free(vetorReais);
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

void executarQuestaoRecursividade5(void)
{
    mostrarMenuQuestaoRecursividade5();
    ungetc('\n', stdin);
}
