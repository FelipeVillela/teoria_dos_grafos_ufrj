#include "Graph.h"
#include <fstream>
#include <iostream>

using namespace std;

struct MatrixAdjacencyGraph : Graph {
    vector<vector<int>> matrix;

    explicit MatrixAdjacencyGraph(const string& filename) {
        auto file = ifstream(filename);
        if (!file.is_open()) {
            cerr << "Could not open the file!\n";
            throw runtime_error("Could not open the file");
        }

        file >> node_count;
        matrix.resize(node_count + 1, vector<int>(node_count + 1, 0));

        int u, v;
        while (file >> u >> v) {
            add_edge(u, v);
        }

        file.close();
    }

    void add_edge(int u, int v) {
        matrix[u][v] = 1;
        matrix[v][u] = 1;
    }

    auto get_neighbors(int node) -> vector<int> override {
        auto neighbors = vector<int>();
        for (int i = 1; i <= node_count; ++i) {
            if (matrix[node][i] == 1) {
                neighbors.push_back(i);
            }
        }
        return neighbors;
    }
};