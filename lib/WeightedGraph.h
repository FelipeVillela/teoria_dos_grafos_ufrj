#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H

#include "Graph.h"
#include <unordered_map>
#include <fstream>
#include <iostream>

using namespace std;

struct WeightedGraph : Graph {
    vector<unordered_map<int, float>> adj_list;
    int node_count;

    explicit WeightedGraph(const string& filename) {
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
            add_edge(v, u, w); // Comment this line if the graph is directed
        }

        file.close();
    }

    void add_edge(int u, int v, float w) {
        adj_list[u][v] = w;
    }

    vector<int> get_neighbors(int node) {
        vector<int> neighbors;
        for (const auto& [v, w] : adj_list[node]) {
            neighbors.push_back(v);
        }
        return neighbors;
    }

    vector<int> reconstruct_path(int start, int target, const vector<int>& predecessor) {
        if (predecessor[target] == -1 && target != start) {
            return {};  // Return an empty path or handle as needed
        }

        vector<int> path;
        for (int at = target; at != start; at = predecessor[at]) {
            if (at == -1) {
                return {};  // Return an empty path or handle as needed
            }
            path.push_back(at);
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
        return path;
    }

    vector<pair<float, vector<int>>> dijkstra_vector(int start) {
        vector<float> distances(node_count + 1, numeric_limits<float>::infinity());
        vector<int> predecessor(node_count + 1, -1);
        vector<bool> visited(node_count + 1, false);
        distances[start] = 0;

        for (int i = 1; i <= node_count; ++i) {
            int min_distance_node = -1;
            for (int j = 1; j <= node_count; ++j) {
                if (!visited[j] && (min_distance_node == -1 || distances[j] < distances[min_distance_node])) {
                    min_distance_node = j;
                }
            }

            if (distances[min_distance_node] == numeric_limits<float>::infinity()) break;

            visited[min_distance_node] = true;
            for (const auto& [neighbor, weight] : adj_list[min_distance_node]) {
                float new_distance = distances[min_distance_node] + weight;
                if (new_distance < distances[neighbor]) {
                    distances[neighbor] = new_distance;
                    predecessor[neighbor] = min_distance_node;
                }
            }
        }

        vector<pair<float, vector<int>>> result(node_count + 1);
        for (int i = 1; i <= node_count; ++i) {
            result[i] = {distances[i], reconstruct_path(start, i, predecessor)};
        }

        return result;
    }

    vector<pair<float, vector<int>>> dijkstra_heap(int start) {
        vector<float> distances(node_count + 1, numeric_limits<float>::infinity());
        vector<int> predecessor(node_count + 1, -1);
        priority_queue<pair<float, int>, vector<pair<float, int>>, greater<>> pq;
        distances[start] = 0;
        pq.emplace(0, start);

        while (!pq.empty()) {
            auto [current_distance, node] = pq.top();
            pq.pop();

            if (current_distance > distances[node]) continue;

            for (const auto& [neighbor, weight] : adj_list[node]) {
                float new_distance = distances[node] + weight;
                if (new_distance < distances[neighbor]) {
                    distances[neighbor] = new_distance;
                    predecessor[neighbor] = node;
                    pq.emplace(new_distance, neighbor);
                }
            }
        }

        vector<pair<float, vector<int>>> result(node_count + 1);
        for (int i = 1; i <= node_count; ++i) {
            result[i] = {distances[i], reconstruct_path(start, i, predecessor)};
        }

        return result;
    }

    pair<float, vector<int>> dijkstra_vector(int start, int end) {
        return dijkstra_vector(start)[end];
    }

    pair<float, vector<int>> dijkstra_heap(int start, int end) {
        return dijkstra_heap(start)[end];
    }
};


#endif