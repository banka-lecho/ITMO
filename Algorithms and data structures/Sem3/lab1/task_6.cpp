#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<int> color;
vector<int> color2;
vector<vector<int>> graph;
vector<vector<int>> trans;
vector<int> res;
int comp = 1;
vector<int> answer;
set<pair<int,int> > s;

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

void dfs2(int number) {
    color2[number] = 1;
    for (int i : trans[number]) {
        if (color2[i] == 0) {
            dfs2(i);
        }
    }
    color2[number] = 2;
    answer[number] = comp;
}

int main() {
    int m, n;
    cin >> n >> m;
    graph.resize(n);
    trans.resize(n);
    color.resize(n, 0);
    color2.resize(n, 0);
    answer.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x - 1].push_back(y - 1);
        trans[y - 1].push_back(x - 1);
    }
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            dfs(i);
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        if (color2[res[i]] == 0) {
            dfs2(res[i]);
            comp++;
        }
    }
    for(int i = 1; i < graph.size(); i++)
        for(int j = 0; j < graph[i].size(); j++) {
            int to = graph[i][j];
            if (color[i] != color[to])
                s.insert(make_pair(color[i],color[to]));
        }
    cout << s.size();
    return 0;
}