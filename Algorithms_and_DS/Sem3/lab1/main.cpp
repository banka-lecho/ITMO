#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> tin, up, visited;
vector<int> answer;
int n, m, times;

void dfs(int v, int parent = -1) {
    visited[v] = 1;
    up[v] = tin[v] = times++;
    int children = 0;
    for (int u = 0; u < graph[v].size(); ++u){
        int to = graph[v][u];
        if(to == parent) continue;
        if(visited[to]) {
            up[v] = min(up[v], tin[to]);
        }else {
            dfs(to, v);
            up[v] = min(up[v], tin[to]);
            if((parent != -1) && (up[to] >= tin[v])){
                if(find(begin(answer), end(answer), v) == end(answer)){
                    answer.push_back(v);
                }
            }
            children++;
        }
    }
    if((parent == -1) && (children > 1)){
        answer.push_back(v);
    }
}
int main() {
    cin >> n >> m;
    graph.resize(n+1);
    up.resize(n+1);
    visited.resize(n+1);
    tin.resize(n+1);
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    times = 1;
    for (int i = 1; i <= n; ++i) {
        if(!visited[i])
            dfs(i);
    }
    cout << answer.size() << endl;
    reverse(answer.begin(), answer.end());
    for (int i : answer) {
        cout << i << " ";
    }
    return 0;
}