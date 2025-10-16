#ifndef PATH_UTILS_H
#define PATH_UTILS_H

#include <stddef.h>

// Retorna o caminho absoluto do diretorio raiz do projeto
// O buffer deve ter pelo menos 512 bytes
void obterDiretorioRaiz(char* buffer, size_t tamanho);

#endif
