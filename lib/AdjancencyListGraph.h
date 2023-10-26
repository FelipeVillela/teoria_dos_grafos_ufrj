#include "Graph.h"
#include <fstream>
#include <iostream>

using namespace std;

struct AdjacencyListGraph : Graph {
    vector<vector<int>> adj_list;

    explicit AdjacencyListGraph(const string& filename) {
        auto file = ifstream(filename);
        if (!file.is_open()) {
            cerr << "Could not open the file!\n";
            throw runtime_error("Could not open the file");
        }

        file >> node_count;
        adj_list.resize(node_count + 1);

        int u, v;
        while (file >> u >> v) {
            add_edge(u, v);
        }

        file.close();
    }

    void add_edge(int u, int v) {
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    auto get_neighbors(int node) -> vector<int> override {
        return adj_list[node];
    }
};