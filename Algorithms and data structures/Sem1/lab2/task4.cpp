//
// Created by Анастасия Шпилёва on 24.11.2022.
//

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    double A;
    cin >> A;
    bool ok;
    double left = 0, right = A, mid = A / 2;
    while (right - left > 0.000000000001) {
        double prev2 = A, prev1 = mid;
        ok = true;
        for (int i = 0; i < n - 2; i++) {
            double b = 2 * prev1 - prev2 + 2;
            if (b < 0) {
                left = mid;
                mid = (left + right) / 2;
                ok = false;
                break;
            }
            prev2 = prev1;
            prev1 = b;
        }
        if (ok) {
            right = mid;
            mid = (left + right) / 2;
        }
    }
    double prev2 = A, prev1 = (right + left) / 2, b = 1.1;
    for (int i = 0; i < n - 2; i++) {
        b = 2 * prev1 - prev2 + 2;
        prev2 = prev1;
        prev1 = b;
    }
    return 0;
}