#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> chromaticPolynom(vector<pair<int, int>> edges, int n) {
    if (edges.empty()) {
        vector<int> ans(n);
        ans[n - 1] = 1;
        return ans;
    }
    pair<int, int> last = edges.back();
    edges.pop_back();
    vector<bool> s(n);
    vector<pair<int, int>> new_edges;
    for (auto e: edges) {
        if (e.second == last.second || e.second == last.first) {
            swap(e.first, e.second);
        }
        if (e.first == last.first || e.first == last.second) {
            e.first = last.first;
            if (!s[e.second]) {
                s[e.second] = true;
                new_edges.push_back(e);
            }
        } else {
            new_edges.push_back(e);
        }
    }
    vector<int> ans1 = chromaticPolynom(new_edges, n - 1);
    vector<int> ans = chromaticPolynom(edges, n);
    for (int i = 0; i + 1 < n; i++) {
        ans[i] -= ans1[i];
    }
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back(make_pair(u - 1, v - 1));
    }
    vector<int> ans = chromaticPolynom(edges, n);
    cout << n << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[ans.size() - 1 - i] << " ";
    }
    cout << "0" << endl;
}