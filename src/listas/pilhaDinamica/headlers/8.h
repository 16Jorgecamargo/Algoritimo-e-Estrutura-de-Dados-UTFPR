#ifndef PILHADINAMICA_8_H
#define PILHADINAMICA_8_H

struct elementoquestao8
{
    char caractere;
    struct elementoquestao8 *prox;
};

typedef struct elementoquestao8 ElemQuestao8;
typedef struct elementoquestao8* PilhaQuestao8;

PilhaQuestao8 *cria_PilhaQuestao8();
void libera_PilhaQuestao8(PilhaQuestao8 *pi);
int insere_PilhaQuestao8(PilhaQuestao8 *pi, char c);
int remove_Elemento_PilhaQuestao8(PilhaQuestao8 *pi, char *c);
int PilhaQuestao8_vazia(PilhaQuestao8 *pi);
int verifica_padrao_xCy(PilhaQuestao8 *pi, char *string);
void executarQuestaoPilhaDinamica8(void);

#endif
