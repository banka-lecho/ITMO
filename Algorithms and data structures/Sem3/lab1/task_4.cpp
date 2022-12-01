#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>


using namespace std;

struct edge {
    int to;
    int number;
    bool multiple;
};

vector<int> color;
vector<vector<edge>> graph;
vector<int> tin;
vector<int> f;
int pos = 0;
vector<bool> bridge;
vector<int> result;

void dfs(int number, int parent = -1) {
    color[number] = 1;
    tin[number] = pos;
    f[number] = pos;
    pos++;
    for (auto i : graph[number]) {
        int to = i.to;
        if (to != parent) {
            if (color[to] == 0) {
                dfs(to, number);
                if (f[number] > f[to]) {
                    f[number] = f[to];
                }
            } else {
                if (f[number] > tin[to]) {
                    f[number] = tin[to];
                }
            }
        }
    }
    color[number] = 2;
}

void dfs2(int number) {
    color[number] = 1;
    result[number] = pos;
    for (auto i : graph[number]) {
        int to = i.to;
        if (!bridge[i.number]) {
            if (color[to] == 0) {
                dfs2(to);
            }
        }
    }
    color[number] = 2;
}

int main() {
    int m, n;
    cin >> n >> m;
    graph.resize(n);
    set<pair<int, int>> edges;
    vector<bool> multiple(m, false);
    int x, y;
    int number = 0;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        x--;
        y--;
        bool mult = false;
        if (edges.find({min(x, y), max(x, y)}) != edges.end()) {
            mult = true;
        } else {
            edges.insert({min(x, y), max(x, y)});
        }
        graph[x].push_back({y, number, mult});
        graph[y].push_back({x, number, mult});
        number++;
    }
    edges.clear();
    color.resize(n, 0);
    f.resize(n, 0);
    tin.resize(n, 0);
    bridge.resize(m, false);
    result.resize(n, -1);
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            dfs(i);
        }
    }
    for (int i = 0; i < n; i++) {
        for (size_t j = 0; j < graph[i].size(); j++) {
            if (tin[i] < f[graph[i][j].to] && !graph[i][j].multiple) {
                bridge[graph[i][j].number] = true;
            }
        }
    }
    color.clear();
    color.resize(n, 0);
    pos = 1;
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            dfs2(i);
            pos++;
        }
    }
    cout << pos - 1 << "\n";
    for (int i : result) {
        cout << i << " ";
    }
    return 0;
}