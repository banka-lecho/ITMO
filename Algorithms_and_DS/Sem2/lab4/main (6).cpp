#include <iostream>
#include <vector>

using namespace std;

struct MyNode {
    long long val, set, add;
    bool needToChange;
    bool needToAdd;
};

vector<MyNode> tree;
vector<long long> a;

void push(int node) {  // Занимается нашим ленивым проталкиванием
    if (tree[node].needToChange) {
        if ((unsigned int) node * 2 + 1 < tree.size()) {
            tree[node * 2 + 1].val = tree[node].set;
            tree[node * 2 + 1].set = tree[node].set;
            tree[node * 2 + 1].needToChange = true;
            tree[node * 2 + 1].add = 0;
            tree[node * 2 + 1].needToAdd = false;
        }
        if ((unsigned int) node * 2 + 2 < tree.size()) {
            tree[node * 2 + 2].val = tree[node].set;
            tree[node * 2 + 2].set = tree[node].set;
            tree[node * 2 + 2].needToChange = true;
            tree[node * 2 + 2].add = 0;
            tree[node * 2 + 2].needToAdd = false;
        }
        tree[node].needToChange = false;
    }
    if (tree[node].needToAdd) {
        if ((unsigned int) node * 2 + 1 < tree.size()) {
            tree[node * 2 + 1].val += tree[node].add;
            tree[node * 2 + 1].add += tree[node].add;
            tree[node * 2 + 1].needToAdd = true;
        }
        if ((unsigned int) node * 2 + 2 < tree.size()) {
            tree[node * 2 + 2].val += tree[node].add;
            tree[node * 2 + 2].add += tree[node].add;
            tree[node * 2 + 2].needToAdd = true;
        }
        tree[node].add = 0;
        tree[node].needToAdd = false;
    }
}

void build_tree(int left, int right, int node) {  // OK
    if (left == right) {
        tree[node] = MyNode{a[left], 0, 0, false, false};
        return;
    }
    int middle = (left + right) / 2;
    build_tree(left, middle, node * 2 + 1);
    build_tree(middle + 1, right, node * 2 + 2);
    tree[node] = {min(tree[node * 2 + 1].val, tree[node * 2 + 2].val), 0, 0, false, false};
}

long long make_answer(int left, int right, int cur_left, int cur_right, int node) {  // OK
    push(node);
    if (left > cur_right || right < cur_left) {
        return LONG_LONG_MAX;
    }
    if (left <= cur_left && cur_right <= right) {
        return tree[node].val;
    }
    int middle = (cur_left + cur_right) / 2;
    return min(make_answer(left, right, cur_left, middle, node * 2 + 1),
               make_answer(left, right, middle + 1, cur_right, node * 2 + 2));
}


void set(int from, int to, long long element, int left, int right, int node) {  // OK
    push(node);
    if (from <= left && right <= to) {
        tree[node] = {element, element, 0, true, false};
        return;
    }
    int middle = (left + right) / 2;
    if (from <= middle) {
        if (to <= middle) {
            set(from, to, element, left, middle, node * 2 + 1);
        } else {
            set(from, to, element, left, middle, node * 2 + 1);
            set(from, to, element, middle + 1, right, node * 2 + 2);
        }
    } else {
        set(from, to, element, middle + 1, right, node * 2 + 2);
    }
    tree[node].val = min(tree[node * 2 + 1].val, tree[node * 2 + 2].val);
}


void add(int from, int to, long long element, int left, int right, int node) {
    push(node);
    if (from <= left && right <= to) {
        tree[node].val += element;
        tree[node].add += element;
        tree[node].needToAdd = true;
        return;
    }
    int middle = (left + right) / 2;
    if (from <= middle) {
        if (to <= middle) {
            add(from, to, element, left, middle, node * 2 + 1);
        } else {
            add(from, to, element, left, middle, node * 2 + 1);
            add(from, to, element, middle + 1, right, node * 2 + 2);
        }
    } else {
        add(from, to, element, middle + 1, right, node * 2 + 2);
    }
    tree[node].val = min(tree[node * 2 + 1].val, tree[node * 2 + 2].val);
}


int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    size_t tree_size = 2;
    while (tree_size < (unsigned int) n * 2) {
        tree_size *= 2;
    }
    tree.resize(tree_size);
    a.resize(n);
    for (size_t i = 0; i < (unsigned int) n; i++) {
        cin >> a[i];
    }
    build_tree(0, n - 1, 0);
    string operation;
    while (cin >> operation) {
        if (operation == "set") {
            int from, to;
            long long x;
            cin >> from >> to >> x;
            set(from - 1, to - 1, x, 0, n - 1, 0);
        } else if (operation == "add") {
            int from, to;
            long long x;
            cin >> from >> to >> x;
            add(from - 1, to - 1, x, 0, n - 1, 0);
        } else {
            int left, right;
            cin >> left >> right;
            cout << make_answer(left - 1, right - 1, 0, n - 1, 0) << "\n";
        }
    }
    return 0;
}
