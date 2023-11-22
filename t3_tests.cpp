#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <queue>
#include <stack>
#include <ranges>
#include <numeric>
#include <thread>
#include <unordered_map>
#include <limits>
#include <set>
#include "lib/FlowGraph.h"


using namespace std;


void test(FlowGraph& graph, int graph_number=0, int iterations=10) {
    // Essa função é utilizada para executar o estudo de caso de acordo com o número recebido
    float max_flow;
    int source = 1;
    int sink = 2;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i <= iterations; ++i) {        

        max_flow = graph.ford_fulkerson(source, sink);
        
    }
    auto stop = chrono::high_resolution_clock::now();

    auto duration = duration_cast<chrono::microseconds>(stop - start);
    auto duration_ms = duration.count() / 1000.0;
    
    cout << "Fluxo máximo para o grafo " + to_string(graph_number) + " " + to_string(max_flow) << endl;
    cout << "Tempo de execução médio " + to_string(duration_ms/iterations) + " ms" << endl;

};





int main(int argc, char *argv[]) {
    try {
        
        for (int i = 1; i <= 6; ++i) {
            FlowGraph g("./graphs/grafo_rf_" + to_string(i) + ".txt");

            cout << "Iniciando teste para o grafo: " + to_string(i) << endl;
            test(g, i);
            cout << "---------------------" << endl;
            
        }

                

    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}
