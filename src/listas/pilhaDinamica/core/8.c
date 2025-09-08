#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headlers/8.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

PilhaQuestao8 *cria_PilhaQuestao8()
{
    PilhaQuestao8 *pi = (PilhaQuestao8 *)malloc(sizeof(PilhaQuestao8));
    if (pi != NULL) *pi = NULL;
    return pi;
}

void libera_PilhaQuestao8(PilhaQuestao8 *pi)
{
    if (pi != NULL)
    {
        ElemQuestao8 *no;
        while ((*pi) != NULL) { no = *pi; *pi = (*pi)->prox; free(no); }
        free(pi);
    }
}

int insere_PilhaQuestao8(PilhaQuestao8 *pi, char c)
{
    if (pi == NULL) return 0;
    ElemQuestao8 *no;
    no = (ElemQuestao8 *)malloc(sizeof(ElemQuestao8));
    if (no == NULL) return 0;
    no->caractere = c;
    no->prox = (*pi);
    *pi = no;
    return 1;
}

int remove_Elemento_PilhaQuestao8(PilhaQuestao8 *pi, char *c)
{
    if (pi == NULL || (*pi) == NULL) return 0;
    ElemQuestao8 *no = *pi;
    *c = no->caractere;
    *pi = no->prox;
    free(no);
    return 1;
}

int verifica_padrao_xCy(PilhaQuestao8 *pi, char *string)
{
    int i = 0;
    if (!pi) return 0;

    while (string[i] != '\0' && string[i] != 'C')
    {
        if (string[i] == 'A' || string[i] == 'B') insere_PilhaQuestao8(pi, string[i]);
        else if (string[i] != ' ') return 0;
        i++;
    }

    if (string[i] != 'C') return 0;
    i++; 
    
    while (string[i] != '\0')
    {
        if (string[i] == 'A' || string[i] == 'B')
        {
            char c;
            if (!remove_Elemento_PilhaQuestao8(pi, &c) || c != string[i]) return 0;
        }
        else if (string[i] != ' ') return 0;
        i++;
    }
    
    return (*pi) == NULL;
}

void executarQuestaoPilhaDinamica8(void) 
{    
    char string[100];
    PilhaQuestao8 *pilha = cria_PilhaQuestao8();
    printMensagemColorida(3, "Digite uma string no formato 'x C y' (onde x e y contem apenas A e B).\n Exemplo: ABABBA C BABAAB");
    printf("Digite: ");
    scanf(" %s", string);
    int len = strlen(string);
    if (len > 0 && string[len-1] == '\n') string[len-1] = '\0';
    
    if (verifica_padrao_xCy(pilha, string)) printMensagemColorida(2, "\nSEGUE o padrao xCy"); 
    else printMensagemColorida(1, "\nNAO SEGUE o padrao xCy");
    
    libera_PilhaQuestao8(pilha);
}
