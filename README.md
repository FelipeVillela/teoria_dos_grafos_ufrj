# teoria_dos_grafos_ufrj

Este repositório foi criado para fins academicos para o estudo de grafos. O arquivo main.cpp contém um código em C++ para realizar diferentes estudos de caso em grafos utilizando a representação do mesmo em forma de lista de adjacências e matriz de adjacências. O código utiliza a Biblioteca Padrão do C++ e fornece funcionalidades como busca em largura (BFS), busca em profundidade (DFS), cálculo de distâncias, determinação de componentes conexas e cálculo do diâmetro do grafo.

## Compilação

Para compilar o código, você precisará do compilador g++-10 para que os recursos da versão 20 do C++ sejam utilizadas. Com o compilador instalado, basta executar o seguinte comando que o executável main.o será criado.

```bash
make
```

## Utilização

Ao compilar utilizando o comando anterior, um executável main.o é criado. Em um terminal e estando na raiz do projeto, basta inserir o comando abaixo que o programa será executado. Note também que para utilizá-lo, deve-se informar o número do estudo de caso (será detalhado mais abaixo). Vale ressaltar que para o funcionamento do programa, o grafo deve estar no diretório graphs e seu nome deve estar no formato grafo_n.txt (n deve ser substituido por um número). Mais detalhes podem ser encontrados no arquivo README que está dentro do diretório.

No exemplo abaixo, o programa está sendo executado e o parâmetro 1 representa o número do estudo de caso.

```bash
./main.o 1
```

# Estudos de Caso
O código presente no arquivo main.cpp contém uma função chamada test que executa diferentes estudos de caso de acordo com o número recebido como parâmetro na função.

1. **Medição do Tempo de Execução da BFS**  
   Neste estudo de caso, o código mede o tempo de execução da busca em largura (BFS) em 10 iterações.

2. **Medição do Tempo de Execução da DFS**  
   Neste estudo de caso, o código mede o tempo de execução da busca em profundidade (DFS) em 10 iterações.

3. **Determinação do Pai dos Vértices 10, 20 e 30**  
   Este estudo de caso determina o pai dos vértices 10, 20 e 30 tanto na BFS quanto na DFS.

4. **Medição da Distância entre Pares de Vértices**  
   Neste estudo de caso, o código mede a distância entre os pares de vértices (10,20), (10,30) e (20,30) usando a DFS.

5. **Quantidade de Componentes Conexas**  
   Este estudo de caso determina a quantidade de componentes conexas do grafo e o tamanho da maior e da menor componente.

6. **Medição do Diâmetro do Grafo**  
   Neste estudo de caso, o código mede o diâmetro do grafo.

