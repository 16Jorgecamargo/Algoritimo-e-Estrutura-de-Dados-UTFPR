#include <stdio.h>
#include <stdlib.h>
#include "../headlers/4.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"


void criaVetor(int n, int* v) {
    printf("Vetor[%d] = {", n);
	for (int i = 0; i < n; i++) {
		v[i] = i+1;
        if (i == n - 1) printf("%d}\n", v[i]);
        else printf("%d, ", v[i]);
	}
}

int mostrarMenuQuestaoPonteiros4(void)
{
    int op;
    do
    {
        limparTela();
        setColor(YELLOW);
        printf("=== Ponteiros ===\n");
        printf("=== Executando a Questao 4 ===\n\n");
        resetColor();
        printf("Escolha uma opcao:\n");
        printMenuItem(1, "Executar com numero pre definido");
        printMenuItem(2, "Escolher o tamanho do vetor");
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
        processarOpcaoQuestaoPonteiros4(op);
    } while (op != 0);
    return (op == 0) ? 0 : 1;
}

void processarOpcaoQuestaoPonteiros4(int op)
{
    int n = 10, *v;
    
    switch (op)
    {
    case 1:
        printf("Tamanho do vetor pre definido: %d\n", n);
        v = (int*)malloc(n * sizeof(int));
        criaVetor(n, v);
        free(v);
        pausar();
        break;
    case 2:
        setColor(YELLOW);
        printf("Digite um tamanho para o vetor (numero inteiro): ");
        scanf("%d", &n);
        v = (int*)malloc(n * sizeof(int));
        criaVetor(n, v);
        free(v);
        resetColor();
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

void executarQuestaoPonteiros4(void)
{
    mostrarMenuQuestaoPonteiros4();
    ungetc('\n', stdin);
}
