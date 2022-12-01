#include <iostream>
#include <vector>

using namespace std;

vector<unsigned int> arr;

unsigned int a, b;
unsigned int cur = 0;

unsigned int nextRand() {
    cur = cur * a + b;
    return cur >> 8;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    size_t n = 1 << 24;
    arr.resize(n, 0);
    unsigned int m, q;
    cin >> m >> q >> a >> b;
    for (unsigned int i = 0; i < m; i++) {
        unsigned int add = nextRand();
        unsigned int l = nextRand();
        unsigned int r = nextRand();
        if (l > r) {
            swap(l, r);
        }
        arr[l] += add;
        if (r != n - 1) {
            arr[r + 1] -= add;
        }
    }
    for (unsigned int i = 1; i < arr.size(); i++) {
        arr[i] += arr[i - 1];
    }
    for (unsigned int i = 1; i < arr.size(); i++) {
        arr[i] += arr[i - 1];
    }
    unsigned int answer = 0;
    for (unsigned int i = 0; i < q; i++) {
        unsigned int l = nextRand();
        unsigned int r = nextRand();
        if (l > r) {
            swap(l, r);
        }
        if (l == 0) {
            answer += arr[r];
        } else {
            answer += (arr[r] - arr[l - 1]);
        }
    }
    cout << answer;
    return 0;
}
