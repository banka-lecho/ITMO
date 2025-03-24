#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int n, m;
    queue<int> q; // наша очередь
    vector<int> d; // вектор проигрышных и непроигрышных вершин
    vector<vector<int>> graph;
    vector<vector<int>> expanded_graph;
    vector<int> cnt_in;

    // тут неправильно работает цикл while, мб нужно будет подчищать все массивы

//    while(cin >> n){
    cin >> n;
    cin >> m;
    d.resize(n, -1);
    graph.resize(n);
    expanded_graph.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x - 1].push_back(y - 1); // конкретно эта сука неправильно выводится
        expanded_graph[y - 1].push_back(x - 1);
    }
//     заносим в вектор out число исходящих ребер соответсвующих вершинам
    for (int v = 0; v < n; v++) {
        cnt_in.push_back(graph[v].size());
    }
    // ищем и заносим тупики в вектор d
    for (int v = 0; v < n; v++) {
        if (graph[v].size() == 0) {
            d[v] = 0;
            q.push(v);
        }
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (d[v] == 0) {
            for (int u: expanded_graph[v]) { // тут нужно итерироваться по входящим ребрам
                if (d[u] == -1) {
                    d[u] = 1;
                    q.push(u);
                }
            }
        } else {
            for (int u: expanded_graph[v]) {
                cnt_in[u]--;
                if (cnt_in[u] == 0) {
                    d[u] = 0;
                    q.push(u);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (d[i] == -1) {
            cout << "DRAW" << "\n";
        } else if (d[i] == 1) {
            cout << "FIRST" << "\n";
        } else if (d[i] == 0) {
            cout << "SECOND" << "\n";
        }
    }
    // тут нужно будет все очистить
//   }
    return 0;
}