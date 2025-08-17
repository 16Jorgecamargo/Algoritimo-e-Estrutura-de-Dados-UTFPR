#include <stdio.h>


//tenho que verificar se esta funcionando


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