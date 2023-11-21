#ifndef FLOWGRAPH_H
#define FLOWGRAPH_H

#include "Graph.h"
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>

using namespace std;

struct FlowGraph : Graph {
    vector<unordered_map<int, float>> adj_list;
    int node_count;

    explicit FlowGraph(const string& filename) {
        ifstream file(filename);
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
        vector<int> neighbors;
        for (const auto& [v, capacity] : adj_list[node]) {
            neighbors.push_back(v);
        }
        return neighbors;
    }

    float ford_fulkerson(int source, int sink) {
        vector<vector<float>> residual_capacity(node_count + 1, vector<float>(node_count + 1, 0));
        
        // Inicializa o grafo residual
        for (int u = 1; u <= node_count; ++u) {
            for (const auto& [v, w] : adj_list[u]) {
                residual_capacity[u][v] = w;
            }
        }

        float max_flow = 0;

        while (true) {
            vector<int> parent(node_count + 1, -1);
            queue<pair<int, float>> q;
            q.push({source, numeric_limits<float>::infinity()});

            // BFS para encontrar caminho aumentante
            while (!q.empty()) {
                auto [current, flow] = q.front();
                q.pop();

                for (const auto& [neighbor, capacity] : adj_list[current]) {
                    if (parent[neighbor] == -1 && residual_capacity[current][neighbor] > 0) {
                        float new_flow = min(flow, residual_capacity[current][neighbor]);
                        q.push({neighbor, new_flow});
                        parent[neighbor] = current;

                        if (neighbor == sink) {

                            max_flow += new_flow;
                            int v = sink;
                            while (v != source) {
                                int u = parent[v];
                                residual_capacity[u][v] -= new_flow;
                                residual_capacity[v][u] += new_flow;
                                v = u;
                            }
                            break;
                        }
                    }
                }
            }

            if (parent[sink] == -1) {
                break;
            }
        }

        return max_flow;
    }
};

#endif