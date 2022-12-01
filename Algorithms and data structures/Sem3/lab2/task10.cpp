#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
vector<vector<int>> graph;
vector<vector<int>> expanded_graph;
queue<int> q;
vector<int> d;
const int INF = 100000;

int mex(int g) {
    static bool visited[INF + 1];
    int c = graph[g].size() + 1;

    for (int i : graph[g]) {
        if (d[i] <= INF) {
            visited[d[i]] = true;
        }
    }

    int result = 0;
    for (int i = 0; i < c; ++i) {
        if (!visited[i]) {
            result = i;
            break;
        }
    }

    for (int i : graph[g]) {
        if (d[i] <= INF) {
            visited[d[i]] = false;
        }
    }
    return result;
}

int main() {
    cin >> n >> m;
    graph.resize(n);
    expanded_graph.resize(n);
    d.resize(n, -1);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x - 1].push_back(y - 1);
        expanded_graph[y - 1].push_back(x - 1);
    }
    // нашли тупики
    for (int v = 0; v < n; v++) {
        if (graph[v].size() == 0) {
            d[v] = 0;
            q.push(v);
        }
    }
    // далее перебираем все смежные с тупиком вершины
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (d[v] == 0) {
            for (int u : expanded_graph[v]) {
                if (d[u] == -1) {
                    if (graph[u].size() == 0) {
                        d[u] = 1;
                    } else {
                        d[u] = mex(u);
                    }
                }
            }
        }
    }
    // по выполнению предыдущего цикла у нас будет результат записан в векторе в
    // далее просто выводим этот вектор
    for (int i = 0; i < n; i++) {
        cout << d[i] << "\n";
    }

}
