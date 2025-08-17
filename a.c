#include <stdio.h>




//tenho que verificar se esta funcionando
int somaInteiros(int x, int y) {
	if (y == 0) return 0;
	else return somaInteros(x );
}

//tenho que verificar se esta funcionando
void ocorrenciaParCrescente(int n) {
	int inicio = 0;
	if (inicio <= n) {
		if (inicio%inicio == 0) printf("%d |", inicio);
		ocorrenciaParCrescente(inicio++);
	}
}

//tenho que verificar se esta funcionando
void numerosNaturais(int n)
{
    if(n > 0) {
        printf("%d", n);
        numerosNaturais(n--);
    }
}

//tenho que verificar se esta funcionando
void ocorrenciaParDecrescente(int n) {
	if (n >= 0) {
		if (n%n == 0) printf("%d |", n);
		ocorrenciaParDecrescente(n--);
	}
}

//tenho que verificar se esta funcionando



int main()
{
	int op;
	int menu = 1;
	while (menu == 1)
	{
		printf("Escolha o numero da atividade de recursao (1 - 12)\n");
		scanf("%d", &op);
		switch (op)
		{
		case 8:
			somaInteiros(x, y);
			break;
		case 9:
			int valorPar
			scanf("%d", &valorPar)
			if (valorPar % 2 != 0) printf("o valor precisa ser inteir par");
			ocorrenciaPar(valorPar);
			break;
		case 10:
			break;
		case 11:
			break;
		case 12:
			break;
		case 0:
			menu = 0;
			break;
		default:
			printf("numero nao encontrado");
			break;
		}
	}

	return 0;
}