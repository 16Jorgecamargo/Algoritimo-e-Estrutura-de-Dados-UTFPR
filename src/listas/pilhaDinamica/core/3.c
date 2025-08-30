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

    Elem* topoOriginal = *p;
    while (topoOriginal != NULL) {
        insere_Pilha(copia, topoOriginal->dados);
        topoOriginal = topoOriginal->prox;
    }
    return copia;
}

void executarQuestaoPilhaDinamica3(void) {
    struct aluno a[4] = 
    {
        {2,"Andre",9.5,7.8,8.5},{4,"Ricardo",7.5,8.7,6.8},{1,"Bianca",9.7,6.7,8.4},{3,"Ana",5.7,6.1,7.4}
    };
    Pilha* pi = cria_Pilha();
    printf("Tamanho atual: %d\n\n",tamanho_Pilha(pi));
    printf("Adicionando 4 elementos...\n");
    for (int i = 0; i < 4; i++) insere_Pilha(pi, a[i]);
    imprime_Pilha(pi);
    printf("Tamanho atual: %d\n\n",tamanho_Pilha(pi));
    printf("Copiando pilha...\n");
    Pilha* p = pilha_copia(pi);
    printf("\n\nPilha Original:\n");
    imprime_Pilha(pi);
    printf("\n\nPilha Copiada:\n");
    imprime_Pilha(p);
    printf(
        "Tamanho atual da pilha original: %d\nTamanho atual da pilha copiada: %d\n",
        tamanho_Pilha(pi), tamanho_Pilha(p)
    );
    libera_Pilha(pi);
    libera_Pilha(p);
}
