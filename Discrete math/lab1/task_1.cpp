#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

vector<vector<bool>> graph;
int n;
deque<int> deque1;

void gamilton() {
    for (int i = 0; i < n; i++) {
        deque1.push_back(i);
    }
    for (int i = 0; i < n*(n - 1); i++) {
        if (!graph[deque1[0]][deque1[1]]) {
            int number = 2;
            while (!graph[deque1[0]][deque1[number]] || !graph[deque1[1]][deque1[number + 1]]) {
                number++;
            }
            reverse(deque1.begin() + 1, deque1.begin() + number + 1);
        }
        deque1.push_back(deque1.front());
        deque1.pop_front();
    }
}

int main() {
    cin >> n;
    vector<bool> temp(n, false);
    graph.resize(n, temp);
    for (int i = 1; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < s.size(); j++) {
            if (s[j] == '1') {
                graph[i][j] = true;
                graph[j][i] = true;
            }
        }
    }

    gamilton();
    for (int i : deque1) {
        cout << i + 1 << " ";
    }
}