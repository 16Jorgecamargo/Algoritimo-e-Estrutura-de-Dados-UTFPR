@echo off
setlocal enabledelayedexpansion
echo === Sistema de Build para Windows ===
echo.

:: Detecta o compilador GCC disponivel no sistema
set COMPILER_FOUND=0
set GCC_PATH=

:: Verifica se o GCC esta no diretorio especificado pelo usuario
if exist "D:\MinGW\bin\gcc.exe" (
    set GCC_PATH=D:\MinGW\bin\gcc.exe
    set COMPILER_FOUND=1
    echo Compilador encontrado em: D:\MinGW\bin\gcc.exe
    goto :found_compiler
)

:: Verifica se o GCC esta no PATH do sistema
where gcc >nul 2>&1
if %ERRORLEVEL% == 0 (
    set GCC_PATH=gcc
    set COMPILER_FOUND=1
    echo Compilador encontrado no PATH: gcc
    goto :found_compiler
)

:: Verifica MinGW32
where mingw32-gcc >nul 2>&1
if %ERRORLEVEL% == 0 (
    set GCC_PATH=mingw32-gcc
    set COMPILER_FOUND=1
    echo Compilador encontrado no PATH: mingw32-gcc
    goto :found_compiler
)

:: Verifica MinGW64
where x86_64-w64-mingw32-gcc >nul 2>&1
if %ERRORLEVEL% == 0 (
    set GCC_PATH=x86_64-w64-mingw32-gcc
    set COMPILER_FOUND=1
    echo Compilador encontrado no PATH: x86_64-w64-mingw32-gcc
    goto :found_compiler
)

:: Verifica outros caminhos comuns do MinGW
if exist "C:\MinGW\bin\gcc.exe" (
    set GCC_PATH=C:\MinGW\bin\gcc.exe
    set COMPILER_FOUND=1
    echo Compilador encontrado em: C:\MinGW\bin\gcc.exe
    goto :found_compiler
)

if exist "C:\Program Files\MinGW\bin\gcc.exe" (
    set GCC_PATH="C:\Program Files\MinGW\bin\gcc.exe"
    set COMPILER_FOUND=1
    echo Compilador encontrado em: C:\Program Files\MinGW\bin\gcc.exe
    goto :found_compiler
)

if exist "C:\msys64\mingw64\bin\gcc.exe" (
    set GCC_PATH=C:\msys64\mingw64\bin\gcc.exe
    set COMPILER_FOUND=1
    echo Compilador encontrado em: C:\msys64\mingw64\bin\gcc.exe
    goto :found_compiler
)

:: Se nenhum compilador foi encontrado
if %COMPILER_FOUND% == 0 (
    echo.
    echo [ERRO] Compilador GCC nao encontrado!
    echo.
    echo Solucoes possíveis:
    echo 1. Instale o MinGW-w64 de: https://www.mingw-w64.org/downloads/
    echo 2. Adicione o diretorio bin do MinGW ao PATH do sistema
    echo 3. Instale via MSYS2: https://www.msys2.org/
    echo 4. Use um IDE como Dev-C++ ou Code::Blocks que ja inclui o compilador
    echo.
    pause
    exit /b 1
)

:found_compiler
echo.

:: Criar diretorios se nao existirem
if not exist "build" mkdir build
if not exist "bin" mkdir bin

echo === Compilando arquivos fonte (paralelo) ===

:: Compilar arquivos principais em paralelo
echo Iniciando compilacao paralela...
start /b "" %GCC_PATH% -O1 -std=c99 -Isrc -c "src/interface/main.c" -o "build/main.o"
start /b "" %GCC_PATH% -O1 -std=c99 -Isrc -c "src/interface/core/menuPrincipal.c" -o "build/menu_principal.o"
start /b "" %GCC_PATH% -O1 -std=c99 -Isrc -c "src/interface/core/menuLista.c" -o "build/menu_lista.o"
start /b "" %GCC_PATH% -O1 -std=c99 -Isrc -c "src/interface/core/menuQuestao.c" -o "build/menu_questao.o"
start /b "" %GCC_PATH% -O1 -std=c99 -Isrc -c "src/shared/core/clean.c" -o "build/clean.o"
start /b "" %GCC_PATH% -O1 -std=c99 -Isrc -c "src/shared/core/color.c" -o "build/color.o"
start /b "" %GCC_PATH% -O1 -std=c99 -Isrc -c "src/shared/core/logo.c" -o "build/logo.o"
start /b "" %GCC_PATH% -O1 -std=c99 -Isrc -c "src/shared/core/colorPrint.c" -o "build/colorPrint.o"
start /b "" %GCC_PATH% -O1 -std=c99 -Isrc -c "src/shared/core/pilhaDinamica.c" -o "build/pilhaDinamica.o"

:: Aguardar conclusao da compilacao principal
:wait_core
tasklist /fi "imagename eq gcc.exe" | find "gcc.exe" >nul
if %errorlevel% == 0 (
    timeout /t 1 /nobreak >nul
    goto wait_core
)

:: Verificar se houve erros na compilacao principal
set CORE_FILES=main.o menu_principal.o menu_lista.o menu_questao.o clean.o color.o logo.o colorPrint.o pilhaDinamica.o
for %%f in (%CORE_FILES%) do (
    if not exist "build\%%f" (
        echo [ERRO] Falha ao compilar %%f
        goto :error
    )
)

:: Compilar questoes (otimizado)
echo Compilando questoes...
set QUESTAO_OBJECTS=

:: Compilar questoes em lotes paralelos
for /r "src\listas" %%f in (*.c) do (
    set "caminho_completo=%%~dpf"
    set "caminho_completo=!caminho_completo:%CD%\src\listas\=!"
    for /f "tokens=1 delims=\" %%a in ("!caminho_completo!") do set "nome_lista=%%a"
    
    set "arquivo=%%f"
    set "arquivo=!arquivo:%CD%\=!"
    set "nome_obj=build\questao_!nome_lista!_%%~nf.o"
    
    :: Compilar em background para paralelizar
    start /b "" %GCC_PATH% -O1 -std=c99 -Isrc -c "!arquivo!" -o "!nome_obj!"
    set "QUESTAO_OBJECTS=!QUESTAO_OBJECTS! !nome_obj!"
)

:: Aguardar conclusao das questoes
:wait_questoes
tasklist /fi "imagename eq gcc.exe" | find "gcc.exe" >nul
if %errorlevel% == 0 (
    timeout /t 1 /nobreak >nul
    goto wait_questoes
)

:: Verificar se houve erros
set ERROR_FOUND=0
for /r "src\listas" %%f in (*.c) do (
    set "caminho_completo=%%~dpf"
    set "caminho_completo=!caminho_completo:%CD%\src\listas\=!"
    for /f "tokens=1 delims=\" %%a in ("!caminho_completo!") do set "nome_lista=%%a"
    set "nome_obj=build\questao_!nome_lista!_%%~nf.o"
    if not exist "!nome_obj!" (
        echo [ERRO] Falha ao compilar %%~nxf
        set ERROR_FOUND=1
    )
)

if %ERROR_FOUND% == 1 goto :error

echo === Linkando (otimizado) ===

:: Linkar com otimizacoes
%GCC_PATH% -O1 build/main.o build/menu_principal.o build/menu_lista.o build/menu_questao.o build/clean.o build/color.o build/logo.o build/colorPrint.o build/pilhaDinamica.o !QUESTAO_OBJECTS! -o "bin/APP.exe"
if %ERRORLEVEL% neq 0 (
    echo [ERRO] Falha ao linkar o executavel
    goto :error
)

echo.
echo === Compilacao concluida com sucesso! ===
echo Executavel criado: bin\APP.exe
echo.
goto :end

:error
echo.
echo === Falha na compilacao ===
echo Verifique os erros acima e tente novamente.
echo.
pause
exit /b 1

:end
if "%1"=="run" (
    echo === Executando o programa ===
    echo.
    bin\APP.exe
)

if "%1"=="" (
    pause
)