#include <stdio.h>
#include <stdlib.h>
#include "../../../shared/headlers/pilhaDinamica.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"
#include "../headlers/3.h"

Pilha *pilha_copia (Pilha* p) {
    if (p == NULL) return NULL;
    Pilha* copia = cria_Pilha();
    if (copia == NULL) return NULL;
    Pilha* aux = cria_Pilha();
    if (aux == NULL) return NULL;
    
    Elem* topoOriginal = *p; 
    while (topoOriginal != NULL) {
        insere_Pilha(aux, topoOriginal->dados);
        topoOriginal = topoOriginal->prox;
    }

    Elem* topoAux = *aux;
    while(topoAux != NULL) {
        insere_Pilha(copia, topoAux->dados);
        topoAux = topoAux->prox;
    }

    libera_Pilha(aux);
    return copia;
}

void executarQuestaoPilhaDinamica3(void) {
    struct aluno a[4] = 
    {
        {2,"Andre",9.5,7.8,8.5},{4,"Ricardo",7.5,8.7,6.8},{1,"Bianca",9.7,6.7,8.4},{3,"Ana",5.7,6.1,7.4}
    };
    Pilha* pi = cria_Pilha();
    printMensagemColorida(6,"Pilha criada com sucesso!");
    printMensagemColoridaFormatted(5,"Tamanho atual: %d\n",tamanho_Pilha(pi));
    printMensagemColorida(6,"Adicionando 4 elementos...");
    for (int i = 0; i < 4; i++) insere_Pilha(pi, a[i]);
    imprime_Pilha(pi);
    printMensagemColoridaFormatted(5,"Tamanho atual: %d\n",tamanho_Pilha(pi));
    printMensagemColorida(6,"Copiando pilha...");
    Pilha* p = pilha_copia(pi);
    printMensagemColorida(6,"\nPilha Original:");
    imprime_Pilha(pi);
    printMensagemColorida(6,"\n\nPilha Copiada:");
    imprime_Pilha(p);
    printMensagemColoridaFormatted(5,"Tamanho atual da pilha original: %d", tamanho_Pilha(pi));
    printMensagemColoridaFormatted(5,"Tamanho atual da pilha copiada: %d", tamanho_Pilha(p));
    libera_Pilha(pi);
    libera_Pilha(p);
}
