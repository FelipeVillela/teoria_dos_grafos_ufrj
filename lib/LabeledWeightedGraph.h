#include "WeightedGraph.h"
#include <unordered_map>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

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

        string line;
        while (getline(labels_file, line)) {
            int u;
            string label;
            char comma;

            auto ss = stringstream(line);

            if (ss >> u && ss >> comma && getline(ss, label)) {
                label_to_id[label] = u;
            } else {
                cerr << "Failed to parse line: " << line << endl;
            }
        }

        labels_file.close();
    }

    float labeled_dijkstra_vector(string start, string end) {
        auto start_id = label_to_id[start];
        auto end_id = label_to_id[end];

        if (start_id == 0) {
            cerr << "(Vertex not found: " << start << ") ";
            return -1;
        }

        if (end_id == 0) {
            cerr << "(Vertex not found: " << end << ") ";
            return -1;
        }

        return graph.dijkstra_vector(start_id, end_id);
    }

    float labeled_dijkstra_heap(string start, string end) {
        auto start_id = label_to_id[start];
        auto end_id = label_to_id[end];

        if (start_id == 0) {
            cerr << "(Vertex not found: " << start << ") ";
            return -1;
        }

        if (end_id == 0) {
            cerr << "(Vertex not found: " << end << ") ";
            return -1;
        }

        return graph.dijkstra_heap(start_id, end_id);
    }

    float labeled_dijkstra_path(string start, string end) {
        auto start_id = label_to_id[start];
        auto end_id = label_to_id[end];

        if (start_id == 0) {
            cerr << "(Vertex not found: " << start << ") ";
            return -1;
        }

        if (end_id == 0) {
            cerr << "(Vertex not found: " << end << ") ";
            return -1;
        }

        return graph.dijkstra_heap(start_id, end_id);
    }
};