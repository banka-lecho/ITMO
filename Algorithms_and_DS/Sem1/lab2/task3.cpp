//
// Created by Анастасия Шпилёва on 24.11.2022.
//

#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int n = 0;
int a[30000000];

int partition(int left, int right) {
    int marker = left;
    for (int i = left; i < right; i++) {
        if (a[i] <= a[right] && i <= (left + right - 1) / 2) {
            swap(a[i], a[marker]);
            marker++;
        } else if (a[i] < a[right] && i > (left + right - 1) / 2) {
            swap(a[i], a[marker]);
            marker++;
        }
    }
    swap(a[marker], a[right]);
    return marker;
}

int searchKStatistics(int k) {
    int left = 0, right = n - 1;
    while (true) {
        int mid = partition(left, right);
        if (mid == k) {
            return a[mid];
        } else if (k < mid) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    int k;
    cin >> k;
    int A, B, C;
    cin >> A >> B >> C;
    cin >> a[0] >> a[1];
    for (int i = 2; i < n; i++) {
        a[i] = C + B * a[i - 1] + A * a[i - 2];
    }
    cout << searchKStatistics(k - 1);
    return 0;
}