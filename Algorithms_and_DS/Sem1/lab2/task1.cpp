//
// Created by Анастасия Шпилёва on 24.11.2022.
//

#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

void Merge(int *a, int first, int last) {
    int *merge = new int[last - first + 1];
    int middle = (first + last) / 2 + 1;  // крайний элемент правого массива
    int right = middle, left = first;
    for (int i = 0; i < last - first + 1; i++) {
        if ((left < middle) && ((right > last) || (a[left] < a[right]))) {
            merge[i] = a[left];
            left++;
        } else {
            merge[i] = a[right];
            right++;
        }
    }
    for (int i = 0; i < last - first + 1; i++) {
        a[i + first] = merge[i];
    }
}

void MergeSort(int *a, int first, int last) {
    if (first < last) {
        MergeSort(a, first, (first + last) / 2);
        MergeSort(a, (first + last) / 2 + 1, last);
        Merge(a, first, last);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    MergeSort(a, 0, n - 1);
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}