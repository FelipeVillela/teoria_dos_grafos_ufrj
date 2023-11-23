# teoria_dos_grafos_ufrj

Este repositório foi criado para fins academicos para o estudo de grafos. Este projeto é dividido em etapas de 3 trabalhos práticos. O objetivo é ao longo do curso desenvolver uma biblioteca que irá instanciar grafos e executas métodos que envolvem buscas, medição de distâncias, diâmetro, entre outros métodos relacionados a grafos. Na raiz, encontramos os arquivos em C++ responsáveis por executar os testes de acordo com os estudos de caso de cada etapa do projeto. Essas etapas estarão descritas mais a frente. 

## Organização do projeto

O repositório contém alguns arquivos na raiz seguindo o padrão `tp*_tests.cpp` onde `*` representa um número. Nesse arquivo, são realizados os estudos de caso referentes ao trabalho prático em questão. Atualmente, existem dois trabalhos práticos.
Dentro do diretório `lib` estão contidos os arquivos de biblioteca de grafos. O arquivo `Graph.h` contém a implementação de classe para representar grafos não-direcionados e sem pesos. Herdando dessa classe, os arquivos `AdjacencyMatrixGraph.h` e `AdjacencyListGraph.h` são utilizados para representar o objeto grafo, respectivamente, como matriz de adjacências e lista de adjacências. A biblioteca `WeightedGtaph.h` representa grafos não-direcionados com peso como lista de adjacência (não foi justificada a necessidade de se ter também a representação em matriz de adjacências).
O arquivo `Makefile` é utilizado para armazenar instruções de compilação, muito comum em projetos escritos em C/C++. No próximo tópico, será explicado como o programa pode ser compilado.


## Compilação

Para compilar o código, você precisará do compilador g++-10 para que os recursos da versão 20 do C++ sejam utilizadas. Com o compilador instalado, basta executar o seguinte comando que os executáveis referentes aos arquivos na forma `tp*_tests.cpp` sejam criados. Com dois arquivos de código, serão criados os executáveis `tp1_tests.o` e `tp1_tests.o`.

```bash
make
```

Caso queira compilar apenas um código em específico, basta executar o comando anterior acompanhado do nome do arquivo. No exemplo abaixo, somente o executável `tp1_tests.o` será criado.

```bash
make tp1_tests.o
```

Caso queira modificar o código e criar um novo arquivo executável, o comando seguinte garante que todos os executáveis serão removidos. Após isso, poderá ser feito uma nova compilação.

```bash
make clean
```

## Trabalho prático 1 - TP1

O objetivo do primeiro trabalho é realizar diferentes estudos de caso que serão descritos mais a frente. Utilizando a representação na memória do grafo em forma de lista de adjacências e matriz de adjacências, o programa, escrito em C++, deverá ser capaz de executar métodos de busca a como busca em largura (BFS), busca em profundidade (DFS), cálculo de distâncias, determinação de componentes conexas e cálculo do diâmetro do grafo. Neste primeiro momento, serão utilizados grafos não-direcionados e sem pesos.

### Utilização

Ao compilar utilizando um dos comandos descritos anteriormente, o executável `tp1_tests.o` será criado. Em um terminal e estando na raiz do projeto, basta inserir o comando abaixo que o programa será executado. Note também que para utilizá-lo, deve-se informar o número do estudo de caso (será detalhado mais abaixo) e o tipo de representação desejada (`l` para lista de adjacência e `m` para matriz de adjacência). Vale ressaltar que para o funcionamento do programa, o grafo deve estar no diretório graphs e seu nome deve estar no formato `grafo_n.txt` (`n` deve ser substituido por um número). Mais detalhes podem ser encontrados acessando o diretório [graphs](https://github.com/FelipeVillela/teoria_dos_grafos_ufrj/tree/main/graphs).

No exemplo abaixo, o programa está sendo executando o estudo de caso de número 1 com o grafo representado em matriz de adjâcencias.

```bash
./t1_tests.o 1 m
```

### Estudos de Caso
O código presente no arquivo `tp1_tests.cpp` contém uma função chamada `test` que executa diferentes estudos de caso de acordo com o número recebido como parâmetro na função.

1. **Medição do Tempo de Execução da BFS**  
   Neste estudo de caso, o código mede o tempo de execução da busca em largura (BFS) em 10 iterações.

2. **Medição do Tempo de Execução da DFS**  
   Neste estudo de caso, o código mede o tempo de execução da busca em profundidade (DFS) em 10 iterações.

3. **Determinação do Pai dos Vértices 10, 20 e 30**  
   Este estudo de caso determina o pai dos vértices 10, 20 e 30 tanto na BFS quanto na DFS. O pai de um vértice é aquele que o descobriu na execução do algoritmo.

4. **Medição da Distância entre Pares de Vértices**  
   Neste estudo de caso, o código mede a distância entre os pares de vértices (10,20), (10,30) e (20,30) usando a DFS.

5. **Quantidade de Componentes Conexas**  
   Este estudo de caso determina a quantidade de componentes conexas do grafo e o tamanho da maior e da menor componente.

6. **Medição do Diâmetro do Grafo**  
   Neste estudo de caso, o código mede o diâmetro do grafo.

## Trabalho prático 2 - TP2

Nessa etapa, a biblioteca deverá ser capaz de trabalhar com grafos não-direcionados e com pesos. Os pesos poderão ser números reais, porém, não serão implementados algoritmos em que se leva em conta pesos negativos. O algoritmo utilizado para realizar os testes será o de Dijkstra. Este poderá ser executado de duas formas diferentes. No algoritmo, é necessário utilizar uma lista contendo vértices visitados. Por essa lista poder variar bastante, pode ser interessante utilizar um heap, já que ele tem complexidade de busca, atualização e remoção menor que a de um vetor. Com isso, a biblioteca será capaz de executar o algoritmo com heap ou com vetor, afim de comparar a eficiência na prática. Como o objetivo não é comparar o tamanho dos grafos na memória nas diferentes representações (matriz e lista), foi determinado que todo grafo seria representado como lista de adjacência.

### Utilização

Ao compilar utilizando um dos comandos descritos no tópico de compilação, o executável `tp2_tests.o` será criado. Em um terminal e estando na raiz do projeto, basta inserir o comando abaixo que o programa será executado. Note também que para utilizá-lo, deve-se informar o número do estudo de caso (será detalhado mais abaixo) e o tipo de estrutura da lista de vértices visitados desejada (`v` para vetor e `h` heap). Vale ressaltar que para o funcionamento do programa, o grafo deve estar no diretório graphs e seu nome deve estar no formato `grafo_W_n.txt` (`n` deve ser substituido por um número). Mais detalhes podem ser encontrados acessando o diretório [graphs](https://github.com/FelipeVillela/teoria_dos_grafos_ufrj/tree/main/graphs).

No exemplo abaixo, o programa está sendo executando o estudo de caso de número 1 e a estrutura de heap para a lista de vértices visitados.

```bash
./t2_tests.o 1 h
```

### Estudos de Caso
O código presente no arquivo `tp2_tests.cpp` contém uma função chamada `test` que executa diferentes estudos de caso de acordo com o número recebido como parâmetro na função.

1. **Distâncias e caminhos**  
   A partir do vértice 10, o programa irá medir a distância aos vértices 20,30,40,50,60 além de retornar o caminho entre os pares. Pode ser executado com vetor ou heap

2. **Medição do Tempo de Execução do algoritmo de Dijkistra**  
   O programa executa o algoritmo de Dijkistra diversas vezes a partir de um vértice aleatório com a finalidade de obter um tempo médio e comparar o tempo de execução ao utilizar vetor e heap. O parâmetro de selecionar a estrutura de lista desejada não é levado em conta aqui, já que o programa executa as duas implementações do algoritmo.

3. **Distâncias e caminhos entre pesquisadores**  
   Aqui é utilizado um grafo que codifica o relacionamento entre pesquisadores que colaboraram. O objetivo é, dada uma lista de pesquisadores, encontrar a distância e o caminho com o autor do algoritmo desse estudo, Edsger W. Dijkstra.

## Trabalho prático 2 - TP3

No terceiro e último trabalho, a biblioteca deverá ser capaz de trabalhar com grafos direcionados e com pesos. Também foi implementado o algoritmo de Floyd-Fulkerson

### Utilização

Ao criar o arquivo utilizando um dos comandos descritos no tópico de compilação, o executável `tp3_tests.o` será criado. Em um terminal e estando na raiz do projeto, basta inserir o comando abaixo que o programa será executado.
Este teste consiste em apenas um estudo de caso, portanto, não é preciso especificar o número do estudo de caso como nos testes anteriores, porém, existem parâmetros opcionais que serão descritos abaixo.

`-i` número de execuções para cada grafo: é utilizado para calcular o tempo médio de execução. Caso não seja informado, o valor padrão é igual a 10.

`-f` Parâmetro que define se será gerado ou não um arquivo de texto com as alocações de fluxo para cada grafo. Deve ser passado o número 1 para gerar o arquivo e 0 para não gerar. Caso não seja informado, o valor padrão é igual a 0.

Vale ressaltar que para o funcionamento do programa, o grafo deve estar no diretório graphs e seu nome deve estar no formato `grafo_rf_n.txt` (`n` deve ser substituido por um número). Mais detalhes podem ser encontrados acessando o diretório [graphs](https://github.com/FelipeVillela/teoria_dos_grafos_ufrj/tree/main/graphs).

No exemplo abaixo, o programa está sendo executando o algoritmo Floyd-Fulkerson 10 vezes e não irá gerar o arquivo com as alocações de fluxo. Apoós a execução, será retornado no terminal o fluxo máximo e a média do tempo de execução para cada grafo.

```bash
./t3_tests.o -i 10 -f 0
```

### Estudos de Caso
O código presente no arquivo `tp3_tests.cpp` contém uma função chamada `test` que executa apenas um estudo de caso.

1. **Fluxo máximo e tempo de execução do algoritmo Floyd-Fulkerson**  
   O programa irá executar um número de vezes igual ao número informado no parâmetro ao executar o programa.


