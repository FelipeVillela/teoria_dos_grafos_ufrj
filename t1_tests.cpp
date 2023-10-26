#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <queue>
#include <stack>
#include <ranges>
#include <numeric>
#include <thread>
#include "lib/Graph.h"
#include "lib/AdjacencyMatrixGraph.h"
#include "lib/AdjancencyListGraph.h"

using namespace std;


void test(Graph& graph, int case_number) {
    // Essa função é utilizada para executar o estudo de caso de acordo com o número recebido


    if (case_number == 1) {
        // Medição do tempo de execução da BFS

        auto start = chrono::high_resolution_clock::now();
        for (int i = 1; i <= 10; ++i) {
            graph.bfs(i % graph.node_count + 1);
        }
        auto stop = chrono::high_resolution_clock::now();

        auto duration = duration_cast<chrono::microseconds>(stop - start);
        cout << "Time taken by BFS: " << duration.count() / (1000.0 * 10) << " milliseconds" << endl;
    }


    if (case_number == 2) {
        // Medição do tempo de execução da DFS

        auto start = chrono::high_resolution_clock::now();
        for (int i = 1; i <= 10; ++i) {
            graph.dfs(i % graph.node_count + 1, (i + 1) % graph.node_count + 1);
        }
        auto stop = chrono::high_resolution_clock::now();

        auto duration = duration_cast<chrono::microseconds>(stop - start);
        cout << "Time taken by DFS: " << duration.count() / (1000.0 * 10) << " milliseconds" << endl;
    }


     if (case_number == 3) {
        // Determina o pai dos vértices 10, 20 e 30 tanto na BFS quanto na DFS

        cout << "BFS parent of vertex 10: " << graph.bfs(1, 10)[1] << endl;
        cout << "BFS parent of vertex 20: " << graph.bfs(2, 20)[1] << endl;
        cout << "BFS parent of vertex 30: " << graph.bfs(3, 30)[1] << endl;

        cout << "DFS parent of vertex 10: " << graph.dfs(1, 10)[1] << endl;
        cout << "DFS parent of vertex 20: " << graph.dfs(2, 20)[1] << endl;
        cout << "DFS parent of vertex 30: " << graph.dfs(3, 30)[1] << endl;
    }


     if (case_number == 4) {
        // Medição da distância entre os pares de vértices (10,20), (10,30), (20,30)

        cout << "Distance between vertices 10 and 20: " << graph.dfs(10, 20).size() << endl;
        cout << "Distance between vertices 10 and 30: " << graph.dfs(10, 30).size() << endl;
        cout << "Distance between vertices 20 and 30: " << graph.dfs(20, 30).size() << endl;
    }


    if (case_number == 5) {
        // Obtém a quantidade de componentes conexas do grafo e qual o tamanho da maior e da menor componente

        auto components = graph.connected_components();
        cout << "Number of connected components: " << components.size() << endl;

        int max_size = 0, min_size = graph.node_count;
        for (const auto &component: components) {
            max_size = max(max_size, static_cast<int>(component.size()));
            min_size = min(min_size, static_cast<int>(component.size()));
        }

        cout << "Size of the largest connected component: " << max_size << endl;
        cout << "Size of the smallest connected component: " << min_size << endl;
    }


   if (case_number == 6) {
        // Medição do diâmetro do grafo

        int diameter = graph.diameter();
        cout << "Diameter of the graph: " << diameter << endl;
   }
}


int main(int argc, char *argv[]) {
    try {
        if (argc != 3) {
            printf("Usage: %s <number of test case> <l for adjacency list, m for adjacency matrix>\n", argv[0]);
            return 1;
        }

        int case_number = atoi(argv[1]); //número do caso de estudo
        char graph_type = argv[2][0];    // Tipo de grafo (l ou m)

        if (graph_type != 'l' && graph_type != 'm') {
            cerr << "Invalid graph type. Use 'l' for adjacency list or 'm' for adjacency matrix." << endl;
            return 1;
        }

        for (int i = 1; i <= 6; ++i) {

            if (graph_type == 'l') {
                cout << "Testing Adjacency List Graph " << i << ":" << endl;

                AdjacencyListGraph adj_list_graph("./graphs/grafo_" + to_string(i) + ".txt");
                test(adj_list_graph, case_number);
                
            } else if (graph_type == 'm') {
                cout << "Testing Adjacency Matrix Graph " << i << ":" << endl;

                MatrixAdjacencyGraph adj_matrix_graph("./graphs/grafo_" + to_string(i) + ".txt");
                test(adj_matrix_graph, case_number);

            }

            cout << endl;
        }

    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}
