//
// Created by Анастасия Шпилёва on 24.11.2022.
//

#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int n = 0;
int a[1000000];

int searchLeft(int a[], int b) {
    int left = 0, right = n - 1;
    int middle = (left + right) / 2;
    while (left != right) {
        if (a[middle] >= b) {
            right = middle;
        } else {
            left = middle + 1;
        }
        middle = (left + right) / 2;
    }
    if (a[left] == b) {
        return left + 1;
    }
    return -1;
}

int searchRight(int a[], int b) {
    int left = 0, right = n - 1;
    int middle = (left + right + 1) / 2;
    while (left != right) {
        if (a[middle] <= b) {
            left = middle;
        } else {
            right = middle - 1;
        }
        middle = (left + right + 1) / 2;
    }
    if (a[right] == b) {
        return right + 1;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        cout << searchLeft(a, k) << " " << searchRight(a, k) << endl;
    }
    return 0;
}