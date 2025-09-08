#ifndef PILHADINAMICA_7_H
#define PILHADINAMICA_7_H

struct elementoquestao7
{
    int id;
    int valor;
    struct elementoquestao7 *prox;
};

typedef struct elementoquestao7 ElemQuestao7;
typedef struct elementoquestao7* PilhaQuestao7;

PilhaQuestao7 *cria_PilhaQuestao7();
void libera_PilhaQuestao7(PilhaQuestao7 *pi);
int insere_PilhaQuestao7(PilhaQuestao7 *pi, int id);
int tamanho_PilhaQuestao7(PilhaQuestao7 *pi);
void imprime_PilhaQuestao7(PilhaQuestao7 *pi);
void imprime_PilhaQuestao7_Checagem(PilhaQuestao7 *pi);
void executarQuestaoPilhaDinamica7(void);

#endif
