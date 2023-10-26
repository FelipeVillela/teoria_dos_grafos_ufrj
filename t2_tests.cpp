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
#include "lib/WeightedGraph.h"
#include "lib/LabeledWeightedGraph.h"

using namespace std;


void writeLineToFile(const string& filename, const string& line) {
    ofstream outputFile(filename, ios::app); // Abra o arquivo de saída em modo de anexação

    if (outputFile.is_open()) {
        // Redirecione a saída para o arquivo
        outputFile << line << endl;

        // Feche o arquivo quando terminar
        outputFile.close();
    } else {
        cerr << "Não foi possível abrir o arquivo de saída: " << filename << endl;
    }
}


void test(WeightedGraph& graph, int case_number, char queue_structure, int graph_number=0) {
    // Essa função é utilizada para executar o estudo de caso de acordo com o número recebido
    if (case_number == 1) {

        cout << to_string(graph.node_count) << endl;
            
        int startNode = 10;
        vector<float> dist;
        string structure_name;

       for (int endNode = 20; endNode <= 60; endNode += 10) {
            cout << "Distância de " << startNode << " até " << endNode << endl;

            if (queue_structure == 'h') {
                structure_name = 'heap';
                dist = graph.dijkstra_heap(startNode);
            }
            if (queue_structure == 'v') {
                structure_name = 'vector';
                dist = graph.dijkstra_vector(startNode);
            }

            float float_dist = dist[endNode];

            cout << structure_name + ": " + to_string(float_dist) << endl;

            writeLineToFile("dist_" + to_string(startNode) + "_" + to_string(endNode) + ".txt", "\nGraph " + to_string(graph_number) + ": " + to_string(float_dist) + "\n");
        }
                
            
    }

    if (case_number == 2) {
        // Medição do tempo de execução do dijkstra

        int total_iterations = 10;
        float total_vector_time = 0;
        float total_heap_time = 0;
        float duration_vector_ms;
        float duration_heap_ms;

        writeLineToFile("output_heap.txt", "\nGraph " + to_string(graph_number));
        writeLineToFile("output_vector.txt", "\nGraph " + to_string(graph_number));


        for (int i = 1; i <= total_iterations; ++i) {
            
            int randomNode = (rand() % graph.node_count) + 1;

            // Vector
            auto start_vector = chrono::high_resolution_clock::now();
            
            graph.dijkstra_vector(randomNode);
            
            auto stop_vector = chrono::high_resolution_clock::now();

            auto duration_vector = duration_cast<chrono::microseconds>(stop_vector - start_vector);
            duration_vector_ms = duration_vector.count() / 1000.0;

            total_vector_time += duration_vector_ms;

            cout << "Time taken by Dijkstra with vector starting in node " + to_string(randomNode) + ": " << to_string(duration_vector_ms) << " milliseconds" << endl;
            
            writeLineToFile("output_vector.txt", "Time taken by Dijkstra with vector starting in node " + to_string(randomNode) + ": " + to_string(duration_vector_ms) + " milliseconds");
            //end Vector

            //Heap
            auto start_heap = chrono::high_resolution_clock::now();
            
            graph.dijkstra_heap(randomNode);
            
            auto stop_heap = chrono::high_resolution_clock::now();

            auto duration_heap = duration_cast<chrono::microseconds>(stop_heap - start_heap);
            duration_heap_ms = duration_heap.count() / 1000.0;

            total_heap_time += duration_heap_ms;
            
            cout << "Time taken by Dijkstra with heap starting in node " + to_string(randomNode) + ": " << duration_heap_ms << " milliseconds" << endl;
            
            writeLineToFile("output_heap.txt", "Time taken by Dijkstra com heap no node " + to_string(randomNode) + ": " + to_string(duration_heap_ms) + " milliseconds");
            //End heap
        }

        writeLineToFile("output_vector.txt", "\nTotal exec time: " + to_string(total_vector_time) + " milliseconds");
        writeLineToFile("output_vector.txt", "\nMean exec time: " + to_string(total_vector_time / total_iterations) + " milliseconds");

        writeLineToFile("output_heap.txt", "\nTotal exec time: " + to_string(total_heap_time) + " milliseconds");
        writeLineToFile("output_heap.txt", "\nMean exec time: " + to_string(total_heap_time / total_iterations) + " milliseconds");

    }
};





int main(int argc, char *argv[]) {
    // auto g = Graph("./graphs/grafo_W_1.txt");
    // return 0;

    try {
        if (argc != 3) {
            printf("Usage: %s <number of test case> <v for vector, h for heap>\n", argv[0]);
            return 1;
        }

        int case_number = atoi(argv[1]); //número do caso de estudo
        char queue_structure = argv[2][0];    // Estrutura da fila grafo (v ou h)
        string filename = "output.txt";

        if (queue_structure != 'v' && queue_structure != 'h') {
            cerr << "Invalid data structure. Use 'v' for vector or 'h' for heap." << endl;
            return 1;
        }

        if (case_number <= 2) {
            for (int i = 1; i <= 5; ++i) {

                if (queue_structure == 'h') {
                    cout << "Testing Graph " << i << " with heap:" << endl;

                    writeLineToFile(filename, "\nTesting Graph " + to_string(i) + " with heap:");

                }

                if (queue_structure == 'v') {
                    cout << "Testing Graph " << i << " with vector:" << endl;

                    writeLineToFile(filename, "\nTesting Graph " + to_string(i) + "with vector:");

                }

                WeightedGraph g("./graphs/grafo_W_" + to_string(i) + ".txt");
                test(g, case_number, queue_structure, i);

                cout << endl;
            }
        } else if (case_number == 3) {
            auto graph = LabeledWeightedGraph("./graphs/rede_colaboracao.txt", "./graphs/rede_colaboracao_vertices.txt");

            cout << "Distance Dijkstra -> Turing: " << graph.labeled_dijkstra_heap("Edsger W. Dijkstra", "Alan M. Turing") << endl;
            cout << "Distance Dijkstra -> Kruskal: " << graph.labeled_dijkstra_heap("Edsger W. Dijkstra", "J. B. Kruskal") << endl;
            cout << "Distance Dijkstra -> Kleinberg: " << graph.labeled_dijkstra_heap("Edsger W. Dijkstra", "Jon M. Kleinberg") << endl;
            cout << "Distance Dijkstra -> Tardos: " << graph.labeled_dijkstra_heap("Edsger W. Dijkstra", "Éva Tardos") << endl;
            cout << "Distance Dijkstra -> Ratton: " << graph.labeled_dijkstra_heap("Edsger W. Dijkstra", "Daniel R. Figueiredo") << endl;
        }

    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}
