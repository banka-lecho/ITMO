#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

vector<int> a;
vector<pair<string, pair<int, int> > > b;
vector<string> answer;

int find(int x) {
    while (a[x] != x) {
        return a[x] = find(a[x]);
    }
    return a[x];
}

void update(int x, int y) {
    int a1 = find(x);
    int b = find(y);
    if (b != a1) {
        a[a1] = b;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    a.resize(n + 1);
    b.resize(k);
    answer.resize(k);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
    }
    for (int i = 0; i < n + 1; i++) {
        a[i] = i;
    }
    for (int i = k - 1; i >= 0; i--) {
        string s;
        cin >> s;
        int x, y;
        cin >> x >> y;
        b[i] = make_pair(s, make_pair(x, y));
    }
    for (int i = 0; i < k; i++) {
        if (b[i].first == "ask") {
            if (find(a[b[i].second.first]) == find(a[b[i].second.second])) {
                answer[i] = "YES";
            } else {
                answer[i] = "NO";
            }
        } else {
            answer[i] = "-";
            update(b[i].second.second, b[i].second.first);
        }
    }
    for (int i = k - 1; i >= 0; i--) {
        if (answer[i] != "-") {
            cout << answer[i] << "\n";
        }
    }
    return 0;
}
