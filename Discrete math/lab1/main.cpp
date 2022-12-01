#include <vector>
#include <iostream>
#include <deque>
#include <random>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 4001;

bool g[N][N];

int main() {
    int n;
    cin >> n;
    string g_str;
    for (int i = 1; i < n; i++) {
        cin >> g_str;
        for (int j = 0; j < i; j++) {
            if (g_str[j] == '1') {
                g[i][j] = g[j][i] = true;
            }
        }
    }
    deque<int> d;
    for (int i = 0; i < n; i++) {
        d.push_back(i);
    }
    while (clock() < CLOCKS_PER_SEC * 0.95) {
        for (int j = 0; j < n * (n - 1); j++) {
            if (!g[d[0]][d[1]]) {
                int pos = 2;
                while (pos + 1 < len(d) && (!g[d[0]][d[pos]] || !g[d[1]][d[pos + 1]])) {
                    pos++;
                }
                reverse(d.begin() + 1, d.begin() + pos + 1);
            }
            d.push_back(d.front());
            d.pop_front();
        }
        bool ok = true;
        for (int i = 0; i < len(d) - 1; i++) {
            if (!g[d[i]][d[i + 1]]) {
                ok = false;
                break;
            }
        }
        ok &= g[d.back()][d.front()];
        if (!ok) {
            shuffle(all(d), std::mt19937(std::random_device()()));
            continue;
        }
        break;
    }
    for (auto i : d) {
        cout << i + 1 << ' ';
    }
    return 0;
}