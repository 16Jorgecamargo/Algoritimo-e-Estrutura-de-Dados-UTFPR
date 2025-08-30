#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../../shared/headlers/pilhaDinamica.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"
#include "../headlers/4.h"

PilhaQuestao4 *cria_PilhaQuestao4()
{
    PilhaQuestao4 *pi = (PilhaQuestao4 *)malloc(sizeof(PilhaQuestao4));
    if (pi != NULL) *pi = NULL;
    return pi;
}

void libera_PilhaQuestao4(PilhaQuestao4 *pi)
{
    if (pi != NULL)
    {
        ElemQuestao4 *no;
        while ((*pi) != NULL) { no = *pi; *pi = (*pi)->prox; free(no); }
        free(pi);
    }
}

int insere_PilhaQuestao4(PilhaQuestao4 *pi, int n)
{
    if (pi == NULL) return 0;
    ElemQuestao4 *no;
    no = (ElemQuestao4 *)malloc(sizeof(ElemQuestao4));
    if (no == NULL) return 0;
    no->n = n;
    no->prox = (*pi);
    *pi = no;
    return 1;
}

int tamanho_PilhaQuestao4(PilhaQuestao4 *pi)
{
    if (pi == NULL) return 0;
    int cont = 0;
    ElemQuestao4 *no = *pi;
    while (no != NULL) { cont++; no = no->prox;}
    return cont;
}

void imprime_PilhaQuestao4(PilhaQuestao4 *pi)
{
    if (pi == NULL) return;
    ElemQuestao4 *no = *pi;
    printf("-------------------------------\n");
    while (no != NULL)
    {
        printf("Numero: %d\n", no->n);
        printf("-------------------------------\n");
        no = no->prox;
    }
}

void verificaMMM_PilhaQuestao4(PilhaQuestao4 *pi)
{
    int maior= 0, menor= 0, media= 0;
    if (pi == NULL) return;
    ElemQuestao4 *no = *pi;
    while (no != NULL)
    {
        if (no->n > maior) maior = no->n;
        if (no->n < menor || menor == 0) menor = no->n;
        media += no->n;
        no = no->prox;
    }
    media /= tamanho_PilhaQuestao4(pi);
    printMensagemColoridaFormatted(6,"Maior: %d", maior);
    printMensagemColoridaFormatted(6,"Menor: %d", menor);
    printMensagemColoridaFormatted(6,"Media: %d", media);
}

void executarQuestaoPilhaDinamica4(void) {
    srand((unsigned)time(NULL));
    PilhaQuestao4* pi = cria_PilhaQuestao4();
    printMensagemColorida(6,"Pilha criada com sucesso!");
    printMensagemColoridaFormatted(5,"Tamanho atual: %d\n",tamanho_PilhaQuestao4(pi));
    int n = (rand() % 15) + 1;
    printMensagemColorida(6,"Adicionando quantidade aleatoria de elementos...");
    for (int i = 0; i < n; i++) { n = (rand() % 100) + 1; insere_PilhaQuestao4(pi, n); }
    imprime_PilhaQuestao4(pi);
    printMensagemColoridaFormatted(5,"Tamanho atual: %d\n",tamanho_PilhaQuestao4(pi));
    verificaMMM_PilhaQuestao4(pi);
    libera_PilhaQuestao4(pi);
}
