#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, pair<int, int> > > q;
vector<int> answer;
vector<int> snm;  // следующий элемент, который ещё не заполнен

int find(int x) {
    while (snm[x] != x) {
        return snm[x] = find(snm[x]);
    }
    return snm[x];
}

void update(int x, int y) {
    int a1 = find(x);
    int b = find(y);
    if (b != a1) {
        snm[a1] = b;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    q.resize(m);
    answer.resize(n, -1);
    snm.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        q[i] = make_pair(z, make_pair(x - 1, y - 1));
    }
    sort(q.begin(), q.end());
    for (int i = 0; i < n + 1; i++) {
        snm[i] = i;
    }
    for (int i = m - 1; i >= 0; i--) {
        for (int j = q[i].second.first; j < q[i].second.second + 1; j++) {
            if (snm[j] == j) {
                answer[j] = q[i].first;
            }
            int w = find(j + 1);
            update(j, w);
            j = w;
            j--;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << answer[i] << " ";
    }
    return 0;
}
