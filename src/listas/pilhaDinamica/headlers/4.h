#ifndef PILHADINAMICA_4_H
#define PILHADINAMICA_4_H

struct elementoquestao4
{
    int n;
    struct elementoquestao4 *prox;
};

typedef struct elementoquestao4 ElemQuestao4;
typedef struct elementoquestao4* PilhaQuestao4;

PilhaQuestao4 *cria_PilhaQuestao4();
void libera_PilhaQuestao4(PilhaQuestao4 *pi);
int insere_PilhaQuestao4(PilhaQuestao4 *pi, int n);
int tamanho_PilhaQuestao4(PilhaQuestao4 *pi);
void imprime_PilhaQuestao4(PilhaQuestao4 *pi);
void verificaMMM_PilhaQuestao4(PilhaQuestao4 *pi);
void executarQuestaoPilhaDinamica4(void);

#endif
