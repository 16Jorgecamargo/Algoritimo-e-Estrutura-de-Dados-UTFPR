# Makefile para o Sistema de Listas de Exercicios AED3
# Detecta automaticamente o compilador disponivel no sistema

# Nome do executavel
TARGET = APP

# Diretorios
SRCDIR = src
BUILDDIR = build
BINDIR = bin

# Arquivos fonte
SOURCES = $(SRCDIR)/interface/main.c \
          $(SRCDIR)/interface/core/menu\ principal.c \
          $(SRCDIR)/interface/core/menu\ lista.c \
          $(SRCDIR)/interface/core/menu\ questao.c \
          $(SRCDIR)/shared/core/clean.c \
          $(SRCDIR)/shared/core/color.c

# Arquivos objeto
OBJECTS = $(BUILDDIR)/main.o \
          $(BUILDDIR)/menu_principal.o \
          $(BUILDDIR)/menu_lista.o \
          $(BUILDDIR)/menu_questao.o \
          $(BUILDDIR)/clean.o \
          $(BUILDDIR)/color.o

# Deteccao do compilador
ifeq ($(OS),Windows_NT)
    # Tenta encontrar gcc/mingw no Windows
    ifneq (,$(wildcard D:/MinGW/bin/gcc.exe))
        CC = D:/MinGW/bin/gcc.exe
        TARGET_EXT = .exe
    else ifneq (,$(shell where gcc 2>nul))
        CC = gcc
        TARGET_EXT = .exe
    else ifneq (,$(shell where mingw32-gcc 2>nul))
        CC = mingw32-gcc
        TARGET_EXT = .exe
    else ifneq (,$(shell where x86_64-w64-mingw32-gcc 2>nul))
        CC = x86_64-w64-mingw32-gcc
        TARGET_EXT = .exe
    else
        $(error "Compilador GCC nao encontrado! Instale o MinGW ou adicione ao PATH")
    endif
else
    # Sistema Unix/Linux/Mac
    CC = gcc
    TARGET_EXT =
endif

# Flags do compilador
CFLAGS = -Wall -Wextra -std=c99 -I$(SRCDIR)

# Regra principal
all: directories $(BINDIR)/$(TARGET)$(TARGET_EXT)

# Criar diretorios necessarios
directories:
	@if not exist "$(BUILDDIR)" mkdir "$(BUILDDIR)" 2>nul || mkdir -p $(BUILDDIR)
	@if not exist "$(BINDIR)" mkdir "$(BINDIR)" 2>nul || mkdir -p $(BINDIR)

# Link dos arquivos objeto para criar o executavel
$(BINDIR)/$(TARGET)$(TARGET_EXT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@
	@echo.
	@echo === Compilacao concluida com sucesso! ===
	@echo Executavel criado: $(BINDIR)/$(TARGET)$(TARGET_EXT)

# Regras para compilar arquivos fonte individuais
$(BUILDDIR)/main.o: $(SRCDIR)/interface/main.c
	$(CC) $(CFLAGS) -c "$<" -o $@

$(BUILDDIR)/menu_principal.o: "$(SRCDIR)/interface/core/menuPrincipal.c"
	$(CC) $(CFLAGS) -c "$<" -o $@

$(BUILDDIR)/menu_lista.o: "$(SRCDIR)/interface/core/menuLista.c"
	$(CC) $(CFLAGS) -c "$<" -o $@

$(BUILDDIR)/menu_questao.o: "$(SRCDIR)/interface/core/menuQuestao.c"
	$(CC) $(CFLAGS) -c "$<" -o $@

$(BUILDDIR)/clean.o: $(SRCDIR)/shared/core/clean.c
	$(CC) $(CFLAGS) -c "$<" -o $@

$(BUILDDIR)/color.o: $(SRCDIR)/shared/core/color.c
	$(CC) $(CFLAGS) -c "$<" -o $@

# Limpeza dos arquivos de build
clean:
	@if exist "$(BUILDDIR)" rmdir /s /q "$(BUILDDIR)" 2>nul || rm -rf $(BUILDDIR)
	@if exist "$(BINDIR)" rmdir /s /q "$(BINDIR)" 2>nul || rm -rf $(BINDIR)
	@echo Arquivos de build removidos!

# Executar o programa
run: $(BINDIR)/$(TARGET)$(TARGET_EXT)
	@echo.
	@echo === Executando o programa ===
	@"$(BINDIR)/$(TARGET)$(TARGET_EXT)"

# Rebuild completo
rebuild: clean all

# Mostrar informacoes do sistema
info:
	@echo === Informacoes do Sistema de Build ===
	@echo Compilador detectado: $(CC)
	@echo Extensao do executavel: $(TARGET_EXT)
	@echo Sistema operacional: $(OS)
	@echo Diretorio de origem: $(SRCDIR)
	@echo Diretorio de build: $(BUILDDIR)
	@echo Diretorio de destino: $(BINDIR)

.PHONY: all clean run rebuild info directories