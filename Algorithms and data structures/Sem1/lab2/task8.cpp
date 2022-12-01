//
// Created by Анастасия Шпилёва on 24.11.2022.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

vector<unsigned int> arr, arr2;
vector<vector<unsigned int> > buckets;
unsigned int cur = 0;
int a, b;

unsigned int nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

unsigned int nextRand32() {
    unsigned int a = nextRand24(), b = nextRand24();
    return (a << 8) ^ b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    unsigned int t, n;
    cin >> t >> n;
    for (unsigned int j = 0; j < t; j++) {
        arr.clear();
        arr2.clear();
        arr.resize(n);
        arr2.resize(n);
        cin >> a >> b;
        for (unsigned int i = 0; i < n; i++) {
            arr[i] = nextRand32();
        }
        unsigned int x = 1 << 16;
        vector<unsigned int> q(x, 0);
        for (unsigned int i = 0; i < n; i++) {
            q[arr[i] % x]++;
        }
        unsigned int count = 0;
        for (unsigned int i = 0; i < x; i++) {
            int q1 = q[i];
            q[i] = count;
            count += q1;
        }
        for (unsigned int i = 0; i < n; i++) {
            arr2[q[arr[i] % x]] = arr[i];
            q[arr[i] % x]++;
        }
        arr = arr2;
        q.clear();
        q.resize(x, 0);
        for (unsigned int i = 0; i < n; i++) {
            q[arr[i] / x]++;
        }
        count = 0;
        for (unsigned int i = 0; i < x; i++) {
            int q1 = q[i];
            q[i] = count;
            count += q1;
        }
        for (unsigned int i = 0; i < n; i++) {
            arr2[q[arr[i] / x]] = arr[i];
            q[arr[i] / x]++;
        }
        arr = arr2;
        unsigned long long result = 0;
        for (unsigned int i = 0; i < n; i++) {
            result += (long long) arr[i] * ((i + 1));
        }
        cout << result << "\n";
    }
    return 0;
}