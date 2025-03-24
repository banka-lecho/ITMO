#include<iostream>
#include<vector>
#include<set>

using namespace std;

int children = 0;

int dfs(vector<vector<int>>& v, vector<int>& t, vector<int>& up, set<int>& points, set<int>& all, int start, int tim, int parent, int root) {
    int res, max;
    //cout << start << " ";
    if (t[start] == -1) {
        if ((start != parent) && (parent == root)) {
            children++;
        }
        all.erase(start);
        t[start] = tim++;
        max = t[start] - 1;
        int min = t[start];
        if (!v[start].empty()) {
            for (int i = 0; i < v[start].size(); i++) {
                if (v[start][i] == parent) {
                    continue;
                }
                int x = dfs(v, t, up, points, all, v[start][i], tim, start, root);
                if (x > max) {
                    max = x;
                }
                if (x < min) {
                    min = x;
                }
            }
            up[start] = min;
            res = up[start];
        }
    } else {
        return t[start];
    }
    if ((max >= t[start]) && (start != parent)) {
        points.insert(start);
    } else if ((start == parent) && (children > 1)) {
        points.insert(start);
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> v(n + 1);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }

    vector<int> t(n + 1, -1);
    vector<int> up(n + 1, -1);
    set<int> points;
    set<int> all;
    for (int i = 1; i <= n; i++) {
        all.insert(i);
    }

    while (!all.empty()) {
        children = 0;
        set<int> :: iterator it = all.begin();
        int x = dfs(v, t, up, points, all, *it, 0, *it, *it);
        //cout << endl;
    }

    cout << points.size() << endl;
    set<int> :: iterator it = points.begin();
    for (int i = 0; it != points.end(); i++, it++) {
        cout << *it << " ";
    }

    return 0;
}