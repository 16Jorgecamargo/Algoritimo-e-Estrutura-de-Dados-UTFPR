#ifndef MENU_GENERICO_H
#define MENU_GENERICO_H

#include <stdbool.h>

// Tipos de ação para opções do menu
typedef enum {
    ACAO_EXECUTAR_FUNCAO,   // Executar uma função
    ACAO_VOLTAR,            // Voltar ao menu anterior
    ACAO_SAIR               // Sair do programa
} TipoAcao;

// Definição de uma função callback para opções do menu
typedef int (*FuncaoCallback)(void);

// Estrutura para uma opção do menu
typedef struct {
    char *texto;            // Texto da opção
    TipoAcao tipo;          // Tipo de ação
    FuncaoCallback funcao;  // Função a ser executada (pode ser NULL)
} OpcaoMenu;

// Estrutura principal do menu
typedef struct {
    char *titulo;           // Título do menu
    char *descricao;        // Texto descritivo opcional exibido acima das opções
    OpcaoMenu *opcoes;      // Array de opções
    int numOpcoes;          // Número de opções
    int opcaoSelecionada;   // Opção atualmente selecionada
} MenuGenerico;

// Teclas especiais
#define TECLA_SETA_CIMA    72
#define TECLA_SETA_BAIXO   80
#define TECLA_ENTER        13
#define TECLA_ESPACO       32
#define TECLA_ESC          27

// Funções principais
MenuGenerico* criarMenu(const char* titulo, OpcaoMenu* opcoes, int numOpcoes);
int executarMenu(MenuGenerico* menu);
void destruirMenu(MenuGenerico* menu);
void definirDescricaoMenu(MenuGenerico* menu, const char* descricao);

// Funções auxiliares
void renderizarMenu(MenuGenerico* menu);
int lerTeclaEspecial(void);
void moverSelecao(MenuGenerico* menu, int direcao);

#endif
