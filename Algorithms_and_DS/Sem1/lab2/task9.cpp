#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;
unsigned int cur = 0;
unsigned int a, b;
unsigned long long res = 0;

unsigned int nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

void Merge(int *arr, int first, int last) {
    int *merge = new int[last - first + 1];
    int middle = (first + last) / 2 + 1;  // крайний элемент правого массива
    int right = middle, left = first;
    for (int i = 0; i < last - first + 1; i++) {
        if ((left < middle) && ((right > last) || (arr[left] <= arr[right]))) {
            merge[i] = arr[left];
            left++;
        } else {
            if (left < middle) {
                res += middle - left;
            }
            merge[i] = arr[right];
            right++;
        }
    }
    for (int i = 0; i < last - first + 1; i++) {
        arr[i + first] = merge[i];
    }
}

void MergeSort(int *arr, int first, int last) {
    if (first < last) {
        MergeSort(arr, first, (first + last) / 2);
        MergeSort(arr, (first + last) / 2 + 1, last);
        Merge(arr, first, last);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m >> a >> b;
    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = nextRand24() % m;
    }
    MergeSort(arr, 0, n - 1);
    cout << res;
    return 0;
}