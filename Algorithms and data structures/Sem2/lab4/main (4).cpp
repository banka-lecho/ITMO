#include <iostream>
#include <vector>

using namespace std;

vector<long long> tree;
vector<long long> a;

void build_tree(int left, int right, int node) {
    if (left == right) {
        tree[node] = a[left];
        return;
    }
    int middle = (left + right) / 2;
    build_tree(left, middle, node * 2 + 1);
    build_tree(middle + 1, right, node * 2 + 2);
    tree[node] = tree[node * 2 + 1] + tree[node * 2 + 2];
}

long long make_answer(int left, int right, int cur_left, int cur_right, int node) {
    if (left > cur_right || right < cur_left) {
        return 0;
    }
    if (left <= cur_left && cur_right <= right) {
        return tree[node];
    }
    int middle = (cur_left + cur_right) / 2;
    return make_answer(left, right, cur_left, middle, node * 2 + 1) +
           make_answer(left, right, middle + 1, cur_right, node * 2 + 2);
}

void set(int pos, long long element, int left, int right, int node) {
    if (left == right) {
        tree[node] = element;
        return;
    }
    int middle = (left + right) / 2;
    if (pos <= middle) {
        set(pos, element, left, middle, node * 2 + 1);
    } else {
        set(pos, element, middle + 1, right, node * 2 + 2);
    }
    tree[node] = tree[node * 2 + 1] + tree[node * 2 + 2];
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);
    unsigned int n;
    cin >> n;
    size_t tree_size = 2;
    while (tree_size < n * 2) {
        tree_size *= 2;
    }
    tree.resize(tree_size);
    a.resize(n);
    for (size_t i = 0; i < n; i++) {
        cin >> a[i];
    }
    build_tree(0, n - 1, 0);
    string operation;
    while (cin >> operation) {
        if (operation == "set") {
            long long x;
            int index;
            cin >> index >> x;
            set(index - 1, x, 0, n - 1, 0);
        } else {
            int left, right;
            cin >> left >> right;
            cout << make_answer(left - 1, right - 1, 0, n - 1, 0) << "\n";
        }
    }
    return 0;
}
