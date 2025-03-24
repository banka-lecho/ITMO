#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

vector<pair<int, int> > a;  // вторым буду хранить чётность
int shift;


pair<int, int> find(int x) {  // работает
    if (a[x].first != x) {
        int len = a[x].second;
        a[x] = find(a[x].first);
        a[x].second = a[x].second ^ len;
    }
    return a[x];
}

void update(int x, int y) {  // тоже равботает
    pair<int, int> a1 = find(x);
    pair<int, int> b = find(y);
    if (b.first != a1.first) {
        a[a1.first] = make_pair(b.first, 1 ^ a1.second ^ b.second);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    shift = 0;
    a.resize(n);
    for (int i = 0; i < n; i++) {  // ok
        a[i] = make_pair(i, 0);
    }
    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> z >> x >> y;
        x = (x + shift) % n;
        y = (y + shift) % n;
        if (z == 0) {
            update(x, y);
        } else {
            find(x);
            find(y);
            if (a[x].second == a[y].second) {  // и какого лешего ва 15???
                cout << "YES\n";
                shift = (shift + 1) % n;
            } else {
                cout << "NO\n";
            }
        }
    }
    return 0;
}
