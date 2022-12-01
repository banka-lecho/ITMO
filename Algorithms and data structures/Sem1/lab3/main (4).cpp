#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

vector<int> a;

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
    int n;
    cin >> n;
    a.resize(n + 1);
    for (int i = 0; i < n + 1; i++) {
        a[i] = i;
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        int y = find(x);
        cout << y << " ";
        if (y == n) {
            update(x, 1);
        } else {
            update(x, find(x) + 1);
        }
    }
    return 0;
}
