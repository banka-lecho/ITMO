#include <iostream>
#include <vector>

using namespace std;

vector<int> color;
vector<int> color2;
vector<vector<int>> graph;
vector<vector<int>> trans;
vector<int> res;
int comp = 1;

void dfs(size_t number, int k) {
    color[number] = 1;
    for (size_t i = 0; i < graph[number].size(); i++) {
        if (graph[number][i] <= k && i != (unsigned) number) {
            if (color[i] == 0) {
                dfs(i, k);
            }
        }
    }
    color[number] = 2;
    res.push_back((int) number);
}

void dfs2(size_t number, int k) {
    color2[number] = 1;
    for (size_t i = 0; i < trans[number].size(); i++) {
        if (trans[number][i] <= k && i != (unsigned) number) {
            if (color2[i] == 0) {
                dfs2(i, k);
            }
        }
    }
    color2[number] = 2;
}

bool check(int k, int n) {
    comp = 1;
    res.clear();
    color.clear();
    color2.clear();
    color.resize(n, 0);
    color2.resize(n, 0);
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            dfs(i, k);
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        if (color2[res[i]] == 0) {
            dfs2(res[i], k);
            comp++;
        }
    }
    return comp == 2;
}

int main() {
    int n;
    cin >> n;
    graph.resize(n);
    vector<int> a(n);
    trans.resize(n, a);
    int m = 0;
    for (int i = 0; i < n; i++) {
        graph[i].resize(n);
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
            trans[j][i] = graph[i][j];
            m = max(m, graph[i][j]);
        }
    }
    int left = 0, right = m, middle = (left + right) / 2;
    while (left != right) {
        if (check(middle, n)) {
            right = middle;
        } else {
            left = middle + 1;
        }
        middle = (right + left) / 2;
    }
    cout << left;
    return 0;
}