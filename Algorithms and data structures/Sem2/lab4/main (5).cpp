#include <iostream>
#include <vector>

using namespace std;

struct matrix {
    int a11, a12, a21, a22;

    void printString() const {
        cout << a11 << " " << a12 << "\n";
        cout << a21 << " " << a22 << "\n\n";
    }
};

const matrix E = {1, 0, 0, 1};
int r;

matrix multMatrix(matrix first, matrix second) {
    matrix res{};
    res.a11 = (first.a11 * second.a11 + first.a12 * second.a21) % r;
    res.a12 = (first.a11 * second.a12 + first.a12 * second.a22) % r;
    res.a21 = (first.a21 * second.a11 + first.a22 * second.a21) % r;
    res.a22 = (first.a21 * second.a12 + first.a22 * second.a22) % r;
    return res;
}

vector<matrix> tree;
vector<matrix> a;

void build_tree(int left, int right, int node) {
    if (left == right) {
        tree[node] = a[left];
        return;
    }
    int middle = (left + right) / 2;
    build_tree(left, middle, node * 2 + 1);
    build_tree(middle + 1, right, node * 2 + 2);
    tree[node] = multMatrix(tree[node * 2 + 1], tree[node * 2 + 2]);
}

matrix make_answer(int left, int right, int cur_left, int cur_right, int node) {
    if (left > cur_right || right < cur_left) {
        return E;
    }
    if (left <= cur_left && cur_right <= right) {
        return tree[node];
    }
    int middle = (cur_left + cur_right) / 2;
    return multMatrix(make_answer(left, right, cur_left, middle, node * 2 + 1),
                      make_answer(left, right, middle + 1, cur_right, node * 2 + 2));
}

void set(int pos, matrix element, int left, int right, int node) {
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
    tree[node] = multMatrix(tree[node * 2 + 1], tree[node * 2 + 2]);
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);
    int n, m;
    cin >> r >> n >> m;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        int a11, a12, a21, a22;
        cin >> a11 >> a12 >> a21 >> a22;
        a[i] = matrix{a11, a12, a21, a22};
    }
    size_t tree_size = 2;
    while (tree_size < (unsigned int) n * 2) {
        tree_size *= 2;
    }
    tree.resize(tree_size);
    build_tree(0, n - 1, 0);
    for (int i = 0; i < m; i++) {
        int left, right;
        cin >> left >> right;
        make_answer(left - 1, right - 1, 0, n - 1, 0).printString();
    }
    return 0;
}
