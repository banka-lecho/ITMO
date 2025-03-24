#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    size_t n, m;
    cin >> n >> m;
    vector<vector<pair<size_t, int>>> graph(n);
    for (size_t i = 0; i < m; i++) {
        int first, second, weight;
        cin >> first >> second >> weight;
        first--;
        second--;
        graph[first].push_back({second, weight});
        graph[second].push_back({first, weight});
    }
    vector<bool> visit(n, false);
    vector<int> dist(n, INT32_MAX);
    dist[0] = 0;
    int answer = 0;
    set<pair<int, size_t>> q;
    for (size_t i = 0; i < n; i++) {
        q.insert({dist[i], i});
    }
    while (!q.empty()) {
        pair<int, size_t> node = *q.begin();
        q.erase(q.begin());
        visit[node.second] = true;
        answer += node.first;
        for (auto &i : graph[node.second]) {
            size_t to = i.first;
            int weight = i.second;
            if (!visit[to] && dist[to] > weight) {
                q.erase({dist[to], to});
                dist[to] = weight;
                q.insert({dist[to], to});
            }
        }
    }
    cout << answer;
    return 0;
}