#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > table;
vector<int> a;
vector<int> k;  // здесь храним k
vector<int> pow2;  // здесь храним 2^k

void build_table() {
    size_t j1 = 1;
    size_t number = 2;
    while (number < a.size()) {
        number *= 2;
        j1++;
    }
    vector<int> b(j1);
    table.resize(a.size(), b);
    for (size_t i = 0; i < a.size(); i++) {
        table[i][0] = a[i];
    }
    size_t q = 1;
    for (size_t j = 1; j < j1; j++) {
        for (size_t i = 0; i < a.size(); i++) {
            if (i + q < a.size() - 1) {
                table[i][j] = min(table[i][j - 1], table[i + q][j - 1]);
            } else {
                table[i][j] = min(table[i][j - 1], table[a.size() - 1][j - 1]);
            }
        }
        q *= 2;
    }
}

int find_min(int left, int right) {
    int len = right - left + 1;
    return min(table[left - 1][k[len]], table[right - pow2[len]][k[len]]);
}


int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, m, a1;
    cin >> n >> m >> a1;
    a.resize(n);
    a[0] = a1;
    for (int i = 1; i < n; i++) {
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
    }
    build_table();  // вроде верно
    int u1, v1;
    pow2.resize(n + 1);
    k.resize(n + 1);
    pow2[0] = 0;
    k[0] = -1;
    pow2[1] = 1;
    k[1] = 0;
    for (int i = 2; i < n + 1; i++) {
        if (i >= 2 * pow2[i - 1]) {
            pow2[i] = pow2[i - 1] * 2;
            k[i] = k[i - 1] + 1;
        } else {
            k[i] = k[i - 1];
            pow2[i] = pow2[i - 1];
        }
    }
    cin >> u1 >> v1;
    int ans = 0;
    for (int i = 1; i < m + 1; i++) {
        ans = find_min(min(u1, v1), max(u1, v1));
        if (i == m) {
            break;
        }
        u1 = ((17 * u1 + 751 + ans + 2 * i) % n) + 1;
        v1 = ((13 * v1 + 593 + ans + 5 * i) % n) + 1;
    }
    cout << u1 << " " << v1 << " " << ans;

    return 0;
}
