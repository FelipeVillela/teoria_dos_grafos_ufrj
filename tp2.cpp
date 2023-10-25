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


void test(Graph& graph, int case_number) {
    // Essa função é utilizada para executar o estudo de caso de acordo com o número recebido


    if (case_number == 2) {
        // Medição do tempo de execução da BFS

        for (int i = 1; i <= 100; ++i) {
            // cout << to_string(graph.node_count) << endl;
            int randomNode = (std::rand() % graph.node_count) + 1;

            auto start = chrono::high_resolution_clock::now();
            
            graph.dijkstra_vector(randomNode);
            
            auto stop = chrono::high_resolution_clock::now();

            auto duration = duration_cast<chrono::microseconds>(stop - start);
            cout << "Time taken by Dijkstra sem heap no node " + to_string(randomNode) + ": " << duration.count() / (1000.0 * 10) << " milliseconds" << endl;
            
            writeLineToFile("semHeap.txt", "Time taken by Dijkstra sem heap no node " + to_string(randomNode) + ": " + to_string(duration.count() / (1000.0 * 10)) + " milliseconds");
        
            auto start2 = chrono::high_resolution_clock::now();
            
            graph.dijkstra_heap(randomNode);
            
            auto stop2 = chrono::high_resolution_clock::now();

            auto duration2 = duration_cast<chrono::microseconds>(stop2 - start2);
            cout << "Time taken by Dijkstra com heap no node " + to_string(randomNode) + ": " << duration2.count() / (1000.0 * 10) << " milliseconds" << endl;
            
            writeLineToFile("comHeap.txt", "Time taken by Dijkstra com heap no node " + to_string(randomNode) + ": " + to_string(duration2.count() / (1000.0 * 10)) + " milliseconds");
        }
    }


};





int main(int argc, char *argv[]) {
    // auto g = Graph("./graphs/grafo_W_1.txt");
    // return 0;

    try {

        for (int i = 4; i <= 5; ++i) {
            cout << "Testing Graph " << i << ":" << endl;

            writeLineToFile("comHeap.txt", "\nTesting Graph " + to_string(i) + ":");
            writeLineToFile("semHeap.txt", "\nTesting Graph " + to_string(i) + ":");

            Graph g("./graphs/grafo_W_" + to_string(i) + ".txt");
            test(g, 2);

            cout << endl;
        }

    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}
