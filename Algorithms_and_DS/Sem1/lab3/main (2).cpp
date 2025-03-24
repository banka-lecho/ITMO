#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

vector<int> a;
vector<int> count1;
vector<int> min1;
vector<int> max1;

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
        max1[b] = max(max1[b], max1[a1]);
        min1[b] = min(min1[b], min1[a1]);
        count1[b] += count1[a1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);
    int n;
    cin >> n;
    a.resize(n + 1);
    count1.resize(n + 1);
    min1.resize(n + 1);
    max1.resize(n + 1);
    for (int i = 0; i < n + 1; i++) {
        a[i] = i;
        count1[i] = 1;
        max1[i] = i;
        min1[i] = i;
    }
    string c;
    while (cin >> c) {
        if (c == "union") {
            int x, y;
            cin >> x >> y;
            update(x, y);
        } else {
            int x;
            cin >> x;
            int q = find(x);
            cout << min1[q] << " " << max1[q] << " " << count1[q] << "\n";
        }
    }
    return 0;
}
