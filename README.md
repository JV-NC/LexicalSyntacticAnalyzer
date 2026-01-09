<h1 align='center'>
         🔍 Analisador Léxico-Sintático
</h1>

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++">
  <img src="https://img.shields.io/badge/GCC-orange?style=for-the-badge&logo=gnu-compiler-collection&logoColor=white" alt="GCC">
  <img src="https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54" alt="Python">
  <img src="https://img.shields.io/badge/Ubuntu-E95420?style=for-the-badge&logo=ubuntu&logoColor=white" alt="Ubuntu">
  <img src="https://img.shields.io/badge/Visual_Studio_Code-007ACC?style=for-the-badge&logo=visual-studio-code&logoColor=white" alt="Visual Studio Code">
  <img src="https://img.shields.io/badge/Git-F05032?style=for-the-badge&logo=git&logoColor=white" alt="Git">
  <img src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white" alt="GitHub">
  
<img src="https://img.shields.io/badge/-Makefile-red?style=for-the-badge&logo=gnu-make&logoColor=white" alt="Makefile">
<img src="https://img.shields.io/badge/doxygen-2C4AA8?style=for-the-badge&logo=doxygen&logoColor=white" alt="Doxygen"></p>
<div align='center'>
Laboratório de Algoritmos e Estruturas de Dados I <br>
Engenharia de Computação <br>
Prof. Michel Pires da Silva <br>
CEFET-MG Campus V <br>
2026/1  
</div>

<details>
<summary><h2>📋 Índice</h2></summary>
</details>

## 📝 Introdução

Este projeto foi desenvolvido como trabalho de aproveitamento da disciplina de Laboratório de Algorítmos e Estruturas de Dados I (LAEDI), sob a orientação do professor [Michel Pires Silva](https://github.com/mpiress). Este trabalho tem como objetivo principal o desenvolvimento de um sistema denominado Analisador Léxico-Sintático (LSA), capaz de avaliar diferentes métricas associadas à qualidade textual.
O LSA é responsável por processar um texto de entrada e extrair informações estatísticas, estruturais e semânticas sobre seu conteúdo. A partir da leitura sequencial do texto, o sistema identifica palavras (*tokens*), expressões compostas, sentenças, parágrafos e símbolos de pontuação, organizando esses dados por meio de estruturas de dados implementadas manualmente, como:
* Listas encadeadas (LinkedList).
* Pilhas (Stack).
* Filas (Queue).
* Tabelas hash (HashTable).
Todas as estruturas foram implementadas durante o projeto, sem o uso de bibliotecas prontas da Standard Template Library (STL), respeitando as restrições e objetivos didáticos da disciplina aproveitada.
Durante o processamento do texto, o sistema realiza diversas tarefas, entre elas:
* Contagem da frequência de palavras e expressões.
* Identificação de palavras irrelevantes (*stop words*).
* Registro detalhado das ocorrências dos *tokens* (parágrafo, sentença, linha e posição).
* Verificação do balanceamento de símbolos de pontuação.
* Geração de estatísticas por sentença e por parágrafo.
* Construção da distribuição de comprimento das palavras.
Além disso, o sistema incorpora análise de desempenho de algoritmos de ordenação, comparando *MergeSort* e *QuickSort* usando diferentes comparadores e variáveis de ordenação. Para cada algoritmo, são coletadas as seguintes métricas:
* Número de comparações
* Número de trocas
* Tempo de execução
Esses dados e a distribuição por comprimento são exportados no formato `.csv` e posteriormente utilizados para plotagem de gráficos com scripts em Python.
Como parte da automação do projeto, foi desenvolvido pensando na execução em *pipeline* a partir do Makefile, tendo a seguinte ordem:
1. Compilação e criação dos objetos (.o) do código em C++.
2. Execução do analisador sobre o texto de entrada.
3. Geração do ``output.txt`` e dos arquivos `.csv`.
4. Plotagem dos gráficos utilizando ``pandas`` e ``matplolib`` em Python.
Os textos utilizados para testar e analisar o projeto foram Dom Casmurro e a Semana Machado de Assis, ambas obras de Machado de Assis, oferecidas inicialmente para o trabalho de aproveitamento. Estes materiais foram selecionados devido ao tamanho textual e riqueza linguística, possibilitando executar o sistema em um cenário realista e desafiador para análise.
Com este trabalho, busca-se consolidar os conceitos fundamentais da disciplina de LAEDI, demonstrando o conhecimento do autor sobre a disciplina em uma aplicação real, mensurável e extensível.

## 🎯Objetivos

### Objetivo Geral
O objetivo geral deste trabalho é projetar e implementar um Analisador Léxico-Sintático para processamento de texto em linguagem natural, capaz de identificar tokens, sentenças, parágrafos, expressões e padróes sintáticos, utilizando estruturas de dados fundamentais e algoritmos de ordenação, com foco em corretude, elegância e desempenho computacional.
Busca-se aplicar, de forma prática os conceitos de Algoritmos e Estruturas de Dados I, integrando análise léxica, controle sintático básico (balanceamento de símbolos) e geração de estatísticas textuais relevantes, podendo ser relacionado a disciplinas posteriores do curso, como Linguagens de Programação, Linguagens Formais e Autômatos e Compiladores.
#### Métricas de Desempenho
A avaliação do sistema desenvolvido considera os seguintes critérios:
* **Tempo de Execução:**
  Tempo necessário para realizar a análise completa do texto e executar os algoritmos de ordenação, medido em segundos.
* **Uso de Estruturas de Dados:**
  Aplicação correta e elegante de estruturas de dados como pilhas, filas, listas encadeadas e tabelas hash, respeitando suas características.
* **Complexidade assintótica:**
  Análise do comportamento assintótico das principais operações, como inserções em tabelas hash, percursos em listas encadeadas e algoritmos de ordenação (*MergeSort* e *QuickSort*).
* **Qualidade da Análise Textual:**
  Capacidade do sistema em extrair informações léxicas e estruturais relevantes, como frequência de tokens, distribuição de comprimento das palavras e identificação de expressões.

### Objetivos Específicos
* **Implementar um analisador léxico para textos em linguagem natural:**
  Identificar e normalizar tokens (palavras), removendo *stopwords*, tratando abreviações, números e caracteres especiais, além de registrar ocorrências detalhadas (parágrafo, sentença, linha e posição).
* **Realizar análise sintática básica do texto:**
  Verificar o balanceamento de símbolos de pontuação (parênteses, colchetes, chaves, aspas), utilizando estruturas de pilha, identificando inconsistências sintáticas.
* **Organizar informações textuais por sentenças e parágrafos:**
  Estruturar os dados analisados em níveis hierárquicos (texto → parágrafos → sentenças), armazenando estatísticas como número de palavras, palavras sem *stopwords* e comprimento médio, além de facilitar a gestão das estruturas de dados globais, como a listas de tabela hash para tokens e expressões.
* **Detectar e contabilizar expressões pré-definidas:**
  Identificar expressões compostas ao longo do texto, registrando sua frequência e linhas de ocorrência.
* **Construir distribuições estatísticas do texto:**
  Gerar a distribuição de comprimento das palavras, utilizando uma estrutura de mapa (`IntIntMap`) implementada sem dependência da STL.
* **Aplicar e comparar algoritmos de ordenação:**
  Implementar e avaliar *MergeSort* e *QuickSort* para diferentes critérios de ordenação (ordem alfabética e frequência), coletando métricas de comparações, trocas e tempo de execução.
* **Exportar dados para análise externa:**
  Gerar arquivos `.csv` contendo métricas de ordenação e distribuições estatísticas, possibilitando a visualização gráfica por meio de scripts em Python.
* **Documentar o projeto com Doxygen:**
  Produzir documentação técnica completa do código-fonte, incluindo descrição de classes, métodos, parâmetros e estruturas de dados utilizadas.
