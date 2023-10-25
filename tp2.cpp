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

using namespace std;

struct Graph {
    vector<unordered_map<int, float>> adj_list;
    int node_count;

    explicit Graph(const string& filename) {
        auto file = ifstream(filename);

        if (!file.is_open()) {
            cerr << "Could not open the file!\n";
            throw runtime_error("Could not open the file");
        }

        file >> node_count;
        adj_list.resize(node_count + 1);

        int u, v;
        float w;

        while (file >> u >> v >> w) {
            add_edge(u, v, w);
        }

        file.close();
    }

    void add_edge(int u, int v, float w) {
        adj_list[u][v] = w;
    }

    vector<int> get_neighbors(int node) {
        auto neighbors = vector<int>();

        for (const auto& [v, w] : adj_list[node]) {
            neighbors.push_back(v);
        }

        return neighbors;
    }

    vector<int> get_nodes() {
        auto nodes = vector<int>(node_count);
        iota(nodes.begin(), nodes.end(), 1);
        return nodes;
    }

    vector<float> dijkstra_vector(int start) {
        vector<float> dist(node_count + 1, numeric_limits<float>::max());
        vector<bool> visited(node_count + 1, false);
        dist[start] = 0;

        for (int i = 1; i <= node_count; ++i) {
            int u = -1;
            for (int j = 1; j <= node_count; ++j) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }

            visited[u] = true;

            for (const auto& [v, w] : adj_list[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }

        return dist;
    }

    vector<float> dijkstra_heap(int start) {
        vector<float> dist(node_count + 1, numeric_limits<float>::max());
        priority_queue<pair<float, int>, vector<pair<float, int>>, greater<>> pq;
        dist[start] = 0;
        pq.emplace(0, start);

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) {
                continue;
            }

            for (const auto& [v, w] : adj_list[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }
        }

        return dist;
    }
};

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


void test(Graph& graph, int case_number, char queue_structure, int graph_number=0) {
    // Essa função é utilizada para executar o estudo de caso de acordo com o número recebido
    if (case_number == 1) {

        cout << to_string(graph.node_count) << endl;
            
        int startNode = 10;
        vector<float> dist;
        string structure_name;
        float float_dist;

        if (queue_structure == 'h') {
            structure_name = 'heap';
            dist = graph.dijkstra_heap(startNode);
        }
        if (queue_structure == 'v') {
            structure_name = 'vector';
            dist = graph.dijkstra_vector(startNode);
        }

       for (int endNode = 20; endNode <= 60; endNode += 10) {
            cout << "Distância de " << startNode << " até " << endNode << endl;

            float_dist = dist[endNode];

            cout << to_string(float_dist) << endl;

            writeLineToFile("dist_" + to_string(startNode) + "_" + to_string(endNode) + ".txt", "\nGraph " + to_string(graph_number) + ": " + to_string(float_dist) + "\n");
        }
                
            
    }

    if (case_number == 2) {
        // Medição do tempo de execução do dijkstra

        int total_iterations = 100;
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
            
            writeLineToFile("output_heap.txt", "Time taken by Dijkstra with heap starting in node " + to_string(randomNode) + ": " + to_string(duration_heap_ms) + " milliseconds");
            //End heap
        }

        writeLineToFile("output_vector.txt", "\nTotal exec time: " + to_string(total_vector_time) + " milliseconds");
        writeLineToFile("output_vector.txt", "\nMean exec time: " + to_string(total_vector_time / total_iterations) + " milliseconds");

        writeLineToFile("output_heap.txt", "\nTotal exec time: " + to_string(total_heap_time) + " milliseconds");
        writeLineToFile("output_heap.txt", "\nMean exec time: " + to_string(total_heap_time / total_iterations) + " milliseconds");

    }


};





int main(int argc, char *argv[]) {
    try {
        if (argc != 3) {
            printf("Usage: %s <number of test case> <v for vector, h for heap (only case 1)>\n", argv[0]);
            return 1;
        }

        int case_number = atoi(argv[1]); //número do caso de estudo
        char queue_structure = argv[2][0];    // Estrutura da fila grafo (v ou h)

        if (queue_structure != 'l' && queue_structure != 'h') {
            cerr << "Invalid data structure. Use 'v' for vector or 'h' for heap." << endl;
            return 1;
        }

        for (int i = 1; i <= 5; ++i) {

            cout << "Testing Graph " << i  << endl;

            Graph g("./graphs/grafo_W_" + to_string(i) + ".txt");
            test(g, case_number, queue_structure, i);     

            cout << endl;
        }

    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}
