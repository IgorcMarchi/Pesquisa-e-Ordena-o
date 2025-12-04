RESUMO EXECUTIVO - PROJETO B-TREE
================================

ESTRUTURA DO PROJETO
====================

Arquivos de Codigo:
- function.h       -> Header com definicoes e declaracoes
- function.c       -> Implementacao das funcoes B-Tree
- main.c           -> Interface de usuario e file I/O

Arquivos de Dados:
- operacoes.txt    -> Comandos INSERT/SEARCH para testes
- RELATORIO_TESTES.txt -> Resultados detalhados dos testes

Executaveis:
- programa.exe     -> Binario compilado pronto para usar

Scripts:
- teste.sh         -> Script bash para testes
- teste.ps1        -> Script PowerShell para testes

---

FUNCIONALITIES IMPLEMENTADAS
============================

1. ESTRUTURA B-TREE
   - Nos com multiplas chaves (ate 2*t-1)
   - Filhos organizados em array de IDs
   - Suporte para qualquer grau t >= 2
   - Balanceamento automatico

2. DISCO SIMULADO
   - Array disk[] simula armazenamento em paginas
   - ID unico por no (page_id)
   - Contador NUM_PAGES controla alocacao
   - CONTA_LEITURA e CONTA_ESCRITA monitoram I/O

3. OPERACOES BASICAS
   - INSERT: com split preventivo
   - SEARCH: busca binaria recursiva
   - SPLIT: divide nos cheios mantendo propriedades

4. INTERFACE
   - Modo Leitura: executa arquivo operacoes.txt
   - Modo Escrita: adiciona operacoes individuais
   - Visualizacao: exibe arvore em formato hierarquico

5. RELATORIO I/O
   - Cada operacao mostra leituras/escritas
   - Contadores zerados apos cada operacao
   - Rastreamento completo do acesso ao disco

---

COMO USAR
=========

Compilacao:
  gcc -o programa function.c main.c

Execucao:
  .\programa

Entrada Interativa:
  1. Digite o grau minimo t da Arvore B (minimo 2)
  2. Escolha modo:
     - 1: Ler arquivo operacoes.txt
     - 2: Escrever comando individual no arquivo

Arquivo operacoes.txt:
  Formato: INSERT <valor>
  Formato: SEARCH <valor>
  
  Exemplo:
  INSERT 10
  INSERT 20
  SEARCH 10

---

RESULTADOS DOS TESTES
=====================

Teste 1 (t=3, modo leitura):
✓ 15 INSERTs processados
✓ 10 SEARCHes realizados (encontrados e nao encontrados)
✓ Arvore com 2 niveis (raiz + folhas)
✓ Contadores de I/O funcionando

Teste 2 (t=2, modo leitura):
✓ 15 INSERTs processados
✓ 10 SEARCHes realizados
✓ Arvore com 3 niveis (mais profunda)
✓ Maior consumo de I/O devido a arvore mais profunda

Teste 3 (modo escrita - INSERT):
✓ Comando INSERT executado
✓ Arquivo atualizado
✓ Arvore visualizada

Teste 4 (modo escrita - SEARCH):
✓ Comando SEARCH executado
✓ Tratamento correto de arvore vazia

---

OBSERVACOES IMPORTANTES
=======================

1. Grau t afeta profundidade:
   - t maior = arvore mais rasa = menos I/O
   - t menor = arvore mais profunda = mais I/O

2. Split ocorre quando no atinge 2*t-1 chaves
   - Chave do meio promovida ao pai
   - Cria novo no irmao com chaves restantes
   - Pai pode ficar cheio (causando split em cascata)

3. Contadores I/O reset apos cada operacao
   - Permite analisar custos isolados
   - SEARCH nao causa escritas
   - INSERT pode causar multiplas escritas (splits)

4. Sem acentuacao no codigo
   - Compatibilidade total com compiladores C
   - Output legivel em qualquer sistema

---

PROXIMOS PASSOS OPCIONAIS
==========================

1. Adicionar persistencia em arquivo real
2. Implementar REMOVE (delecao de chaves)
3. Exportar relatorio de I/O para CSV
4. Teste de stress com milhares de chaves
5. Comparacao com outras estruturas (ABB, Hash, etc)

---

Projeto completado com sucesso!
Codigo pronto para pesquisa academica.