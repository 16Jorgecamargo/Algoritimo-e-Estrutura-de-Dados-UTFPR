#include <stdio.h>
#include <stdlib.h>
#include "headlers/menuPrincipal.h"
#include "../shared/headlers/clean.h"
#include "../shared/headlers/color.h"
#include "../shared/headlers/logo.h"
#include "../shared/headlers/sleep.h"

int main() {

    limparTela();
    setColor(GREEN);
    printf("=== Sistema de Listas de Exercicios AED3 - UTFPR ===\n\n");
    resetColor();
    
    mostrarLogoUTFPR();
    setColor(GREEN);
    printf("\n\n\nInicializando sistema"); 
    for (int i = 0; i < 3; i++) {
        printf(". ");
        fflush(stdout);
        SLEEP(500); 
    }
    resetColor();

    mostrarMenuPrincipal();
    
    setColor(GREEN);
    printf("\nObrigado por usar o sistema!\n");
    resetColor();
    
    return 0;
}