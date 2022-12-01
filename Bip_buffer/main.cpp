#include <iostream>
#include <vector>

using namespace std;

struct Sets {
    int val;
    int point;
};

vector<Sets> parent;
vector<int> rang;
int n, m, sum;

void make_set(int v) {
    parent[v].val = v;
    parent[v].point = 0;
    rang[v] = 0;
}

// Такая простая реализация делает всё, что задумывалось: сначала путём рекурсивных вызовов находит лидера множества,
// а затем, в процессе раскрутки стека, этот лидер присваивается ссылкам parent для всех пройденных элементов.
int find(int g) {
    if (g == parent[g].val) {
        sum = 0;
        return g;
    }else{
        // перенаправив их parent[] на эту вершину p - лидера.
        parent[g].val = find(parent[g].val);
        parent[g].point += sum;
        parent[g].val = parent[g].val;
        sum = parent[g].point;
        return parent[g].val;
    }
}

void add(int x, int val) {
    x = find(x);
    parent[x].point += val;
}

void union_set(int k, int l) {
    k = find(k);
    l = find(l);
    if (k != l) {
        if (rang[k] < rang[l]) { swap(k, l); }
        parent[l].val = k;
        parent[l].point -= parent[k].point;
        if (rang[k] == rang[l]) { rang[k]++; }
    }

}

int main() {
    cin >> n >> m;
    parent.resize(n + 1);
    rang.resize(n + 1);
    string operation;
    int a, b, c, d, e, h;
    for (int i = 1; i <= n; i++) {
        make_set(i);
    }
    for(int i = 0; i < m; i++) {
        cin >> operation;
        if (operation == "add") {
            cin >> a >> b;
            add(a, b);
        } else if (operation == "join") {
            cin >> c >> d;
            union_set(c, d);
        } else {
            cin >> e;
            h = find(e);
            if (e == h) {
                cout << parent[e].point << "\n";
            } else {
                cout << parent[e].point + parent[h].point << "\n";
            }
        }
    }
}