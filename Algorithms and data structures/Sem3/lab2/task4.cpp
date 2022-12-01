#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int to;
    int weight;
};

const int INF = 1000000;

int main(){
    int n, m, k, s;
    vector<vector<Edge>> graph;
    vector<vector<long long>> d;
    int a, b, len;
    cin >> n >> m >> k >> s; s--;
    d.resize(k + 1, vector<long long>(n, INF));
    graph.resize(n);
    d[0][s] = 0;
    for(int i = 0; i < n;i++){
        cin >> a >> b >> len;
        graph[a - 1].push_back({b - 1, len});
    }
    // сам алгоритм форда беллмана
    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < n; j++)
            for (long long u = 0; u < graph[j].size(); u++) {
//                if (d[i][j] == INF) {
//                    continue;
//                }
                long long from = j;
                long long to = graph[j][u].to;
                long long dist = graph[j][u].weight;
                d[i + 1][to] = min(d[i + 1][to], d[i][from] + dist);
            }
    }
    // вывели ответ
    for (long long i = 0; i < n; ++i) {
        if (d[k][i] == INF) {
            cout << -1 << endl;
        } else {
            cout << d[k][i] << endl;
        }
    }

}