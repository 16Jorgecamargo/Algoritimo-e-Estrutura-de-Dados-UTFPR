#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headlers/menuGenerico.h"
#include "../headlers/clean.h"
#include "../headlers/color.h"

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

// Função para criar um novo menu
MenuGenerico* criarMenu(const char* titulo, OpcaoMenu* opcoes, int numOpcoes) {
    MenuGenerico* menu = (MenuGenerico*)malloc(sizeof(MenuGenerico));
    if (!menu) return NULL;

    // Copiar título
    menu->titulo = (char*)malloc(strlen(titulo) + 1);
    strcpy(menu->titulo, titulo);
    menu->descricao = NULL;

    // Copiar opções
    menu->opcoes = (OpcaoMenu*)malloc(sizeof(OpcaoMenu) * numOpcoes);
    for (int i = 0; i < numOpcoes; i++) {
        menu->opcoes[i].texto = (char*)malloc(strlen(opcoes[i].texto) + 1);
        strcpy(menu->opcoes[i].texto, opcoes[i].texto);
        menu->opcoes[i].tipo = opcoes[i].tipo;
        menu->opcoes[i].funcao = opcoes[i].funcao;
    }

    menu->numOpcoes = numOpcoes;
    menu->opcaoSelecionada = 0;

    return menu;
}

// Função para destruir um menu e liberar memória
void destruirMenu(MenuGenerico* menu) {
    if (!menu) return;

    free(menu->titulo);
    if (menu->descricao) {
        free(menu->descricao);
    }

    for (int i = 0; i < menu->numOpcoes; i++) {
        free(menu->opcoes[i].texto);
    }
    free(menu->opcoes);
    free(menu);
}

void definirDescricaoMenu(MenuGenerico* menu, const char* descricao) {
    if (!menu) return;

    if (menu->descricao) {
        free(menu->descricao);
        menu->descricao = NULL;
    }

    if (descricao) {
        menu->descricao = (char*)malloc(strlen(descricao) + 1);
        if (menu->descricao) {
            strcpy(menu->descricao, descricao);
        }
    }
}

// Função para renderizar o menu na tela
void renderizarMenu(MenuGenerico* menu) {
    limparTela();

    // Mostrar título
    setColor(CYAN);
    printf("=== %s ===\n\n", menu->titulo);
    resetColor();

    if (menu->descricao && menu->descricao[0] != '\0') {
        printf("%s\n", menu->descricao);
        printf("\n");
    }

    // Mostrar opções
    for (int i = 0; i < menu->numOpcoes; i++) {
        if (i == menu->opcaoSelecionada) {
            setColorAndBackground(WHITE, YELLOW);
            printf("  %s  ", menu->opcoes[i].texto);
            resetColor();
        } else {
            printf("  %s  ", menu->opcoes[i].texto);
        }
        printf("\n");
    }

    printf("\n");
    setColor(GREEN);
    printf("Use ↑↓ para navegar | Enter/Espaco para selecionar | ESC para voltar\n");
    resetColor();
}

// Função para ler tecla especial (multiplataforma)
int lerTeclaEspecial(void) {
#ifdef _WIN32
    int tecla = _getch();
    if (tecla == 0 || tecla == 224) {
        tecla = _getch(); // Ler código da tecla especial
    }
    return tecla;
#else
    struct termios oldattr, newattr;
    int ch;

    // Configurar terminal para modo raw
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

    ch = getchar();

    // Se for sequência de escape (setas)
    if (ch == 27) {
        // Configurar para não bloquear na leitura
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

        int ch2 = getchar();

        if (ch2 == 91) {
            int ch3 = getchar();
            switch (ch3) {
                case 65: ch = TECLA_SETA_CIMA; break;    // Seta para cima
                case 66: ch = TECLA_SETA_BAIXO; break;   // Seta para baixo
                default: ch = TECLA_ESC; break;
            }
        } else {
            // Se não veio nada depois, é ESC puro
            ch = TECLA_ESC;
        }

        // Restaurar modo de bloqueio
        fcntl(STDIN_FILENO, F_SETFL, flags);
    }

    // Restaurar configurações do terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

    return ch;
#endif
}

// Função para mover a seleção
void moverSelecao(MenuGenerico* menu, int direcao) {
    if (direcao > 0) { // Para baixo
        menu->opcaoSelecionada = (menu->opcaoSelecionada + 1) % menu->numOpcoes;
    } else { // Para cima
        menu->opcaoSelecionada = (menu->opcaoSelecionada - 1 + menu->numOpcoes) % menu->numOpcoes;
    }
}

// Função principal para executar o menu
int executarMenu(MenuGenerico* menu) {
    if (!menu) return -1;

    int continuar = 1;

    while (continuar) {
        renderizarMenu(menu);

        int tecla = lerTeclaEspecial();

        switch (tecla) {
            case TECLA_SETA_CIMA:
#ifdef _WIN32
            case 72: // Seta para cima no Windows
#endif
                moverSelecao(menu, -1);
                break;

            case TECLA_SETA_BAIXO:
#ifdef _WIN32
            case 80: // Seta para baixo no Windows
#endif
                moverSelecao(menu, 1);
                break;

            case TECLA_ENTER:
            case '\n':
            case TECLA_ESPACO:
                {
                    OpcaoMenu* opcaoAtual = &menu->opcoes[menu->opcaoSelecionada];

                    switch (opcaoAtual->tipo) {
                        case ACAO_EXECUTAR_FUNCAO:
                            if (opcaoAtual->funcao) {
                                int resultado = opcaoAtual->funcao();
                                if (resultado == 0) { // Se a função retornar 0, sair
                                    continuar = 0;
                                }
                            }
                            break;

                        case ACAO_VOLTAR:
                            return 1; // Voltar ao menu anterior

                        case ACAO_SAIR:
                            return 0; // Sair do programa
                    }
                }
                break;

            case TECLA_ESC:
                return 1; // ESC sempre volta

            default:
                // Ignorar outras teclas
                break;
        }
    }

    return 0;
}
