#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct MyNode {
    int val, add;
    bool needToAdd;
};

struct Side {
    int coord;
    int id;
    int isOpen;
};

bool comp_coord(Side first, Side second) {
    return (first.coord < second.coord);
}

bool comp_open(Side first, Side second) {
    return first.isOpen > second.isOpen;
}

struct Rectangle {
    int x1, y1, x2, y2;
};

const int SHIFT = 1000000;

vector<MyNode> tree;

void push(int node) {  // Занимается нашим ленивым проталкиванием
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
        tree[node] = MyNode{0, 0, false};
        return;
    }
    int middle = (left + right) / 2;
    build_tree(left, middle, node * 2 + 1);
    build_tree(middle + 1, right, node * 2 + 2);
    tree[node] = {0, 0, false};
}

int make_answer(int left, int right, int node) {  // OK
    push(node);
    if (left == right) {
        return left;
    }
    int middle = (left + right) / 2;
    if (tree[node * 2 + 1].val > tree[node * 2 + 2].val) {
        return make_answer(left, middle, node * 2 + 1);
    }
    return make_answer(middle + 1, right, node * 2 + 2);
}

void add(int from, int to, int element, int left, int right, int node) {
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
    tree[node].val = max(tree[node * 2 + 1].val, tree[node * 2 + 2].val);
}


int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<Side> x;
    vector<int> x_sort;
    vector<Rectangle> a(n);
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        a[i] = {x1, y1, x2, y2};
        x.push_back({x1, i, 1});
        x.push_back({x2, i, -1});
    }
    sort(x.begin(), x.end(), comp_coord);
    int start = 0, finish = 0, element = x[0].coord;
    for (int i = 1; i < n * 2 - 1; i++) {
        if (x[i].coord == element) {
            finish++;
        } else {
            sort(x.begin() + start, x.begin() + finish + 1, comp_open);
            start = i;
            finish = i;
            element = x[i].coord;
        }
    }
    if (x[x.size() - 1].coord != element) {
        finish++;
    }
    sort(x.begin() + start, x.begin() + finish + 1, comp_open);
    size_t tree_size = 2;
    while (tree_size < (SHIFT + 1) * 4) {
        tree_size *= 2;
    }
    tree.resize(tree_size);
    build_tree(0, (SHIFT + 1) * 2, 0);  // 1e6 соответсвует координате 0
    int resX = 0, resY = 0;
    int max = 0;
    for (auto &i : x) {
        int id = i.id;
        add(a[id].y1 + SHIFT, a[id].y2 + SHIFT, i.isOpen, 0, (SHIFT + 1) * 2, 0);
        if (tree[0].val > max) {
            max = tree[0].val;
            resX = i.coord;
            resY = make_answer(0, (SHIFT + 1) * 2, 0) - SHIFT;
        }
    }
    cout << max << "\n" << resX << " " << resY;
    return 0;
}
