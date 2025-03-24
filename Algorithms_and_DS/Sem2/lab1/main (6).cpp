#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int n;
vector<long long> a, b;
vector<vector<pair<int, long long> > > r;
vector<bool> visit;

void dfs(int i) {
    visit[i] = true;
    for (unsigned int q = 0; q < r[i].size(); q++) {
        int index = r[i][q].first;
        if (!visit[index]) {
            dfs(r[i][q].first);
            long long w = r[i][q].second;
            if (a[i] < b[index] + w - max(a[index], b[index])) {
                a[i] = b[index] + w - max(a[index], b[index]);
            }
            b[i] += max(a[index], b[index]);
        }
    }
    a[i] += b[i];
}

int main() {
    ifstream in("matching.in");
    ofstream out("matching.out");
    in >> n;
    b.resize(n, 0);
    a.resize(n, 0);
    r.resize(n);
    visit.resize(n, false);
    for (int i = 0; i < n - 1; i++) {
        int v1, v2;
        long long w;
        in >> v1 >> v2 >> w;
        r[v1 - 1].push_back(make_pair(v2 - 1, w));
        r[v2 - 1].push_back(make_pair(v1 - 1, w));
    }
    dfs(0);
    out << max(a[0], b[0]);
    return 0;
}
