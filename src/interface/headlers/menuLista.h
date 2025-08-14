#ifndef MENU_LISTA_H
#define MENU_LISTA_H

int mostrarMenuLista(int tipoLista);  // Retorna 0 se deve voltar ao menu principal
int processarOpcaoLista(int tipoLista, int opcao, int numQuestoes);  // Retorna 0 se deve voltar ao menu principal
const char* obterNomeLista(int tipoLista);
int contarQuestoes(int tipoLista);

#endif