#include <stdio.h>
#include "../headlers/animacao.h"

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(x) Sleep(x)
#else
    #include <unistd.h>
    #define SLEEP_MS(x) usleep((x) * 1000)
#endif

// Funcao para imprimir texto com animacao de pontinhos
void printComAnimacao(const char* texto) {
    printf("%s", texto);
    fflush(stdout);  // Força impressão imediata

    // Anima 3 pontinhos
    for (int i = 0; i < 3; i++) {
        SLEEP_MS(300);  // 300ms entre cada ponto
        printf(".");
        fflush(stdout);
    }

    printf("\n");
}
