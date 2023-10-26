#include <vector>
#include <ranges>
#include <numeric>
#include <thread>
#include <queue>
#include <stack>
#include <tuple>
#include <algorithm>

using namespace std;

struct Graph {
    virtual auto get_neighbors(int node) -> vector<int> = 0;
    int node_count;

    vector<int> get_nodes() {
        auto nodes = vector<int>(node_count);
        iota(nodes.begin(), nodes.end(), 1);
        return nodes;
    }

    vector<int> bfs(int start_node, int end_node = -1) {
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

    vector<int> dfs(int start_node, int end_node = -1) {
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
