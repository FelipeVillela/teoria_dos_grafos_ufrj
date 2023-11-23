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

    pair<float, unordered_map<int, unordered_map<int, float>>> ford_fulkerson(int source, int sink, const string& flow_allocation_filename = "") {
        unordered_map<int, unordered_map<int, float>> residual_capacity, flow_allocation;

        for (int u = 1; u <= node_count; ++u) {
            for (const auto& [v, w] : adj_list[u]) {
                residual_capacity[u][v] = w;
                flow_allocation[u][v] = 0;
            }
        }

        float max_flow = 0;

        while (true) {
            vector<int> parent(node_count + 1, -1);
            queue<pair<int, float>> q;
            q.push({source, numeric_limits<float>::infinity()});
            vector<bool> visited(node_count + 1, false);
            visited[source] = true;

            while (!q.empty()) {
                auto [current, flow] = q.front();
                q.pop();

                for (const auto& [neighbor, capacity] : adj_list[current]) {
                    if (!visited[neighbor] && residual_capacity[current][neighbor] > 0) {
                        visited[neighbor] = true;
                        float new_flow = min(flow, residual_capacity[current][neighbor]);
                        q.push({neighbor, new_flow});
                        parent[neighbor] = current;

                        if (neighbor == sink) {
                            max_flow += new_flow;
                            update_path(parent, source, sink, new_flow, residual_capacity, flow_allocation);
                            break;
                        }
                    }
                }
                if (visited[sink]) {
                    break;
                }
            }

            if (parent[sink] == -1) {
                break;
            }
        }

        if (!flow_allocation_filename.empty()) {
            write_flow_allocation(flow_allocation_filename, flow_allocation);
        }

        return {max_flow, flow_allocation};
    }

    void update_path(vector<int>& parent, int source, int sink, float flow, unordered_map<int, unordered_map<int, float>>& residual_capacity, unordered_map<int, unordered_map<int, float>>& flow_allocation) {
        int v = sink;
        while (v != source) {
            int u = parent[v];
            residual_capacity[u][v] -= flow;
            residual_capacity[v][u] += flow;
            flow_allocation[u][v] += flow;
            v = u;
        }
    }

    void write_flow_allocation(const string& filename, unordered_map<int, unordered_map<int, float>>& flow_allocation) {
        ofstream output_file(filename);
        if (!output_file.is_open()) {
            cerr << "Could not open the output file!\n";
            throw runtime_error("Output file opening failed");
        }

        output_file << "Edge\tFlow Allocation\n";
        for (int u = 1; u <= node_count; ++u) {
            for (const auto& [v, flow] : flow_allocation[u]) {
                if (flow > 0) {
                    output_file << "(" << u << " -> " << v << ")\t" << flow << "\n";
                }
            }
        }
        output_file.close();
    }

    float get_bottleneck(vector<int>& path, unordered_map<int, unordered_map<int, float>>& flow_allocation) {
        float bottleneck = numeric_limits<float>::infinity();
        for (int i = 0; i < path.size() - 1; ++i) {
            bottleneck = min(bottleneck, flow_allocation[path[i]][path[i + 1]]);
        }
        return bottleneck;
    }

};

#endif