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
build.bat
```
#### Compilar e executar imediatamente
```bash
build.bat run
```
#### Executar manualmente
```bash
bin/APP.exe
```

## Estrutura do Projeto

```
Algoritimo-e-Estrutura-de-Dados-UTFPR/
├── README.md
├── build.bat              # Sistema de build automatizado
├── src/
│   ├── interface/
│   │   ├── main.c         # Ponto de entrada do programa
│   │   ├── core/          # Logica dos menus
│   │   └── headlers/      # Headers da interface
│   ├── shared/
│   │   ├── core/          # Utilitarios (cores, limpeza, etc.)
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
├── headlers/
│   ├── 1.h               # Header da questao 1
│   ├── 2.h               # Header da questao 2
│   └── ...
├── core/
│   ├── 1.c               # Implementacao da questao 1
│   ├── 2.c               # Implementacao da questao 2
│   └── ...
├── index.h               # Agrega todos os headers
└── lista.txt             # Enunciados e solucoes
```

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

Digite o numero da lista que deseja ou 0 para sair
> 
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

Digite o numero do exercicio que deseja ou 0 para voltar
> 
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

1. **Crie os arquivos da questao:**
   ```bash
   # Na pasta da lista apropriada (ex: recursividade)
   touch src/listas/recursividade/headlers/13.h
   touch src/listas/recursividade/core/13.c
   ```

2. **Implemente o header (.h):**
   ```c
   #ifndef RECURSIVIDADE_13_H
   #define RECURSIVIDADE_13_H
   
   void executarQuestaoRecursividade13(void);
   
   #endif
   ```

3. **Implemente a solucao (.c):**
   ```c
   #include <stdio.h>
   #include "../headlers/13.h"
   #include "../../../shared/headlers/color.h"
   
   void executarQuestaoRecursividade13(void) {
       printf("=== Questao 13 - Recursividade ===\n");
       // Sua implementacao aqui
   }
   ```

4. **Atualize o switch case em `menuQuestao.c`:**
   ```c
   case 13:
       executarQuestaoRecursividade13();
       break;
   ```

5. **Compile:** O sistema detectara automaticamente o novo arquivo!

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

## Estatisticas do Projeto

- **Total de Exercicios**: 93 questoes implementadas
- **Listas Suportadas**: 10 categorias diferentes
- **Arquivos de Codigo**: ~200 arquivos (.c + .h)
- **Linhas de Codigo**: ~3000+ linhas
- **Compatibilidade**: Windows + Linux

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