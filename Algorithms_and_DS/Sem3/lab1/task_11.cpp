#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
vector<vector<int>> trans;
vector<int> color;
vector<int> color2;
vector<int> components;
vector<int> res;
int comp;

void dfs(int number) {
    color[number] = 1;
    for (size_t i = 0; i < graph[number].size(); i++) {
        if (graph[number][i] == 0) {
            if (color[i] == 0) {
                dfs(i);
            }
        }
    }
    res.push_back(number);
}

void dfs_check(int number) {
    color[number] = 1;
    for (size_t i = 0; i < graph[number].size(); i++) {
        if (graph[number][i] != INT32_MAX && color[i] == 0) {
            dfs_check(i);
        }
    }
}

void dfs2(int number) {
    color2[number] = 1;
    for (size_t i = 0; i < trans[number].size(); i++) {
        if (trans[number][i] == 0 && color2[i] == 0) {
            dfs2(i);
        }
    }
    components[number] = comp;
}

int64_t china(int n, int root) {
    // Определяем минимум, вычитаем из всех входящих
    vector<int> minEdges(n, INT32_MAX);
    for (auto &i : graph) {
        for (size_t j = 0; j < i.size(); j++) {
            minEdges[j] = min(minEdges[j], i[j]);
        }
    }
    int64_t answer = 0;
    for (size_t i = 0; i < graph.size(); i++) {
        for (size_t j = 0; j < graph[i].size(); j++) {
            if (graph[i][j] != INT32_MAX) {
                graph[i][j] -= minEdges[j];
            }
        }
        if (i != (unsigned) root) {
            answer += minEdges[i];
        }
    }
    // Проверяем можно ли добраться по 0
    color.clear();
    color.resize(n, 0);
    dfs(root);
    bool check = true;
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            check = false;
            break;
        }
    }
    if (check) {
        return answer;
    }
    // Если нельзя по 0, то конденсация графа
    res.clear();
    components.clear();
    components.resize(n, -1);
    comp = 0;
    color.clear();
    color.resize(n, 0);
    color2.clear();
    color2.resize(n, 0);
    vector<int> temp(n);
    trans.resize(n, temp);
    for (size_t i = 0; i < graph.size(); i++) {
        for (size_t j = 0; j < graph[i].size(); j++) {
            trans[i][j] = graph[j][i];
        }
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
    // В components лежит компонента для каждой вершины
    // Теперь пересоздадим граф
    temp.clear();
    temp.resize(comp, INT32_MAX);
    vector<vector<int>> new_graph(comp, temp);
    for (size_t i = 0; i < graph.size(); i++) {
        for (size_t j = 0; j < graph[i].size(); j++) {
            if (graph[i][j] != INT32_MAX) {
                int i1 = components[i], j1 = components[j];
                if (i1 != j1) {
                    new_graph[i1][j1] = min(graph[i][j], new_graph[i1][j1]);
                }
            }
        }
    }
    graph.clear();
    graph = new_graph;
    new_graph.clear();
    answer += china(comp, components[root]);
    return answer;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> temp(n, INT32_MAX);
    graph.resize(n, temp);
    color.resize(n, 0);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a != b && b != 1) {
            graph[a - 1][b - 1] = min(c, graph[a - 1][b - 1]);
        }
    }
    dfs_check(0);
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES\n";
    cout << china(n, 0);
    return 0;
}
