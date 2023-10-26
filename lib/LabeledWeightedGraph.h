#include "WeightedGraph.h"
#include <unordered_map>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

struct LabeledWeightedGraph {
    WeightedGraph graph;
    map<string, int> label_to_id;

    int node_count;

    explicit LabeledWeightedGraph(const string& graph_filename, const string& labels_filename): graph(graph_filename) {
        // Read labels
        auto labels_file = ifstream(labels_filename);
        if (!labels_file.is_open()) {
            cerr << "Could not open the labels file!\n";
            throw runtime_error("Could not open the labels file");
        }

        int u;

        while (labels_file >> u) {
            string label;
            labels_file >> label;
            label_to_id[label] = u;
        }

        labels_file.close();
    }

    float labeled_dijkstra_vector(string start, string end) {
        return graph.dijkstra_vector(label_to_id[start], label_to_id[end]);
    }

    float labeled_dijkstra_heap(string start, string end) {
        return graph.dijkstra_heap(label_to_id[start], label_to_id[end]);
    }
};