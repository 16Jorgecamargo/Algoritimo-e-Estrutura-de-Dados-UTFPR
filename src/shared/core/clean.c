#include <stdio.h>
#include <stdlib.h>
#include "../headlers/clean.h"

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

void limparTela(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void limparBufferTeclado(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar(void) {
    printf("\n\n\n");
    printf("Pressione Enter ou ESC para continuar...");

#ifdef _WIN32
    // Windows: usar getch() que não requer Enter
    while (1) {
        int ch = _getch();
        if (ch == 13 || ch == 27) { // Enter ou ESC
            break;
        }
    }
#else
    // Unix/Linux/macOS: configurar terminal para modo raw
    struct termios oldattr, newattr;

    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

    while (1) {
        int ch = getchar();
        if (ch == '\n' || ch == 27) { // Enter ou ESC
            break;
        }
    }

    // Restaurar configurações do terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
#endif
}