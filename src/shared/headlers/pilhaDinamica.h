//Arquivo PilhaDin.h

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
}; // estrutura do aluno ou model aluno

struct elemento
{
    struct aluno dados;
    struct elemento *prox;
}; // estrutura do elemento 

typedef struct elemento Elem;

typedef struct elemento* Pilha;

Pilha* cria_Pilha(); // cria uma nova pilha
void libera_Pilha(Pilha* pi); 
int consulta_topo_Pilha(Pilha* pi, struct aluno *al);
int insere_Pilha(Pilha* pi, struct aluno al); //push
int remove_Pilha(Pilha* pi); //pop
int tamanho_Pilha(Pilha* pi);
int Pilha_vazia(Pilha* pi);
int Pilha_cheia(Pilha* pi);
void imprime_Pilha(Pilha* pi);
