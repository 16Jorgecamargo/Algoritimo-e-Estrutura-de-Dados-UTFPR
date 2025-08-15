#include <stdio.h>
#include "../headlers/1.h"
#include "../shared/headlers/color.h"

void inverterNumero(int numero) {
	if (numero > 0)
	{
		printf("%d", numero % 10);
		inverterNumero(numero / 10);
	}
}


void executarQuestaoRecursividade1(void) {
    int numero;
    setColor(YELLOW);
    printf("Digite um numero inteiro positivo: ");
    scanf("%d", &numero);
    resetColor();
    printf("Numero original: %d\n", numero);
    printf("Numero invertido: ");
    inverterNumero(numero);
    printf("\n");
}