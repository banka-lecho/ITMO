#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    vector<vector<int>> graph;
    vector<int> d;
    vector<int> out;

    int n, m;
    cin >> n >> m;
    graph.resize(n);
    d.resize(n);
    out.resize(n);
    // вот тут считать m и ещё m рёбер
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x - 1].push_back(y - 1);
    }
    // далее нам нужно присвоить всем вершинам 1 или 0
    // для этого находим тупики
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (graph[i].empty()) {
            d[i] = 0;
            q.push(i);
        } else {
            // out[v] - это просто массив чисел, которые соответствуют выходящим ребрам каждой вершины
            out.push_back(graph[i].size());
        }
    }
    // далее нужно пометить всё, что помечается
    int v;
    while (!q.empty()) {
        v = q.front();
        if (d[v] == 0) {
            for (int i = 0; i < graph[v].size(); i++) {
                if (d[i] == 0) {
                    d[i] = 1;
                    q.push(i);
                }
            }
        } else {
            for (int i = 0; i < n; i++) {
                // перебираем все входящие вершины
                out[i]--;
                if (out[i] == 0) {
                    d[i] = 0;
                    q.push(i);
                }
            }
        }
    }
    // теперь нам нужно как-то сделать проверку на то, кто выиграл
    for (int i = 1; i <= n; i++) {
        if (d[i] == 1) {
            cout << "FIRST" << "\n";
        } else{
            cout << "SECOND" << "\n";
        }
    }
}