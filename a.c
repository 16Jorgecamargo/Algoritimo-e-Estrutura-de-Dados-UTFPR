#include <stdio.h>


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