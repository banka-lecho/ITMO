#include <iostream>
#include <vector>

using namespace std;

vector<int> color;
vector<int> visit;
vector<vector<pair<int, int>>> graph;
vector<int> time_in;
int position = 0;
vector<int> f;
vector<bool> pos;
int answer = 0;

void dfs(int number, int parent = -1) {
    color[number] = 1;
    time_in[number] = position;
    position++;
    f[number] = time_in[number];
    int counts = 0;
    for (auto i : graph[number]) {
        if (i.first != parent) {
            if (color[i.first] == 0) {
                counts++;
                dfs(i.first, number);
                if (f[number] > f[i.first]) {
                    f[number] = f[i.first];
                }
                if (parent != -1 && f[i.first] >= time_in[number]) {
                    pos[number] = true;
                }
            } else {
                if (f[number] > time_in[i.first]) {
                    f[number] = time_in[i.first];
                }
            }
        }
    }
    if (parent == -1 && counts > 1) {
        pos[number] = true;
    }
    color[number] = 2;
}


void dfs_1(int number, int cur_color) {
    visit[number] = 1;
    for (size_t i = 0; i < graph[number].size(); i++) {
        int to = graph[number][i].first;
        int num = graph[number][i].second;
        if (visit[to] == 0) {
            if (f[to] >= time_in[number]) {
                answer++;
                color[num] = answer;
                dfs_1(to, answer);
            } else {
                color[num] = answer;
                dfs_1(to, cur_color);
            }
        } else {
            if (time_in[to] < time_in[number]) {
                color[num] = cur_color;
            }
        }
    }
    visit[number] = 2;
}

int main() {
    int m, n;
    cin >> n >> m;
    graph.resize(n);
    color.resize(n, 0);
    time_in.resize(n, -1);
    f.resize(n);
    pos.resize(n, false);
    int number = 0;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x - 1].push_back({y - 1, number});
        graph[y - 1].push_back({x - 1, number});
        number++;
    }
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            dfs(i);
        }
    }
    color.clear();
    visit.resize(n, 0);
    color.resize(m, 0);
    for (int i = 0; i < n; i++) {
        if (visit[i] == 0) {
            dfs_1(i, answer);
        }
    }
    cout << answer << endl;
    for (int i = 0; i < m; i++) {
        cout << color[i] << " ";
    }
    return 0;
}