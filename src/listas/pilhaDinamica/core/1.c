#include <stdio.h>
#include <stdlib.h>
#include "../../../shared/headlers/pilhaDinamica.h"
#include "../headlers/1.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

void pop2(Pilha *pi)
{
    if (pi == NULL) return; // pilha nao existe
    if ((*pi) == NULL) return; // pilha vazia
    for (int i = 0; i < 2; i++)
    {
        Elem *no = *pi;
        *pi = no->prox;
        free(no);
    }
}

void push2(Pilha *pi, struct aluno al[])
{
    if (pi == NULL) return; // pilha nao existe
    for (int i = 0; i < 2; i++)
    {
        Elem *no = malloc(sizeof(Elem));
        if (no == NULL) return; // falha na alocação
        no->dados = al[i]; no->prox = (*pi);
        *pi = no;
    }
}

void executarQuestaoPilhaDinamica1(void)
{
    struct aluno a[4] = 
    {
        {2,"Andre",9.5,7.8,8.5},{4,"Ricardo",7.5,8.7,6.8},{1,"Bianca",9.7,6.7,8.4},{3,"Ana",5.7,6.1,7.4}
    };
    Pilha* pi = cria_Pilha();
    printf("Tamanho atual: %d\n\n",tamanho_Pilha(pi));
    printf("Adicionando 2 elementos...\n");
    push2(pi,a);
    imprime_Pilha(pi);
    printf("Tamanho atual: %d\n\n",tamanho_Pilha(pi));
    printf("Removendo dois elementos...\n");
    pop2(pi);
    imprime_Pilha(pi);
    printf("Tamanho atual: %d\n\n",tamanho_Pilha(pi));
    libera_Pilha(pi);
}
