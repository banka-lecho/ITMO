#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

vector<int> a;
vector<int> b;

int finda(int x) {
    while (a[x] != x) {
        return a[x] = finda(a[x]);
    }
    return a[x];
}

int findb(int x) {
    while (b[x] != x) {
        return b[x] = findb(b[x]);
    }
    return b[x];
}

void updateb(int x, int y) {
    int a1 = findb(x);
    int b1 = findb(y);
    if (b1 != a1) {
        b[a1] = b1;
    }
}

void updatea(int x, int y) {
    int a1 = finda(x);
    int b1 = finda(y);
    if (b1 != a1) {
        a[a1] = b1;
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    a.resize(n + 1);
    b.resize(n + 1);
    for (int i = 0; i < n + 1; i++) {
        a[i] = i;
        b[i] = i;
    }
    for (int i = 0; i < q; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        if (x == 1) {
            updatea(y, z);
        } else if (x == 2) {
            while (y < z) {
                y = findb(y);
                if (y >= z) {
                    break;
                }
                updatea(y, y + 1);
                updateb(y, y + 1);
            }
        } else {
            if (finda(y) == finda(z)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
    return 0;
}
