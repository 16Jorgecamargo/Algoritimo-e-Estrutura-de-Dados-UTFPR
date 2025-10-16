#ifndef COLORPRINT_H
#define COLORPRINT_H

void printMenuItem(int numero, const char* descricao);
void printMenuItemFormatted(int numero, const char* formato, ...);
void printMensagemColorida(int cor, const char* mensagem);
void printMensagemColoridaFormatted(int cor, const char* formato, ...);
void printMensagemColoridaInline(int cor, const char* mensagem);

#endif
