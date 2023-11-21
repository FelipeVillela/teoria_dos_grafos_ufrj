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


void test(FlowGraph& graph, int case_number, int graph_number=0) {
    // Essa função é utilizada para executar o estudo de caso de acordo com o número recebido
    if (case_number == 1) {
        auto start = chrono::high_resolution_clock::now();
                
        auto max_flow = graph.ford_fulkerson(1, 2);
        
        auto stop = chrono::high_resolution_clock::now();

        auto duration = duration_cast<chrono::microseconds>(stop - start);
        auto duration_ms = duration.count() / 1000.0;

        cout << to_string(graph_number) + " - max flow: " + to_string(max_flow) << endl;
        cout << to_string(graph_number) + " - duration: " + to_string(duration_ms) << endl;
            
    }
};





int main(int argc, char *argv[]) {
    try {
        // if (argc != 2) {
        //     printf("Usage: %s <number of test case> \n", argv[0]);
        //     return 1;
        // }

        // int case_number = atoi(argv[1]); //número do caso de estudo
        int case_number = 1;
        
        for (int i = 1; i <= 6; ++i) {
            FlowGraph g("./graphs/grafo_rf_" + to_string(i) + ".txt");

            test(g, case_number, i);
            
        }

                

    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}
