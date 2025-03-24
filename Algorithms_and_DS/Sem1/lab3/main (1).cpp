#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n + 1);
    a[0] = -1;
    for (int i = 1; i < n + 1; i++) {
        cin >> a[i];
    }
    bool ok = true;
    for (int i = 1; i < n / 2 + 2; i++) {
        if (i * 2 <= n) {
            if (a[i] > a[i * 2]) {
                ok = false;
                break;
            }
        }
        if (i * 2 + 1 <= n) {
            if (a[i] > a[i * 2 + 1]) {
                ok = false;
                break;
            }
        }
    }
    if (ok) {
        cout << "YES";
        return 0;
    }
    cout << "NO";
    return 0;
}
