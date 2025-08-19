#include <stdio.h>
#include <stdlib.h>
#include "../headlers/6.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

void imprime_inv(char *cptr){
    if (cptr[0] != '\0') {
        imprime_inv(cptr + 1);
        printf("%c", cptr[0]);
    }
}

int mostrarMenuQuestaoPonteiros6(void)
{
    int op;
    do
    {
        limparTela();
        setColor(YELLOW);
        printf("=== Ponteiros ===\n");
        printf("=== Executando a Questao 6 ===\n\n");
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
        processarOpcaoQuestaoPonteiros6(op);
    } while (op != 0);
    return (op == 0) ? 0 : 1;
}

void processarOpcaoQuestaoPonteiros6(int op)
{
    char s[10] = "abcde";
    char* cptr = s;
    switch (op)
    {
    case 1:
        printf("\nOrdem original: abcde\nOrdem inversa: ");
        imprime_inv(cptr);
        pausar();
        break;
    case 2:
        setColor(YELLOW);
        printf("Digite ate 10 caracteres: ");
        while(getchar() != '\n');
        int i;
        for (i = 0; i < 9; i++) scanf("%c", &cptr[i]);
        resetColor();
        cptr[i] = '\0';
        printf("\nOrdem original: ");
        for(int i = 0; cptr[i] != '\0'; i++) printf("%c", cptr[i]);
        printf("\nOrdem inversa: ");
        imprime_inv(cptr);
        pausar();
        break;
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

void executarQuestaoPonteiros6(void)
{
    mostrarMenuQuestaoPonteiros6();
    ungetc('\n', stdin);
}
