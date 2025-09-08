#ifndef PILHADINAMICA_6_H
#define PILHADINAMICA_6_H

struct elementoquestao6
{
    char caracter;
    struct elementoquestao6 *prox;
};

typedef struct elementoquestao6 ElemQuestao6;
typedef struct elementoquestao6* PilhaQuestao6;

PilhaQuestao6 *cria_PilhaQuestao6();
void libera_PilhaQuestao6(PilhaQuestao6 *pi);
int insere_PilhaQuestao6(PilhaQuestao6 *pi, char caractere);
int tamanho_PilhaQuestao6(PilhaQuestao6 *pi);
void imprime_PilhaQuestao6(PilhaQuestao6 *pi);
void pilha_CheckQuestao6(PilhaQuestao6* p);
void executarQuestaoPilhaDinamica6(void);

#endif
