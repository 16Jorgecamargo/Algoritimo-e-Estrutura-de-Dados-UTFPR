#include <stdio.h>
#include <stdlib.h>
#include "../../../shared/headlers/pilhaDinamica.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"
#include "../headlers/2.h"

int popN(Pilha *pi, int n)
{
    if (pi == NULL) { printf("Pilha nao existe.\n"); return 0; }
    if ((*pi) == NULL) { printf("Pilha esta vazia.\n"); return 0; } 
    for (int i = 0; i < n; i++)
    {
        if ((*pi) == NULL) { printf("Pilha esvaziou antes de remover %d elementos.\n", n); return 0; }
        else
        {
            Elem *no = *pi;
            *pi = no->prox;
            free(no);
            printf("%d Elemento removido da pilha.\n", i+1);
        }
    }
    return 1;
}

void pushN(Pilha *pi, struct aluno al[])
{
    if (pi == NULL) return;
    for (int i = 0; i < 4; i++)
    {
        Elem *no = malloc(sizeof(Elem));
        if (no == NULL) return;
        no->dados = al[i]; no->prox = (*pi);
        *pi = no;
    }
}

void executarQuestaoPilhaDinamica2(void)
{
    struct aluno a[4] = 
    {
        {2,"Andre",9.5,7.8,8.5},{4,"Ricardo",7.5,8.7,6.8},{1,"Bianca",9.7,6.7,8.4},{3,"Ana",5.7,6.1,7.4}
    };
    Pilha* pi = cria_Pilha();
    printf("Tamanho atual: %d\n\n",tamanho_Pilha(pi));
    printf("Adicionando 4 elementos...\n");
    pushN(pi,a);
    imprime_Pilha(pi);
    printf("Tamanho atual: %d\n\n",tamanho_Pilha(pi));
    int n;
    setColor(YELLOW);
    printf("Quantos elementos deseja remover? ");
    scanf("%d", &n);
    resetColor();
    printf("Removendo %d elementos...\n", n);
    popN(pi, n);
    printf("\n\n");
    imprime_Pilha(pi);
    printf("Tamanho atual: %d\n\n",tamanho_Pilha(pi));
    libera_Pilha(pi);
}
