#include <iostream>
#include <vector>

using namespace std;

vector<vector<pair<int, int> > > table;
vector<vector<int> > tree;
vector<bool> visit;  // для dfs
vector<pair<int, int> > a;  // массив на котором строим до
vector<int> depth;  // глубина конкретной вершины
vector<int> k;  // здесь храним k
vector<int> pow2;  // здесь храним 2^k
vector<int> pos;

void build_table() {
    vector<pair<int, int> > b(k[a.size()] + 1, {0, 0});
    table.resize(a.size() + 1, b);
    for (unsigned int i = 1; i < a.size() + 1; i++) {
        table[i][0] = a[i];
    }
    for (size_t j = 1; j < (unsigned int) k[a.size()] + 1; j++) {
        for (size_t i = 1; i < a.size() + 1; i++) {
            if (j > (unsigned int) k[a.size() - i + 1]) {
                break;
            }

            table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            if (table[i][j - 1].first < table[i + (1 << (j - 1))][j - 1].first) {
                table[i][j] = table[i][j - 1];
            } else {
                table[i][j] = table[i + (1 << (j - 1))][j - 1];
            }
        }
    }
}

pair<int, int> find_min(int left, int right) {
    int len = right - left + 1;
    return min(table[left][k[len]], table[right - pow2[len] + 1][k[len]]);
}

void count_depth(int node) {
    pos[node] = a.size();
    a.push_back({depth[node], node});
    for (size_t i = 0; i < tree[node].size(); i++) {
        depth[tree[node][i]] = depth[node] + 1;
        count_depth(tree[node][i]);
        a.push_back({depth[node], node});
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    // Считали дерево
    int n, m;
    cin >> n >> m;
    pos.resize(n);
    tree.resize(n);
    for (int i = 1; i < n; i++) {
        int parent;
        cin >> parent;
        tree[parent].push_back(i);
    }

    // Посчитали глубину каждой вершины, подготовили массив для до
    depth.resize(n);
    depth[0] = 0;
    a.push_back({0, 0});
    count_depth(0);

    // Предподсчёт степеней 2
    pow2.resize(a.size() + 1);
    k.resize(a.size() + 1);
    pow2[0] = 0;
    k[0] = 0;
    pow2[1] = 1;
    k[1] = 0;
    for (unsigned int i = 2; i < a.size() + 1; i++) {
        if (i >= (unsigned int) 2 * pow2[i - 1]) {
            pow2[i] = pow2[i - 1] * 2;
            k[i] = k[i - 1] + 1;
        } else {
            k[i] = k[i - 1];
            pow2[i] = pow2[i - 1];
        }
    }

    // Построили таблицу
    build_table();

    // Обработка запросов
    int x, y, z;
    vector<int> request(2 * m + 1, 0);
    cin >> request[1] >> request[2] >> x >> y >> z;
    for (size_t i = 3; i < request.size(); i++) {
        request[i] = (request[i - 2] * x + request[i - 1] * y + z) % n;
    }
    long long result = 0;
    int ans = 0;
    for (int i = 1; i < m + 1; i++) {
        size_t l = min(pos[(request[2 * i - 1] + ans) % n], pos[request[2 * i]]);
        size_t r = max(pos[(request[2 * i - 1] + ans) % n], pos[request[2 * i]]);
        // cout << l << " :границы запроса: " << r << endl;
        pair<int, int> res = find_min(l, r);
        ans = res.second;
        result += res.second;
        // cout << ans << endl;
    }
    cout << result;
    return 0;
}
