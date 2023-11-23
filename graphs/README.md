Esta pasta contém arquivos de grafo. Os grafos podem ser não direcionados e sem peso, não direcionados com peso ou redes de fluxo (direcionados, com peso e uma fonte e um destino).

Para o primeiro, o formato do nome deve ser `grafo_n.txt`, onde `n` é o número do grafo.

Para o segundo, o formato do nome deve ser `grafo_W_n.txt`, onde `n` é o número do grafo.

Para o terceiro, o formato do nome deve ser `grafo_rf_n.txt`, onde `n` é o número do grafo. Para este tipo, também é necessário que o grafo tenha o vértice de índice 1 como fonte e o 2 como destino.

## Formato do Arquivo de Grafo

Cada arquivo de grafo segue o seguinte formato:

- A primeira linha contém o número de vértices no grafo.
- As linhas seguintes contêm pares de vértices, indicando a existência de arestas entre eles.
- Se existir peso, ele deve ser representado após do par de vértice

Exemplo de arquivo de grafo (`grafo_1.txt`):
```
3
1 2
2 3
1 3
```

Neste exemplo, temos um grafo com 3 vértices e as seguintes arestas:
- Aresta entre o vértice 1 e o vértice 2.
- Aresta entre o vértice 2 e o vértice 3.
- Aresta entre o vértice 1 e o vértice 3.

Exemplo de arquivo de grafo (`grafo_W_1.txt`):
```
4
1 2 1
2 3 3
1 3 7
1 4 5
2 4 9
```

Neste exemplo, temos um grafo com 4 vértices e as seguintes arestas:
- Aresta entre o vértice 1 e o vértice 2 com peso 1.
- Aresta entre o vértice 2 e o vértice 3 com peso 3.
- Aresta entre o vértice 1 e o vértice 3 com peso 7.
- Aresta entre o vértice 1 e o vértice 4 com peso 5.
- Aresta entre o vértice 2 e o vértice 4 com peso 9.

Exemplo de arquivo de grafo (`grafo_rf_1.txt`):
```
7
1 3 5
1 5 3
3 7 3
5 3 2
5 7 2
5 4 4
6 3 5
6 2 5
7 6 4
7 4 1
4 2 2
```

Neste exemplo, temos um grafo com 7 vértices e as seguintes arestas:
- Aresta partindo do vértice 1 para o vértice 3 com peso 5.
- Aresta partindo do vértice 1 para o vértice 5 com peso 3.
- Aresta partindo do vértice 3 para o vértice 7 com peso 3.
- Aresta partindo do vértice 5 para o vértice 3 com peso 2.
- Aresta partindo do vértice 5 para o vértice 7 com peso 2.
- Aresta partindo do vértice 5 para o vértice 4 com peso 4.
- Aresta partindo do vértice 6 para o vértice 3 com peso 5.
- Aresta partindo do vértice 6 para o vértice 2 com peso 5.
- Aresta partindo do vértice 7 para o vértice 6 com peso 4.
- Aresta partindo do vértice 7 para o vértice 4 com peso 1.
- Aresta partindo do vértice 4 para o vértice 2 com peso 2.

Note que neste exemplo que apenas arestas saem do vértice 1 enquanto o 2 apenas recebe. Eles são a fonte e o destino da rede de fluxo.

Certifique-se de seguir esse formato ao criar ou modificar os arquivos de grafo nesta pasta.
Os grafos podem ser obtidos seguindo este [link](https://www.cos.ufrj.br/~daniel/grafos/).
