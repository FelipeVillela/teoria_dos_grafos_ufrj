#include "Graph.h"
#include <unordered_map>
#include <fstream>
#include <iostream>

using namespace std;

struct WeightedGraph : Graph {
    vector<unordered_map<int, float>> adj_list;
    int node_count;

    explicit WeightedGraph(const string& filename) {
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

    float dijkstra_vector(int start, int end) {
        vector<float> dist(node_count + 1, numeric_limits<float>::max());
        vector<int> prev(node_count + 1, -1);
        vector<int> visited(node_count + 1, 0);
        dist[start] = 0;

        while (true) {
            int u = -1;
            float min_dist = numeric_limits<float>::max();

            for (int i = 1; i <= node_count; ++i) {
                if (!visited[i] && dist[i] < min_dist) {
                    min_dist = dist[i];
                    u = i;
                }
            }

            if (u == -1) {
                break;
            }

            visited[u] = 1;

            for (const auto& [v, w] : adj_list[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    prev[v] = u;
                }
            }
        }

        return dist[end];
    }

    float dijkstra_heap(int start, int end) {
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

        return dist[end];
    }
};