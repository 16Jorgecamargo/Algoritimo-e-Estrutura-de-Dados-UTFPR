#include <stdio.h>





// a logica que eu usei para isso foi usar a multiplicacao
//do numero atual (k) pela potencia do numero atual (k) com o expoente (n-1)
int potencia(int k, int n)
{
	if (n == 0) return 1;
	else return k * potencia(k, n - 1);
}

// essa funC'C#o C) so para criar um vetor de 100 numeros reais
void criarVetor(double vetorReais[], int tamanho)
{
	for (int i = 0; i < tamanho; i++)
	{
		vetorReais[i] = i * 1.1;
		printf("%.1f | ", vetorReais[i]);
	}
	printf("\n\n");
}

// a logica que eu usei para isso foi informar o inicio e o fim do vetor e conforme for passando
// ele salva o inicio em uma variavel temporaria depois trocou o valor do final no inicio e trocou o valor da variavel temporaria no final
// ou seja: inicio -> temp depois fim -> inicio depois temp -> fim
void inverterReais(double vetorReais[], int inicio, int fim)
{
	if (inicio < fim)
	{
		double temp = vetorReais[inicio];
		vetorReais[inicio] = vetorReais[fim];
		vetorReais[fim] = temp;
		inverterReais(vetorReais, inicio + 1, fim - 1);
	}
}


//tenho que verificar se estC! funcionando
int minimoMultiploComum(int x, int y) {
	if(y == 0) return x;
	minimoMultiploComum(y, x%y);
}

//tenho que verificar se estC! funcionando
int ocorrencia(int n, const int *v, int tamanho) {
    if (tamanho == 0) return 0;
    return (v[0] == n) + ocorrencia(n, v + 1, tamanho - 1);
}


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
		case 3:
			int Somatorio;
			scanf("%d", &Somatorio);
			if (Somatorio < 0)
				printf("o numero precisa ser inteiro positivo!\n");
			else
				printf("A somatorio dos %d numeros C): %d\n", Somatorio, somatorio(Somatorio));
			break;
		case 4:
			int k, n;
			scanf("%d", &k);
			scanf("%d", &n);
			if (k < 0 || n < 0)
				printf("os numeros precisa ser inteiro positivo!\n");
			else
				printf("o resultado de %d^%d: %d\n", k, n, potencia(k, n));
			break;
		case 5:
			double vetorReais[100];
			criarVetor(vetorReais, 100);
			inverterReais(vetorReais, 0, 99);
			for (int i = 0; i < 100; i++)
				printf("%.1f | ", vetorReais[i]);
			printf("\n");
			break;
		case 6:
			minimoMultiploComum(x,y);
			break;
		case 7:
			int vetorOcorrencia[] = {1,3,2,1,4,5,1,1,5,6};
            int tamanho = sizeof(vetorOcorrencia) / sizeof(vetorOcorrencia[0]);
            printf("%d\n", ocorrencia(5, vetorOcorrencia, tamanho));
			break;
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