#include <stdio.h>
#include "../headlers/logo.h"
#include "../headlers/color.h"

// Função auxiliar para imprimir uma linha colorida
void imprimirLinha(const char* linha) {
    for (int i = 0; linha[i] != '\0'; i++) {
        char c = linha[i];
        if (c == ':') {
            setColor(YELLOW);
            setBackgroundColor(YELLOW);
            printf("%c", c);
            resetColor();
        } else if (c == 'u' || c == 't' || c == 'f' || c == 'p' || c == 'r') {
            setColor(BLACK);
            setBackgroundColor(BLACK);
            printf("%c", c);
            resetColor();
        } else {
            printf("%c", c);
        }
    }
    printf("\n");
}

void mostrarLogoUTFPR(void) {
    printf("\n");
    
    imprimirLinha("                         tttt              ffffffffffffffff ");
    imprimirLinha("                       ttt:::t            f::::::::::::::::f ");
    imprimirLinha("                       t:::::t           f::::::::::::::::::f ");
    imprimirLinha("                       t:::::t           f::::::fffffff:::::f ");
    imprimirLinha(" uuuuuu    uuuuuuttttttt:::::ttttttt     f:::::f       ffffffppppp   ppppppppp   rrrrr   rrrrrrrrr ");
    imprimirLinha(" u::::u    u::::ut:::::::::::::::::t     f:::::f             p::::ppp:::::::::p  r::::rrr:::::::::r ");
    imprimirLinha(" u::::u    u::::ut:::::::::::::::::t    f:::::::ffffff       p:::::::::::::::::p r:::::::::::::::::r ");
    imprimirLinha(" u::::u    u::::utttttt:::::::tttttt    f::::::::::::f       pp::::::ppppp::::::prr::::::rrrrr::::::r ");
    imprimirLinha(" u::::u    u::::u      t:::::t          f::::::::::::f        p:::::p     p:::::p r:::::r     r:::::r ");
    imprimirLinha(" u::::u    u::::u      t:::::t          f:::::::ffffff        p:::::p     p:::::p r:::::r     rrrrrrr ");
    imprimirLinha(" u::::u    u::::u      t:::::t           f:::::f              p:::::p     p:::::p r:::::r ");
    imprimirLinha(" u:::::uuuu:::::u      t:::::t    tttttt f:::::f              p:::::p    p::::::p r:::::r ");
    imprimirLinha(" u:::::::::::::::u     t::::::tttt:::::t f::::::f             p:::::ppppp:::::::p r:::::r ");
    imprimirLinha("  u:::::::::::::::u    tt::::::::::::::tf:::::::f             p::::::::::::::::p  r:::::r ");
    imprimirLinha("   uu::::::::uu:::u      tt:::::::::::ttf:::::::f             p::::::::::::::pp   r:::::r ");
    imprimirLinha("     uuuuuuuu  uuuu        ttttttttttt  fffffffff             p::::::pppppppp     rrrrrrr ");
    imprimirLinha("                                                              p::::::p ");
    imprimirLinha("                                                              p::::::p ");
    imprimirLinha("                                                              p:::::::p ");
    imprimirLinha("                                                              p:::::::p ");
    imprimirLinha("                                                              p:::::::p ");
    imprimirLinha("                                                              ppppppppp ");
    
    printf("\n");
}