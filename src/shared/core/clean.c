#include <stdio.h>
#include <stdlib.h>
#include "../headlers/clean.h"

#ifdef _WIN32
    #include <windows.h>
#endif

void limparTela(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar(void) {
    printf("\n\n\n");
    printf("Pressione Enter para continuar...");
    getchar();
}