#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

int n;
vector<int> b;
vector<int> data1;

int searchRight(int a) {
    int left = 0, right = n;
    int middle = (left + right + 1) / 2;
    while (left != right) {
        if (b[middle] < a) {
            left = middle + 1;
        } else {
            right = middle;
        }
        middle = (left + right) / 2;
    }
    return right;
}

int main() {
    ifstream cin("lis.in");
    ofstream cout("lis.out");
    cin >> n;
    data1.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> data1[i];
    }
    vector<pair<int, int> > q;
    vector<vector<pair<int, int> > > a(n + 1, q);
    b.resize(n + 2, INT_MAX);
    b[0] = INT_MIN;
    for (int i = 1; i < n + 1; i++) {
        int q = searchRight(data1[i - 1]);
        b[q] = data1[i - 1];
        a[q].push_back(make_pair(i, data1[i - 1]));
    }
    vector<int> result;
    int index = 0;
    for (int i = 1; i < n + 2; i++) {
        if (b[i] == INT_MAX) {
            index = i - 1;
            break;
        }
    }
    for (unsigned int i = 0; i < a.size(); i++) {
        sort(a[i].begin(), a[i].end());
    }
    int w = INT_MAX;
    for (int i = index; i >= 1; i--) {
        for (int j = a[i].size() - 1; j >= 0; j--) {
            if (a[i][j].first < w) {
                result.push_back(a[i][j].second);
                w = a[i][j].first;
                break;
            } else {
                a[i].resize(a[i].size() - 1);
            }
        }
    }
    cout << result.size() << "\n";
    for (int i = result.size() - 1; i >= 0; i--) {
        cout << result[i] << " ";
    }
    return 0;
}
