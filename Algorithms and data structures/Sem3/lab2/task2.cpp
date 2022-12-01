#include <iostream>
#include <vector>
#include <set>

using namespace std;

int n, m;
vector<vector<pair<int, int>>> g;
vector<int> dist;
set<pair<int, int>> edges;

void deikstra() {
    dist[0] = 0;
    edges.emplace(dist[0], 0);
    while (!edges.empty()) {
        int from = edges.begin()->second;
        edges.erase(edges.begin());
        for (auto &edge : g[from]) {
            int to = edge.first;
            int weight = edge.second;
            if (dist[from] + weight < dist[to]) {
                edges.erase({dist[to], to});
                dist[to] = dist[from] + weight;
                edges.emplace(dist[to], to);
            }
        }
    }
}

int main() {
    cin >> n >> m;
    g.resize(n);
    dist.resize(n);
    for (int i = 0; i < n; i++) {
        dist[i] = 100000000;
    }
    for (int i = 0; i < m; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        g[from - 1].emplace_back(to - 1, weight);
        g[to - 1].emplace_back(from - 1, weight);
    }
    deikstra();
    for (int weight : dist) {
        cout << weight << " ";
    }
    return 0;
}