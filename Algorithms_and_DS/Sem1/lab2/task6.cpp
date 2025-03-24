//
// Created by Анастасия Шпилёва on 24.11.2022.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

vector<int> a;
int number;

int main() {
    int n;
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    for (int i = 0; i < n; i++) {
        int q = a[i];
        a[i] = a[i / 2];
        a[i / 2] = q;
    }
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}