#include "../headlers/pathUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <direct.h>
    #include <io.h>
    #define getcwd _getcwd
    #define ACCESS _access
    #define PATH_SEPARATOR '\\'
#else
    #include <unistd.h>
    #define ACCESS access
    #define PATH_SEPARATOR '/'
#endif

// Verifica se um diretorio contem um arquivo marcador (Makefile ou .git)
static int verificarDiretorioRaiz(const char* caminho) {
    char caminhoTeste[512];

    // Verifica se existe Makefile
    snprintf(caminhoTeste, sizeof(caminhoTeste), "%s%cMakefile", caminho, PATH_SEPARATOR);
    if (ACCESS(caminhoTeste, 0) == 0) {
        return 1;
    }

    // Verifica se existe .git
    snprintf(caminhoTeste, sizeof(caminhoTeste), "%s%c.git", caminho, PATH_SEPARATOR);
    if (ACCESS(caminhoTeste, 0) == 0) {
        return 1;
    }

    return 0;
}

void obterDiretorioRaiz(char* buffer, size_t tamanho) {
    char caminhoAtual[512];
    char caminhoAnterior[512] = "";
    char caminhoOriginal[512];

    // Salva o diretorio atual para restaurar depois
    if (getcwd(caminhoOriginal, sizeof(caminhoOriginal)) == NULL) {
        buffer[0] = '\0';
        return;
    }

    // Obtem o diretorio atual
    if (getcwd(caminhoAtual, sizeof(caminhoAtual)) == NULL) {
        buffer[0] = '\0';
        return;
    }

    // Sobe na hierarquia de diretorios ate encontrar a raiz do projeto
    while (1) {
        // Verifica se o diretorio atual e a raiz do projeto
        if (verificarDiretorioRaiz(caminhoAtual)) {
            snprintf(buffer, tamanho, "%s", caminhoAtual);

            // Restaura o diretorio original antes de retornar
            #ifdef _WIN32
                _chdir(caminhoOriginal);
            #else
                chdir(caminhoOriginal);
            #endif

            return;
        }

        // Guarda o caminho anterior
        strncpy(caminhoAnterior, caminhoAtual, sizeof(caminhoAnterior) - 1);

        // Sobe um diretorio
        #ifdef _WIN32
            if (_chdir("..") != 0) {
                break;
            }
        #else
            if (chdir("..") != 0) {
                break;
            }
        #endif

        // Obtem o novo caminho
        if (getcwd(caminhoAtual, sizeof(caminhoAtual)) == NULL) {
            break;
        }

        // Se o caminho nao mudou, chegamos na raiz do sistema
        if (strcmp(caminhoAtual, caminhoAnterior) == 0) {
            break;
        }
    }

    // Restaura o diretorio original antes de retornar
    #ifdef _WIN32
        _chdir(caminhoOriginal);
    #else
        chdir(caminhoOriginal);
    #endif

    // Se nao encontrou, retorna vazio
    buffer[0] = '\0';
}
