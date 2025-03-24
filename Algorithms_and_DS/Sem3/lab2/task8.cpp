#include <iostream>
#include <vector>

using namespace std;

vector<int> color;
vector<vector<int>> graph;
vector<int> res;
vector<int> dp;

void dfs(int number) {
    color[number] = 1;
    for (int i : graph[number]) {
        if (color[i] == 0) {
            dfs(i);
        }
    }
    color[number] = 2;
    res.push_back(number);
}

int main() {
    int m, n, start;
    cin >> n >> m >> start; start--;
    graph.resize(n);
    color.resize(n, 0);
    dp.resize(n, 0);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x - 1].push_back(y - 1);
    }
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            dfs(i);
        }
    }
    for (size_t index = 0; index < res.size(); index++) {
        for (size_t i = 0; i < graph[res[index]].size(); i++) {
            if (dp[graph[res[index]][i]] == 0) {
                dp[res[index]] = 1;
                break;
            }
        }
    }
    if (dp[start] == 1) {
        cout << "First player wins";
    } else {
        cout << "Second player wins";
    }
    return 0;
}