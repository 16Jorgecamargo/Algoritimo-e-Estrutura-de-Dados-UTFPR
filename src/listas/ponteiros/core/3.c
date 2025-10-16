#include <stdio.h>
#include "../index.h"
#include "../../../shared/headlers/color.h"
#include "../../../shared/headlers/clean.h"
#include "../../../shared/headlers/colorPrint.h"

// Questao 3: Corrigir erro em ponteiro duplo

static void imprimirCabecalho(void) {
    limparTela();
    printMensagemColoridaFormatted(YELLOW, "=== Ponteiros - Questao 03 ===");
    printf("\n");
}

static void mostrarCodigoComErro(void) {
    printMensagemColoridaFormatted(CYAN, "CODIGO COM ERRO:\n");

    printf("#include <stdio.h>\n");
    printf("int main() {\n");
    printf("  int x, *p, **q;\n");
    printf("  p = &x;\n");
    printf("  q = &p;\n");
    printf("  x = 10;\n");
    printf("  printf(\"\\n%%d\\n\", &q);  // ERRO AQUI!\n");
    printf("  return(0);\n");
    printf("}\n\n");

    printMensagemColoridaInline(RED, "ERRO: ");
    printf("&q retorna o ENDERECO de q, nao o valor armazenado em x.\n\n");
}

static void mostrarConceito(void) {
    printMensagemColoridaFormatted(CYAN, "PONTEIRO DUPLO - CONCEITO:\n");

    printf("Declaracao: int x, *p, **q;\n\n");
    printf("x   = variavel inteira\n");
    printf("*p  = ponteiro para int\n");
    printf("**q = ponteiro para ponteiro para int\n\n");

    printf("Niveis de acesso:\n");
    printf(" &q  = Endereco de q\n");
    printf("  q  = Conteudo de q (endereco de p)\n");
    printf(" *q  = Conteudo de p (endereco de x)\n");
    printf("**q  = Conteudo de x (valor final)\n\n");
}

static void mostrarCodigoCorrigido(int valorX) {
    printMensagemColoridaFormatted(CYAN, "CODIGO CORRIGIDO:\n");

    printf("#include <stdio.h>\n");
    printf("int main() {\n");
    printf("  int x, *p, **q;\n");
    printf("  p = &x;\n");
    printf("  q = &p;\n");
    printf("  x = %d;\n", valorX);
    printf("  printf(\"\\n%%d\\n\", **q);  // CORRIGIDO!\n");
    printf("  return(0);\n");
    printf("}\n\n");

    int x = valorX;
    int *p = &x;
    int **q = &p;

    printMensagemColoridaFormatted(CYAN, "Resultado em tempo de execucao: %d\n", **q);

    printMensagemColoridaFormatted(GREEN, "Agora usamos **q para acessar o valor de x corretamente.\n");
}

void executarQuestaoPonteiros3(void) {
    executarQuestaoPonteiros3Predefinido();
}

void executarQuestaoPonteiros3Predefinido(void) {
    imprimirCabecalho();
    mostrarCodigoComErro();
    mostrarConceito();
    mostrarCodigoCorrigido(10);
    pausar();
}

void executarQuestaoPonteiros3EntradaManual(void) {
    imprimirCabecalho();

    int valorX;
    printf("Escolha o valor que deseja atribuir a x: ");
    if (scanf("%d", &valorX) != 1) {
        limparBufferTeclado();
        printMensagemColoridaFormatted(RED, "\nEntrada invalida!");
        pausar();
        return;
    }
    limparBufferTeclado();

    mostrarCodigoComErro();
    mostrarConceito();
    mostrarCodigoCorrigido(valorX);
    pausar();
}
