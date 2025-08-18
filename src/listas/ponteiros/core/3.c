#include <stdio.h>
#include "../headlers/3.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

void executarQuestaoPonteiros3(void) {

    limparTela();
    setColor(YELLOW);
    printf("=== Ponteiros ===\n");
    printf("=== Executando a Questao 03 ===\n\n");
    resetColor();

printf("Verifique o programa abaixo. Encontre o seu erro e corrija-o para que escreva o numero 10 na tela.\n\n");
printf("#include <stdio.h>\n\n");
printf("int main() {\n");
printf(" int x, *p, **q;\n");
printf(" p = &x;\n");
printf(" q = &p;\n");
printf(" x = 10;\n");
printf(" printf(\"\\n%%d\\n\", ");
printMensagemColorida(1, "&q); // o %%d esta tentando mostar o valor de x usando endereco de q");
printf(" printf(\"\\n%%d\\n\", ");
printMensagemColorida(4, "**q); // agora estamos pegando o conteudo de q -> p -> x");
printf(" return(0);\n");
printf("}\n");
}
