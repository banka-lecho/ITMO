#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> arr;

int bin_search(int key) {
    int l = -1;
    int r = (int) arr.size();
    string answ;
    while (l < r - 1) {
        int m = (l + r) / 2;
        cout << 1 << " " << arr[m] << " " << key << endl;
        cin >> answ;
        if (answ == "YES") {
            l = m;
        } else {
            r = m;
        }
    }
    return r;
}


int main() {
    arr.resize(1, 1);
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int position = bin_search(i);
        arr.insert(arr.begin() + position, i);
    }
    cout << 0 << " ";
    for (int i : arr) {
        cout << i << " ";
    }
}