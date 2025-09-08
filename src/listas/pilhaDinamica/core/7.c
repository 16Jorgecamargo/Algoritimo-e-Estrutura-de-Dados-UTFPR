#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../../shared/headlers/pilhaDinamica.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"
#include "../headlers/7.h"

PilhaQuestao7 *cria_PilhaQuestao7()
{
    PilhaQuestao7 *pi = (PilhaQuestao7 *)malloc(sizeof(PilhaQuestao7));
    if (pi != NULL) *pi = NULL;
    return pi;
}

void libera_PilhaQuestao7(PilhaQuestao7 *pi)
{
    if (pi != NULL)
    {
        ElemQuestao7 *no;
        while ((*pi) != NULL) { no = *pi; *pi = (*pi)->prox; free(no); }
        free(pi);
    }
}

int insere_PilhaQuestao7(PilhaQuestao7 *pi, int id)
{
    if (pi == NULL) return 0;
    ElemQuestao7 *no;
    no = (ElemQuestao7 *)malloc(sizeof(ElemQuestao7));
    if (no == NULL) return 0;
    no->id = id;
    no->valor = (rand() % 100) + 1;
    no->prox = (*pi);
    *pi = no;
    return 1;
}

int tamanho_PilhaQuestao7(PilhaQuestao7 *pi)
{
    if (pi == NULL) return 0;
    int cont = 0;
    ElemQuestao7 *no = *pi;
    while (no != NULL) { cont++; no = no->prox;}
    return cont;
}

void imprime_PilhaQuestao7(PilhaQuestao7 *pi)
{
    if (pi == NULL) return;
    ElemQuestao7 *no = *pi;
    while (no != NULL)
    {
        printf("elemento da pilha [ID: %d - Valor: %d]\n", no->id, no->valor);
        no = no->prox;
    }
}

void imprime_PilhaQuestao7_Checagem(PilhaQuestao7 *pi)
{
    if (pi == NULL) return;
    ElemQuestao7 *no = *pi;
    while (no != NULL)
    {
        if (no->id % 2 != 0 && no->valor % 2 == 0)
        {
            printf("elemento da pilha [ID: %d - Valor: %d]\n", no->id, no->valor);
        }
        no = no->prox;
    }
}

void executarQuestaoPilhaDinamica7(void) {
    srand((unsigned)time(NULL));
    PilhaQuestao7* pi = cria_PilhaQuestao7();
    printMensagemColorida(6,"Pilha criada com sucesso!");
    printMensagemColoridaFormatted(5,"Tamanho atual: %d\n",tamanho_PilhaQuestao7(pi));

    int n = 10;
    printMensagemColoridaFormatted(3, "Criando pilha com %d elementos", n);
    for (int i = 0; i < n; i++) insere_PilhaQuestao7(pi, i);
    printMensagemColorida(6,"Pilha total: ");
    imprime_PilhaQuestao7(pi);
    printf("\n");
    printMensagemColorida(6,"Pilha criada com sucesso!");

    printMensagemColorida(6,"Pilha com id elemento impar e valor pares:");
    imprime_PilhaQuestao7_Checagem(pi);
    libera_PilhaQuestao7(pi);
}
