#ifndef MENU_QUESTAO_H
#define MENU_QUESTAO_H

int mostrarMenuQuestao(int tipoLista, int numeroQuestao);
void processarOpcaoQuestao(int tipoLista, int numeroQuestao, int opcao);
void mostrarLogicaQuestao(int tipoLista, int numeroQuestao);
void executarQuestao(int tipoLista, int numeroQuestao);
const char* obterCaminhoLista(int tipoLista);

#endif