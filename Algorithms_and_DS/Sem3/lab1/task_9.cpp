#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

double countLen(pair<int, int> node1, pair<int, int> node2) {
    int first = node1.first - node2.first;
    int second = node1.second - node2.second;
    return sqrt(first * first + second * second);
}

int main() {
    size_t n;
    cin >> n;
    vector<pair<int, int>> nodes(n);
    int a, b;
    for (size_t i = 0; i < n; i++) {
        cin >> a >> b;
        nodes[i] = {a, b};
    }
    cout << setprecision(9);
    nodes.clear();
    vector<bool> visit(n, false);
    vector<double> dist(n, INT32_MAX);
    dist[0] = 0;
    double answer = 0;
    for (size_t i = 0; i < n; i++) {
        int node = -1;
        for (size_t j = 0; j < n; j++) {
            if (!visit[j] && (node == -1 || dist[node] > dist[j])) {
                node = (int) j;
            }
        }
        visit[node] = true;
        answer += dist[node];
        for (size_t j = 0; j < n; j++) {
            double len = countLen(nodes[node], nodes[j]);
            if (!visit[j] && len < dist[j]) {
                dist[j] = len;
            }
        }
    }
    cout << answer;
    return 0;
}