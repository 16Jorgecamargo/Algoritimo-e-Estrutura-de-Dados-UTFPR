# Makefile para o Sistema de Listas de Exercicios AED3
# Detecta automaticamente todos os arquivos .c e compila

# Nome do executavel
TARGET = APP

# Diretorios
SRCDIR = src
BUILDDIR = build
BINDIR = bin

# Encontra automaticamente todos os arquivos .c
SOURCES := $(shell find $(SRCDIR) -name '*.c')

# Converte caminhos de .c para .o no diretorio build
# Exemplo: src/interface/main.c -> build/main.o
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))

# Deteccao do compilador
ifeq ($(OS),Windows_NT)
    # Windows: tenta encontrar gcc/mingw
    ifneq (,$(wildcard D:/MinGW/bin/gcc.exe))
        CC = D:/MinGW/bin/gcc.exe
        TARGET_EXT = .exe
        MKDIR = mkdir
        RM = rmdir /s /q
    else ifneq (,$(shell where gcc 2>nul))
        CC = gcc
        TARGET_EXT = .exe
        MKDIR = mkdir
        RM = rmdir /s /q
    else
        $(error "Compilador GCC nao encontrado! Instale o MinGW")
    endif
else
    # Unix/Linux/macOS
    CC = gcc
    TARGET_EXT =
    MKDIR = mkdir -p
    RM = rm -rf
endif

# Flags do compilador
CFLAGS = -Wall -Wextra -std=c99 -I$(SRCDIR)

# Regra principal
all: directories $(BINDIR)/$(TARGET)$(TARGET_EXT)

# Criar diretorios necessarios (incluindo subdiretorios)
directories:
	@$(MKDIR) $(BUILDDIR) 2>/dev/null || true
	@$(MKDIR) $(BINDIR) 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/interface 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/interface/core 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/shared 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/shared/core 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/recursividade 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/recursividade/core 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/ponteiros 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/ponteiros/core 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/pilhaDinamica 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/pilhaDinamica/core 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/filas 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/filas/core 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/listas 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/listas/core 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/listasDuplamenteEncadeadas 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/listasDuplamenteEncadeadas/core 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/arvoresI 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/arvoresI/core 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/arvoresBinarias 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/arvoresBinarias/core 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/arvoresAVL 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/arvoresAVL/core 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/grafos 2>/dev/null || true
	@$(MKDIR) $(BUILDDIR)/listas/grafos/core 2>/dev/null || true

# Link dos arquivos objeto para criar o executavel
$(BINDIR)/$(TARGET)$(TARGET_EXT): $(OBJECTS)
	@echo "Linkando executavel..."
	@$(CC) $(OBJECTS) -o $@
	@echo ""
	@echo "=== Compilacao concluida com sucesso! ==="
	@echo "Executavel criado: $(BINDIR)/$(TARGET)$(TARGET_EXT)"
	@echo "Total de arquivos compilados: $(words $(OBJECTS))"

# Regra generica para compilar qualquer .c para .o
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@echo "Compilando $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos de build
clean:
	@$(RM) $(BUILDDIR) 2>/dev/null || true
	@$(RM) $(BINDIR) 2>/dev/null || true
	@echo "Arquivos de build removidos!"

# Executar o programa
run: $(BINDIR)/$(TARGET)$(TARGET_EXT)
	@echo ""
	@echo "=== Executando o programa ==="
	@./$(BINDIR)/$(TARGET)$(TARGET_EXT)

# Rebuild completo
rebuild: clean all

# Mostrar informacoes do sistema
info:
	@echo "=== Informacoes do Sistema de Build ==="
	@echo "Compilador detectado: $(CC)"
	@echo "Extensao do executavel: $(TARGET_EXT)"
	@echo "Sistema operacional: $(shell uname -s 2>/dev/null || echo Windows)"
	@echo "Diretorio de origem: $(SRCDIR)"
	@echo "Diretorio de build: $(BUILDDIR)"
	@echo "Diretorio de destino: $(BINDIR)"
	@echo "Total de arquivos fonte: $(words $(SOURCES))"
	@echo ""
	@echo "Arquivos .c encontrados:"
	@echo "$(SOURCES)" | tr ' ' '\n' | sort

.PHONY: all clean run rebuild info directories
