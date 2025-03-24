#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

vector<int> weight;
vector<int> price;
vector<vector<int> > a;  // строка - кол-во первых предметов
vector<int> res;

void result(int k, int s) {
    if (k != 0) {
        if (a[k - 1][s] == a[k][s]) {
            result(k - 1, s);
        } else {
            res.push_back(k);
            result(k - 1, s - weight[k]);
        }
    }
}

int main() {
    int n, m;
    ifstream cin("knapsack.in");
    ofstream cout("knapsack.out");
    cin >> n >> m;
    a.resize(n + 1);
    weight.resize(n + 1);
    price.resize(n + 1);
    for (int i = 0; i < n + 1; i++) {
        a[i].resize(m + 1, 0);
    }
    for (int i = 1; i < n + 1; i++) {
        cin >> weight[i];
    }
    for (int i = 1; i < n + 1; i++) {
        cin >> price[i];
    }
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < m + 1; j++) {
            if (j - weight[i] >= 0) {
                a[i][j] = max(a[i - 1][j], a[i - 1][j - weight[i]] + price[i]);
            } else {
                a[i][j] = a[i - 1][j];
            }
        }
    }
    result(n, m);
    cout << res.size() << "\n";
    sort(res.begin(), res.end());
    for (unsigned int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
    }
    return 0;
}
