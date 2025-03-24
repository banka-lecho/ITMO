#include <iostream>
#include <vector>

const long long INF = 1e15;

using namespace std;

struct Edges {
    long long len = 0, to = 0;
};

vector<vector<Edges>> graph;

vector<long long> Bellman_Ford(long long n, long long first) {
    vector<long long> d(n, INF);
    d[first] = 0;

    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < n; j++)
            for (long long k = 0; k < graph[j].size(); k++) {
                long long to = graph[j][k].to;
                long long dist = graph[j][k].len;
                if ((d[j] < INF) && (d[to] > d[j] + dist))
                    d[to] = d[j] + dist;
            }
    }
    return  d;
}

void dfs(long long v, vector<int>& vis) {
    vis[v] = 1;
    for (auto & i : graph[v]) {
        if (!vis[i.to])
            dfs(i.to, vis);
    }
}

int main() {
    long long n, m, first, x, y, len;
    in >> n >> m >> first;
    first--;
    graph.resize(n);
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> len;
        graph[--x].push_back({len, --y});
    }
    vector<long long> d = Bellman_Ford(n, first);
    vector<int> vis(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            long long to = graph[i][j].to;
            long long dist = graph[i][j].len;
            if ((d[i] < INF) && (d[to] > d[i] + dist) && !vis[to])
                dfs(to, vis);
        }
    }

    for (int i = 0; i < n; i++)
        if (d[i] == INF)
            cout << "*\n";
        else if (vis[i] || d[i] < -5e18)
            cout << "-\n";
        else
            out << d[i] << "\n";
    return 0;
}