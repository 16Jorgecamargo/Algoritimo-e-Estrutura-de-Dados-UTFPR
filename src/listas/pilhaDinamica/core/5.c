#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../shared/headlers/pilhaDinamica.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"
#include "../headlers/5.h"

int pilha_check(Pilha* pi1, Pilha* pi2) {
    int igual = 1;
    if (pi1 == NULL || pi2 == NULL) return 0;
    if (tamanho_Pilha(pi1) != tamanho_Pilha(pi2)) igual = 0;

    Elem* topo1 = *pi1;
    Elem* topo2 = *pi2;
   
    while (topo1 != NULL && topo2 != NULL) {
        if (topo1->dados.matricula != topo2->dados.matricula ||
        strcmp(topo1->dados.nome, topo2->dados.nome) != 0 ||
        topo1->dados.n1 != topo2->dados.n1 ||
        topo1->dados.n2 != topo2->dados.n2 ||
        topo1->dados.n3 != topo2->dados.n3) {
            igual = 0;
            break;
        }
        topo1 = topo1->prox;
        topo2 = topo2->prox;
    }

    printf("%s", igual ? "iguais\n" : "diferentes\n");
    return igual ? 1 : 0;
}

void executarQuestaoPilhaDinamica5(void) {
    struct aluno a[4] = 
    {{2,"Andre",9.5,7.8,8.5},{4,"Ricardo",7.5,8.7,6.8},{1,"Bianca",9.7,6.7,8.4},{3,"Ana",5.7,6.1,7.4}};
    Pilha* piA = cria_Pilha();
    for (int i = 0; i < 4; i++) insere_Pilha(piA, a[i]);

    struct aluno b[3] = 
    {{2,"Andre",9.5,7.8,8.5},{4,"Ricardo",7.5,8.7,6.8},{1,"Bianca",9.7,6.7,8.4}};
    Pilha* piB = cria_Pilha();
    for (int i = 0; i < 3; i++) insere_Pilha(piB, b[i]);

    struct aluno c[4] = 
    {{2,"Andre",9.5,7.8,8.5},{4,"Ricardo",7.5,8.7,6.8},{1,"Bianca",9.7,6.7,8.4},{3,"Joao",5.7,6.1,7.4}};
    Pilha* piC = cria_Pilha();
    for (int i = 0; i < 4; i++) insere_Pilha(piC, c[i]);

    struct aluno d[4] =
    {{2,"Andre",9.5,7.8,8.5},{4,"Ricardo",7.5,8.7,6.8},{1,"Bianca",9.7,6.7,8.4},{3,"Ana",5.7,6.1,7.4}};
    Pilha* piD = cria_Pilha();    
    for (int i = 0; i < 4; i++) insere_Pilha(piD, d[i]);

    printMensagemColorida(6,"Pilhas criadas com sucesso!");
    printf("\nPilha A:\n");
    imprime_Pilha(piA);
    printf("\n\nPilha B:\n");
    imprime_Pilha(piB);
    printf("\n\nPilha C:\n");
    imprime_Pilha(piC);
    printf("\n\nPilha D:\n");
    imprime_Pilha(piD);

    printMensagemColorida(6,"\n\nVerificando igualdade das pilhas...");

    printf("\nPilha A e B sao "); pilha_check(piA, piB);
    printf("Pilha A e C sao "); pilha_check(piA, piC);
    printf("Pilha A e D sao "); pilha_check(piA, piD);

    libera_Pilha(piA);
    libera_Pilha(piB);
    libera_Pilha(piC);
    libera_Pilha(piD);
}
