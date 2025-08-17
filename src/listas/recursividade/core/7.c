#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../headlers/7.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

void criarVetorQuestao7(int v[], int n) {
    for (int i = 0; i < n; i++) v[i] = (rand() % 5) + 1;

}

int ocorrencia(int n, const int *v, int tamanho) {
    if (tamanho == 0) return 0;
    return (v[0] == n) + ocorrencia(n, v + 1, tamanho - 1);
}

int mostrarMenuQuestaoRecursividade7(void)
{
    int op;
    do
    {
        limparTela();
        setColor(YELLOW);
        printf("=== Recursividade ===\n");
        printf("=== Executando a Questao 07 ===\n\n");
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
        processarOpcaoQuestaoRecursividade7(op);
    } while (op != 0);
    return (op == 0) ? 0 : 1;
}

void processarOpcaoQuestaoRecursividade7(int op)
{
    int ocorrenciaNumero = (rand() % 5) + 1;
    int tamanho = 10;
    int *vetorOcorrencia = malloc(tamanho * sizeof(int));

    switch (op)
    {
    case 1:
        srand((unsigned)time(NULL));
        criarVetorQuestao7(vetorOcorrencia, tamanho);
        printf("Vetor original: [ ");
	    for (int i = 0; i < tamanho ; i++) printf("%d ", vetorOcorrencia[i]);
	    printf("]\nNumero procurado: %d\n", ocorrenciaNumero);
	    printf("Total encontrado: %d\n", ocorrencia(ocorrenciaNumero, vetorOcorrencia, tamanho));
        free(vetorOcorrencia);
        pausar();
        break;
    case 2:
        setColor(YELLOW);
        printf("Digite o tamanho do vetor: ");
        scanf("%d", &tamanho);
        printf("Digite os elementos do vetor:\n");
        for (int i = 0; i < tamanho; i++)
        {
            printf("Elemento %d: ", i + 1);
            scanf("%d", &vetorOcorrencia[i]);
        }
        printf("Digite o numero que deseja procurar: ");
        scanf("%d", &ocorrenciaNumero);
        resetColor();
        printf("\nVetor original: [ ");
        for (int i = 0; i < tamanho; i++) printf("%d ", vetorOcorrencia[i]);
        printf("]\nNumero procurado: %d\n", ocorrenciaNumero);
        printf("Total encontrado: %d\n\n", ocorrencia(ocorrenciaNumero, vetorOcorrencia, tamanho));
        free(vetorOcorrencia);
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

void executarQuestaoRecursividade7(void)
{
    mostrarMenuQuestaoRecursividade7();
    ungetc('\n', stdin);
}

