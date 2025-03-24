#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;
vector<vector<long long> > a;
vector<vector<int> > res;
vector<pair<int, int> > m;
ifstream in("matrix.in");
ofstream out("matrix.out");

void returnAnswer(int i1, int j1) {
    if (i1 == j1) {
        out << "A";
    } else {
        out << "(";
        returnAnswer(i1, res[i1][j1]);
        returnAnswer(res[i1][j1] + 1, j1);
        out << ")";
    }
}

int main() {
    int n;
    in >> n;
    m.resize(n, make_pair(0, 0));
    for (int i = 0; i < n; i++) {
        in >> m[i].first >> m[i].second;
    }
    if (n == 1) {
        out << "A";
        return 0;
    }
    vector<long long> b(n, -1);
    a.resize(n, b);
    vector<int> b1(n, -1);
    res.resize(n, b1);
    for (int ind = 1; ind < n; ind++) {
        for (int i = 0; i < n - ind; i++) {
            int q = i + ind;
            a[i][q] = 1e14;
            for (int j = i; j < q; j++) {
                long long t = a[i][j] + a[j + 1][q] + m[i].first * m[q].second * m[j].second;
                if (t < a[i][q]) {
                    a[i][q] = t;
                    res[i][q] = j;
                }
            }
        }
    }
    returnAnswer(0, n - 1);
    return 0;
}
