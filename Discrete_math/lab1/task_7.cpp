#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
int n, m;
vector<int> colors;
vector<int> visited;
vector<int> neighbors_color;
int max1;

void maximum() {
    for (int i = 0; i < n; i++) {
        if (max1 < graph[i].size()) {
            max1 = (int) graph[i].size();
        }
    }
    if (max1 % 2 == 0) {
        max1++;
    }
}

void dfs(int v) {
    visited[v] = true;
    neighbors_color.clear();
    neighbors_color.resize(max1, -1);
    for (int i : graph[v]) {
        if (colors[i] != -1) {
            neighbors_color[colors[i]] = 1;
        }
    }
    for (int i = 0; i < neighbors_color.size(); i++) {
        if (neighbors_color[i] != 1) {
            colors[v] = i;
            break;
        }
    }
    for (int j : graph[v]) {
        if (!visited[j]) {
            dfs(j);
        }
    }
}

int main() {
    cin >> n >> m;
    int x, y;
    graph.resize(n);
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        graph[x - 1].push_back(y - 1);
        graph[y - 1].push_back(x - 1);
    }
    visited.resize(n, false);
    colors.resize(n, -1);
    max1 = 0;
    maximum();
    dfs(0);
    cout << max1 << '\n';
    for (int color : colors) {
        cout << color + 1 << '\n';
    }
}

