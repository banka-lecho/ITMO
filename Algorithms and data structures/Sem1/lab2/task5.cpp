//
// Created by Анастасия Шпилёва on 24.11.2022.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    if (k > m) {
        k = m;
    }
    vector<string> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = m - 1; i != (m - k) - 1; i--) {
        vector<int> symbol(128, 0);
        for (int j = 0; j < n; j++) {
            symbol[a[j][i]]++;
        }
        int count = 0;
        for (int j = 0; j < 128; j++) {
            int q = symbol[j];
            symbol[j] = count;
            count += q;
        }
        for (int j = 0; j < n; j++) {
            b[symbol[a[j][i]]] = a[j];
            symbol[a[j][i]]++;
        }
        a = b;
    }
    for (int i = 0; i < n; i++) {
        cout << a[i] << '\n';
    }
    return 0;
}