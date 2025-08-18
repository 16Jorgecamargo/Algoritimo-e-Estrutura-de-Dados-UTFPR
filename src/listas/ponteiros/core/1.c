#include <stdio.h>
#include "../headlers/1.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

void executarQuestaoPonteiros1(void) {
           
    limparTela();
    setColor(YELLOW);
    printf("=== Ponteiros ===\n");
    printf("=== Executando a Questao 01 ===\n\n");
    resetColor();

    printf("Sendo p um ponteiro, qual a diferenca entre:\n");
    printf("| p++;\n->");
    printMensagemColorida(4, " Aqui estamos pulando para o proximo indice, exemplo: v[0] vamos para v[1]\n\n");
    printf("| (*p)++;\n->");
    printMensagemColorida(4, " Aqui estamos incrementando o conteudo apontado por p, ou seja, *p eh 10, agora *p eh 11\n\n");
    printf("| *(p++);\n->");
    printMensagemColorida(4, " Primeiro acessamos o conteudo atual apontado por p, e so depois o ponteiro eh incrementado,\n ou seja acessamos o conteudo do proximo indice do ponteiro\n\n");
    printf("| *(p+10);\n->");
    printMensagemColorida(4, " Aqui estamos acessando o indice que esta 10 posicoes a frente de p\n\n");
}