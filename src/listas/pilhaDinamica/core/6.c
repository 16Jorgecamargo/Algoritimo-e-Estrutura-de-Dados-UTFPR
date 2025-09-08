#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../shared/headlers/pilhaDinamica.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"
#include "../headlers/6.h"

PilhaQuestao6 *cria_PilhaQuestao6()
{
    PilhaQuestao6 *pi = (PilhaQuestao6 *)malloc(sizeof(PilhaQuestao6));
    if (pi != NULL) *pi = NULL;
    return pi;
}

void libera_PilhaQuestao6(PilhaQuestao6 *pi)
{
    if (pi != NULL)
    {
        ElemQuestao6 *no;
        while ((*pi) != NULL) { no = *pi; *pi = (*pi)->prox; free(no); }
        free(pi);
    }
}

int insere_PilhaQuestao6(PilhaQuestao6 *pi, char caractere)
{
    if (pi == NULL) return 0;
    ElemQuestao6 *no;
    no = (ElemQuestao6 *)malloc(sizeof(ElemQuestao6));
    if (no == NULL) return 0;
    no->caracter = caractere;
    no->prox = (*pi);
    *pi = no;
    return 1;
}

int tamanho_PilhaQuestao6(PilhaQuestao6 *pi)
{
    if (pi == NULL) return 0;
    int cont = 0;
    ElemQuestao6 *no = *pi;
    while (no != NULL) { cont++; no = no->prox;}
    return cont;
}

void imprime_PilhaQuestao6(PilhaQuestao6 *pi)
{
    if (pi == NULL) return;
    ElemQuestao6 *no = *pi;
    while (no != NULL)
    {
        printf("%c", no->caracter);
        no = no->prox;
    }
}

void pilha_CheckQuestao6(PilhaQuestao6* p) {
    if (p == NULL) return;
    
    char *stringOriginal = (char*)malloc(1000 * sizeof(char));
    if (stringOriginal == NULL) return;
    
    int indice = 0;
    ElemQuestao6* atual = *p;
    
    int tamanhoTotal = tamanho_PilhaQuestao6(p);
    char *temp = (char*)malloc(tamanhoTotal * sizeof(char));
    if (temp == NULL) {
        free(stringOriginal);
        return;
    }
    
    atual = *p;
    int i = 0;
    while (atual != NULL) {
        temp[i] = atual->caracter;
        atual = atual->prox;
        i++;
    }
    
    for (int j = tamanhoTotal - 1; j >= 0; j--) {
        char c = temp[j];
        if (c != ' ' && c != '.') {
            stringOriginal[indice] = c;
            indice++;
        }
    }
    stringOriginal[indice] = '\0';
    
    int palindromo = 1;
    int inicio = 0;
    int fim = indice - 1;
    
    while (inicio < fim) {
        if (stringOriginal[inicio] != stringOriginal[fim]) {
            palindromo = 0;
            break;
        }
        inicio++;
        fim--;
    }
    
    free(temp);
    free(stringOriginal);
    palindromo ? printMensagemColorida(2, "um palindromo!") : printMensagemColorida(1, "nao palindromo!");
}

void executarQuestaoPilhaDinamica6(void) {
    PilhaQuestao6* pi = cria_PilhaQuestao6();
    printMensagemColorida(6,"Pilha criada com sucesso!");
    printMensagemColoridaFormatted(5,"Tamanho atual: %d\n",tamanho_PilhaQuestao6(pi));
    
    printMensagemColorida(3, "Digite uma mensagem ou palavra: ");
    
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
    while ((c = getchar()) != '\n' && c != EOF) {
        insere_PilhaQuestao6(pi, c);
    }
    
    printMensagemColorida(6,"Mensagem invertida: ");
    imprime_PilhaQuestao6(pi);
    printf("\n");
    printMensagemColorida(6,"Testando se eh palindromo: \n");
    pilha_CheckQuestao6(pi);
    printMensagemColoridaFormatted(5,"Tamanho atual: %d\n",tamanho_PilhaQuestao6(pi));
    libera_PilhaQuestao6(pi);
    ungetc('\n', stdin);
}
