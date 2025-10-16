# Sistema de Listas de Exercicios AED3 - UTFPR

Um sistema interativo em C para gerenciar e executar exercicios de **Algoritmos e Estruturas de Dados III** da Universidade Tecnologica Federal do Parana (UTFPR).

## Sobre o Projeto

Este sistema foi desenvolvido seguindo os principios de **arquitetura limpa** e **escalabilidade**, permitindo que novos exercicios sejam adicionados facilmente sem modificar o codigo principal. O programa utiliza uma interface de menus hierarquicos para navegar entre diferentes listas de exercicios e suas respectivas questoes.

## Caracteristicas Principais

- **Deteccao Automatica de Exercicios**: O sistema detecta dinamicamente quantos exercicios estao disponiveis
- **Interface Colorida**: Sistema de cores cross-platform (Windows/Linux)
- **Arquitetura Escalavel**: Adicione novos exercicios sem modificar codigo existente
- **Build Inteligente**: Sistema de compilacao que detecta automaticamente o compilador
- **Navegacao Intuitiva**: Menus hierarquicos com validacao de entrada
- **Cross-Platform**: Compativel com Windows e Linux

## Inicio Rapido

### Pre-requisitos
- Compilador GCC (MinGW no Windows)
- Sistema operacional Windows ou Linux

### Compilacao e Execucao

#### Compilar o projeto
```bash
make
```

#### Compilar e executar
```bash
make run
```

#### Limpar arquivos de build
```bash
make clean
```

#### Recompilar do zero
```bash
make rebuild
```

#### Executar manualmente
```bash
# Windows
bin/APP.exe

# Linux/macOS
bin/APP
```

## Estrutura do Projeto

```
Algoritimo-e-Estrutura-de-Dados-UTFPR/
├── README.md
├── Makefile               # Sistema de build cross-platform
├── src/
│   ├── interface/
│   │   ├── main.c         # Ponto de entrada do programa
│   │   ├── core/          # Logica dos menus
│   │   └── headlers/      # Headers da interface
│   ├── shared/
│   │   ├── core/          # Utilitarios (cores, limpeza, animacao, etc.)
│   │   └── headlers/      # Headers compartilhados
│   └── listas/            # Exercicios organizados por topico
│       ├── recursividade/               (12 questoes)
│       ├── ponteiros/                   (9 questoes)
│       ├── pilhaDinamica/               (9 questoes)
│       ├── filas/                       (8 questoes)
│       ├── listas/                      (9 questoes)
│       ├── listasDuplamenteEncadeadas/  (5 questoes)
│       ├── arvoresI/                    (5 questoes)
│       ├── arvoresBinarias/             (11 questoes: 1-8 + 9a,9b,9c)
│       ├── arvoresAVL/                  (8 questoes)
│       └── grafos/                      (17 questoes com sub-items)
├── bin/                   # Executavel compilado
└── build/                 # Arquivos objeto (.o)
```

### Estrutura de Cada Lista

```
[nome_da_lista]/
├── core/
│   ├── 1.c               # Implementacao da questao 1
│   ├── 2.c               # Implementacao da questao 2
│   └── ...
├── index.h               # Declaracoes de todas as questoes da lista
└── lista.txt             # Enunciados e solucoes das questoes
```

**Nota:** Cada questao implementa tres funcoes:
- `executarQuestao[Categoria][N]()` - Entrada principal (geralmente chama Predefinido)
- `executarQuestao[Categoria][N]Predefinido()` - Executa com valores pre-definidos
- `executarQuestao[Categoria][N]EntradaManual()` - Solicita entrada do usuario

## Interface do Sistema

### Menu Principal
```
=== Listas de Exercicios Disponiveis ===
 1. Recursividade - Exercicios sobre programacao recursiva
 2. Ponteiros - Exercicios sobre manipulacao de ponteiros
 3. Pilha Dinamica - Exercicios sobre implementacao e uso de pilhas dinamicas
 4. Filas - Exercicios sobre implementacao e uso de filas
 5. Listas - Exercicios sobre listas ligadas simples
 6. Listas Duplamente Encadeadas - Exercicios sobre listas duplamente ligadas
 7. Arvores I - Exercicios introdutorios sobre arvores
 8. Arvores Binarias - Exercicios sobre arvores binarias
 9. Arvores AVL - Exercicios sobre arvores AVL balanceadas
10. Grafos - Exercicios sobre teoria dos grafos e algoritmos
```

### Menu de Lista (Exemplo: Recursividade)
```
=== Recursividade ===
Exercicios disponiveis (12 questoes):
 1. Questao 01
 2. Questao 02
 3. Questao 03
 4. Questao 04
 5. Questao 05
 6. Questao 06
 7. Questao 07
 8. Questao 08
 9. Questao 09
10. Questao 10
11. Questao 11
12. Questao 12
```

### Menu de Questao
```
=== Recursividade ===
=== Questao 01 ===

Faca uma funcao recursiva que permita inverter um numero inteiro N.
Exemplo: 123 - 321

=== Menu da Questao ===
Escolha uma opcao a seguir:
 1. Ver logica utilizada para resolver
 2. Executar a questao
 3. Voltar a lista de questoes de Recursividade
 0. Voltar ao menu principal
> 
```

## Desenvolvimento

### Adicionando Novos Exercicios

1. **Crie o arquivo da questao:**
   ```bash
   # Exemplo: Adicionar questao 13 em recursividade
   touch src/listas/recursividade/core/13.c
   ```

2. **Declare as funcoes em `index.h`:**
   ```c
   // src/listas/recursividade/index.h
   void executarQuestaoRecursividade13(void);
   void executarQuestaoRecursividade13Predefinido(void);
   void executarQuestaoRecursividade13EntradaManual(void);
   ```

3. **Implemente as tres funcoes no arquivo `.c`:**
   ```c
   #include <stdio.h>
   #include "../index.h"
   #include "../../../shared/headlers/color.h"
   #include "../../../shared/headlers/colorPrint.h"
   #include "../../../shared/headlers/clean.h"

   // Funcao auxiliar com a logica principal
   static void logicaQuestao13(int valor) {
       printf("Processando valor: %d\n", valor);
       // ... implementacao da logica ...
   }

   // Entrada principal - chama a versao predefinida
   void executarQuestaoRecursividade13(void) {
       executarQuestaoRecursividade13Predefinido();
   }

   // Executa com valores pre-definidos para demonstracao
   void executarQuestaoRecursividade13Predefinido(void) {
       limparTela();
       printMensagemColoridaFormatted(YELLOW, "=== Recursividade - Questao 13 ===\n\n");
       resetColor();

       logicaQuestao13(123);  // Valor de exemplo
       pausar();
   }

   // Solicita entrada do usuario
   void executarQuestaoRecursividade13EntradaManual(void) {
       limparTela();
       printMensagemColoridaFormatted(YELLOW, "=== Recursividade - Questao 13 ===\n\n");
       resetColor();

       int valor;
       printf("Digite um valor: ");
       if (scanf("%d", &valor) != 1) {
           limparBufferTeclado();
           printMensagemColoridaFormatted(RED, "Entrada invalida!\n");
           pausar();
           return;
       }
       limparBufferTeclado();

       logicaQuestao13(valor);
       pausar();
   }
   ```

4. **Registre as funcoes em `menuQuestao.c`:**
   - Localize o array correspondente a sua categoria (ex: `todasFuncoes[1]` para Recursividade)
   - Adicione `executarQuestaoRecursividade13` na posicao [12] do array `todasFuncoes[1]`
   - Adicione `executarQuestaoRecursividade13EntradaManual` na mesma posicao do array `funcoesEntrada[1]`

5. **Atualize `lista.txt` com a documentacao:**
   ```
   QUESTAO 13:
   Enunciado: [Descricao completa do problema]

   Exemplo de entrada: [Exemplo de entrada]
   Exemplo de saida: [Exemplo de saida esperada]

   Logica utilizada:
   [Explicacao detalhada da sua solucao]
   - Algoritmo utilizado
   - Estruturas de dados
   - Detalhes de implementacao importantes

   ---
   ```

6. **Compile e teste:**
   ```bash
   make
   make run
   ```
   O sistema detectara automaticamente o novo arquivo!

### Convencoes de Nomenclatura

**Funcoes de Execucao:**
- Recursividade: `executarQuestaoRecursividade[N]()`
- Ponteiros: `executarQuestaoPonteiros[N]()`  
- Pilha Dinamica: `executarQuestaoPilhaDinamica[N]()`
- E assim por diante...

**Sub-questoes:**
- Para questoes com letras: `9a.c`, `9b.c`, `9c.c`
- Funcoes: `executarQuestao[Lista]9a()`

## Sistema de Cores

O projeto inclui um sistema de cores cross-platform que funciona tanto no Windows quanto no Linux:

- **YELLOW**: Numeros dos menus e prompts
- **CYAN**: Titulos de secoes  
- **GREEN**: Mensagens de sucesso
- **RED**: Mensagens de erro
- **WHITE**: Texto padrao


## Contribuicao

Este e um projeto academico para a UTFPR. Para contribuir:

1. Implemente novas solucoes nos arquivos `.c` existentes
2. Adicione novos exercicios seguindo a estrutura estabelecida
3. Teste no sistema Windows e Linux
4. Mantenha o padrao de codigo e comentarios em portugues

## Licenca

Este projeto e destinado para fins educacionais na UTFPR.

---

**Desenvolvido para AED3 - UTFPR Campus Santa Helena**  
*Sistema de Exercicios Interativo em C*
