#include <stdio.h>
#include "../headlers/2.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/colorPrint.h"
#include "../../../shared/headlers/clean.h"

void executarQuestaoPonteiros2(void) {

    limparTela();
    setColor(YELLOW);
    printf("=== Ponteiros ===\n");
    printf("=== Executando a Questao 02 ===\n\n");
    resetColor();

printf("main()\n");
printf("{\n");
printf("  int y, *p, x;\n");
printf("  y = 0; ");
printMensagemColorida(4, "// o y recebeu o valor 0");
printf("  p = &y; ");
printMensagemColorida(4, "// o p recebeu o endereco de y");
printf("  x = *p; ");
printMensagemColorida(4, "// o x recebeu o conteudo de *p, entao x=0");
printf("  x = 4; ");
printMensagemColorida(4, "// o x recebeu o valor 4");
printf("  (*p)++;\n");
printf("  x--;\n");
printf("  (*p) += x;");
printMensagemColorida(4, "// o conteudo de p recebeu o conteudo de p + x, ou seja, y = 0 + 3");
printf("  printf (\"y = %%d\\n\", y);");
printMensagemColorida(4, "// vai imprimir y = 3, pois y foi alterado indiretamente com o ponteiro p");
printf("  return(0);\n");
printf("}\n");
}
