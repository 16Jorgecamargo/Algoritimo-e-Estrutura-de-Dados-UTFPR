#include <stdio.h>
#include <stdlib.h>
#include "../headlers/8.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

void preencherVet(int *v, int n, int op){
    if (n > 0 && op == 0) {
        printf("Digite %d elemento: ", n);
        scanf("%d", &v[0]);
        preencherVet(&v[1], n-1, op);
    }
    else if (n > 0 && op == 1) {
        v[0] = n * 2;
        preencherVet(&v[1], n - 1, op);
    }
}

void imprimeVet(int *v, int n){
    if(n > 0) {
        if(n > 1) printf("%d, ", v[0]);
        else printf("%d", v[0]);
        imprimeVet(v + 1, n - 1);
    }
}

int mostrarMenuQuestaoPonteiros8(void)
{
    int op;
    do
    {
        limparTela();
        setColor(YELLOW);
        printf("=== Ponteiros ===\n");
        printf("=== Executando a Questao 8 ===\n\n");
        resetColor();
        printf("Escolha uma opcao:\n");
        printMenuItem(1, "Executar com numero pre definido");
        printMenuItem(2, "Escolher os caracteres do vetor");
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
            printf("\n\nPressione Enter para continuar...");
            getchar();
            continue;
        }
        resetColor();
        processarOpcaoQuestaoPonteiros8(op);
    } while (op != 0);
    return (op == 0) ? 0 : 1;
}

void processarOpcaoQuestaoPonteiros8(int op)
{
    int n;
    switch (op)
    {
    case 1:
    {
        int *v = malloc(8 * sizeof(int));
        preencherVet(v, 8, 1);
        printf("vetor[8] = {");
        imprimeVet(v, 8);
        printf("}\n");
        free(v);
        pausar();
        break;
    }
    case 2:
    {
        setColor(YELLOW);
        printf("Digite o tamanho do vetor: ");
        scanf("%d", &n);
        resetColor();
        int *vetor = malloc(n * sizeof(int));
        preencherVet(vetor, n, 0);
        printf("\nvetor[%d] = {", n);
        imprimeVet(vetor, n);
        printf("}\n");
        free(vetor);
        pausar();
        break;
    }
    case 0:
        return;
    default:
        setColor(RED);
        printf("Opcao invalida! Digite um numero entre 0 e 2.\n");
        resetColor();
        printf("\n\nPressione Enter para continuar...");
        while (getchar() != '\n');
        getchar();
        limparTela();
        break;
    }
}

void executarQuestaoPonteiros8(void)
{
    mostrarMenuQuestaoPonteiros8();
    ungetc('\n', stdin);
}
