#include <stdio.h>
#include <stdarg.h>
#include "../headlers/colorPrint.h"
#include "../headlers/color.h"

void printMenuItem(int numero, const char* descricao) {
    setColor(YELLOW);
    if (numero < 10) {
        printf(" %d. ", numero);
    } else {
        printf("%d. ", numero);
    }
    resetColor();
    printf("%s\n", descricao);
}

void printMenuItemFormatted(int numero, const char* formato, ...) {
    setColor(YELLOW);
    if (numero < 10) {
        printf(" %d. ", numero);
    } else {
        printf("%d. ", numero);
    }
    resetColor();
    
    va_list args;
    va_start(args, formato);
    vprintf(formato, args);
    va_end(args);
    
    printf("\n");
}