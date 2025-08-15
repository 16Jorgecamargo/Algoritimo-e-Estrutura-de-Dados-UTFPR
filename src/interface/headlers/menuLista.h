#ifndef MENU_LISTA_H
#define MENU_LISTA_H

int mostrarMenuLista(int tipoLista);
int processarOpcaoLista(int tipoLista, int opcao, int numQuestoes);
const char* obterNomeLista(int tipoLista);
int contarQuestoes(int tipoLista);

#endif