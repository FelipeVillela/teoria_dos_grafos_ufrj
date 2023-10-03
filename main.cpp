#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <queue>
#include <stack>
#include <ranges>
#include <numeric>
#include <thread>

using namespace std;

struct Graph {
    virtual void add_edge(int u, int v) = 0;
    virtual auto get_neighbors(int node) -> vector<int> = 0;

    int node_count;

    vector<int> get_nodes() {
        auto nodes = vector<int>(node_count);
        iota(nodes.begin(), nodes.end(), 1);
        return nodes;
    }

    vector<int> bfs(int start_node, int end_node) {
        auto visited = vector<int>(node_count + 1, 0);
        auto path = vector<int>();
        auto q = queue<int>();

        q.push(start_node);

        while (!q.empty()) {
            auto node = q.front();
            q.pop();

            if (node == end_node) {
                path.push_back(node);
                break;
            }

            if (!visited[node]) {
                visited[node] = 1;
                path.push_back(node);

                for (auto neighbor : get_neighbors(node)) {
                    if (!visited[neighbor]) {
                        q.push(neighbor);
                    }
                }
            }
        }

        return path;
    }

    vector<int> dfs(int start_node, int end_node) {
        auto visited = vector<int>(node_count + 1, 0);
        auto path = vector<int>();
        auto s = stack<int>();

        s.push(start_node);

        while (!s.empty()) {
            auto node = s.top();
            s.pop();

            if (node == end_node) {
                path.push_back(node);
                break;
            }

            if (!visited[node]) {
                visited[node] = 1;
                path.push_back(node);

                for (auto neighbor : get_neighbors(node)) {
                    if (!visited[neighbor]) {
                        s.push(neighbor);
                    }
                }
            }
        }

        reverse(path.begin(), path.end());
        return path;
    }

    vector<tuple<int, int, int>> distances(int start_node) {
        const int INF = 1e9;
        auto distance = vector<int>(node_count + 1, INF);
        auto predecessor = vector<int>(node_count + 1, -1);
        auto q = queue<int>();

        distance[start_node] = 0;
        q.push(start_node);

        while (!q.empty()) {
            auto node = q.front();
            q.pop();

            for (auto neighbor : get_neighbors(node)) {
                if (distance[neighbor] == INF) {
                    distance[neighbor] = distance[node] + 1;
                    predecessor[neighbor] = node;
                    q.push(neighbor);
                }
            }
        }

        auto result = vector<tuple<int, int, int>>();
        for (int i = 1; i <= node_count; ++i) {
            result.emplace_back(i, predecessor[i], distance[i]);
        }

        return result;
    }

    int _diameter(int start, int end) {
        const int INF = 1e9;
        int local_dist = INF;

        for (int i = start; i < end; ++i) {
            auto dists = distances(i);
            int max_distance = 0;

            for (auto [s, distance, t] : dists) {
                if (distance != INF) {
                    max_distance = max(max_distance, distance);
                }
            }

            local_dist = min(local_dist, max_distance);
        }

        return local_dist;
    }

    int diameter() {
        const auto num_threads = thread::hardware_concurrency();
        auto dists = vector<int>(num_threads);

        auto threads = vector<thread>();
        auto nodes_per_thread = node_count / num_threads;

        for (int i = 0; i < num_threads; ++i) {
            auto start = i * nodes_per_thread + 1;
            auto end = (i == num_threads - 1) ? node_count + 1 : start + nodes_per_thread;
            threads.emplace_back([&](int tid, int start, int end) {
                dists[tid] = _diameter(start, end);
            }, i, start, end);
        }

        for (auto& th : threads) {
            th.join();
        }

        return *max_element(dists.begin(), dists.end());
    }

    vector<vector<int>> connected_components() {
        auto visited = vector<int>(node_count + 1, 0);
        auto components = vector<vector<int>>();

        for (int i = 1; i <= node_count; ++i) {
            if (!visited[i]) {
                auto component = vector<int>();
                auto q = queue<int>();

                visited[i] = 1;
                q.push(i);

                while (!q.empty()) {
                    auto node = q.front();
                    q.pop();

                    component.push_back(node);

                    for (auto neighbor : get_neighbors(node)) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = 1;
                            q.push(neighbor);
                        }
                    }
                }

                components.push_back(component);
            }
        }

        return components;
    }
};

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

    void add_edge(int u, int v) override {
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    auto get_neighbors(int node) -> vector<int> override {
        return adj_list[node];
    }
};

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

    void add_edge(int u, int v) override {
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


void test(Graph& graph) {


//    {
//        auto start = chrono::high_resolution_clock::now();
//        for (int i = 1; i <= 10; ++i) {
//            graph.bfs(i % graph.node_count + 1);
//        }
//        auto stop = chrono::high_resolution_clock::now();
//
//        auto duration = duration_cast<chrono::microseconds>(stop - start);
//        cout << "Time taken by BFS: " << duration.count() / (1000.0 * 10) << " milliseconds" << endl;
//    }


//    {
//        auto start = chrono::high_resolution_clock::now();
//        for (int i = 1; i <= 10; ++i) {
//            graph.dfs(i % graph.node_count + 1, (i + 1) % graph.node_count + 1);
//        }
//        auto stop = chrono::high_resolution_clock::now();
//
//        auto duration = duration_cast<chrono::microseconds>(stop - start);
//        cout << "Time taken by DFS: " << duration.count() / (1000.0 * 10) << " milliseconds" << endl;
//    }


    {
        cout << "BFS parent of vertex 10: " << graph.bfs(1, 10)[1] << endl;
        cout << "BFS parent of vertex 20: " << graph.bfs(2, 20)[1] << endl;
        cout << "BFS parent of vertex 30: " << graph.bfs(3, 30)[1] << endl;

        cout << "DFS parent of vertex 10: " << graph.dfs(1, 10)[1] << endl;
        cout << "DFS parent of vertex 20: " << graph.dfs(2, 20)[1] << endl;
        cout << "DFS parent of vertex 30: " << graph.dfs(3, 30)[1] << endl;
    }


    {
//        cout << "Distance between vertices 10 and 20: " << graph.dfs(10, 20).size() << endl;
//        cout << "Distance between vertices 10 and 30: " << graph.dfs(10, 30).size() << endl;
//        cout << "Distance between vertices 20 and 30: " << graph.dfs(20, 30).size() << endl;
    }


    {
//        auto components = graph.connected_components();
//        cout << "Number of connected components: " << components.size() << endl;
//
//        int max_size = 0, min_size = graph.node_count;
//        for (const auto &component: components) {
//            max_size = max(max_size, static_cast<int>(component.size()));
//            min_size = min(min_size, static_cast<int>(component.size()));
//        }
//
//        cout << "Size of the largest connected component: " << max_size << endl;
//        cout << "Size of the smallest connected component: " << min_size << endl;
    }


//    {
//        int diameter = graph.diameter();
//        cout << "Diameter of the graph: " << diameter << endl;
//    }
}


int main() {
    try {
        for (int i = 1; i <= 6; ++i) {
            cout << "Testing Adjacency List Graph " << i << ":" << endl;

            AdjacencyListGraph adj_list_graph("../grafo_" + to_string(i) + ".txt");
            test(adj_list_graph);

            cout << endl;
        }

    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}
