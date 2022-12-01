#include <iostream>
#include <vector>

using namespace std;

struct MyNode {
    bool isEmpty;
    int minPos;
};

vector<MyNode> tree;

void build_tree(int left, int right, int node) {
    if (left == right) {
        tree[node] = {true, left};
        return;
    }
    int middle = (left + right) / 2;
    build_tree(left, middle, node * 2 + 1);
    build_tree(middle + 1, right, node * 2 + 2);
    tree[node].isEmpty = (tree[node * 2 + 1].isEmpty || tree[node * 2 + 2].isEmpty);
    tree[node].minPos = min(tree[node * 2 + 1].minPos, tree[node * 2 + 2].minPos);
}

MyNode make_answer(int left, int right, int cur_left, int cur_right, int node) {
    if (left > cur_right || right < cur_left) {
        return {false, INT_MAX};
    }
    if (left <= cur_left && cur_right <= right) {
        return tree[node];
    }
    int middle = (cur_left + cur_right) / 2;
    MyNode first = make_answer(left, right, cur_left, middle, node * 2 + 1);
    MyNode second = make_answer(left, right, middle + 1, cur_right, node * 2 + 2);
    MyNode res{};
    res.isEmpty = (first.isEmpty || second.isEmpty);
    if (res.isEmpty) {
        if (first.isEmpty) {
            res.minPos = first.minPos;
            return res;
        }
        res.minPos = second.minPos;
    }
    return res;
}

void set(int pos, bool element, int left, int right, int node) {
    if (left == right) {
        tree[node].isEmpty = element;
        return;
    }
    int middle = (left + right) / 2;
    if (pos <= middle) {
        set(pos, element, left, middle, node * 2 + 1);
    } else {
        set(pos, element, middle + 1, right, node * 2 + 2);
    }
    tree[node].isEmpty = (tree[node * 2 + 1].isEmpty || tree[node * 2 + 2].isEmpty);
    if (tree[node].isEmpty) {
        if (tree[node * 2 + 1].isEmpty) {
            tree[node].minPos = tree[node * 2 + 1].minPos;
            return;
        }
        tree[node].minPos = tree[node * 2 + 2].minPos;
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    size_t tree_size = 2;
    while (tree_size < (unsigned int) n * 2) {
        tree_size *= 2;
    }
    tree.resize(tree_size);
    build_tree(0, n - 1, 0);
    string operation;
    for (int i = 0; i < m; i++) {
        cin >> operation;
        int index;
        cin >> index;
        index--;
        if (operation == "enter") {
            MyNode temp = make_answer(index, n - 1, 0, n - 1, 0);
            if (temp.isEmpty) {
                cout << temp.minPos + 1 << "\n";
            } else {
                temp = make_answer(0, index, 0, n - 1, 0);
                cout << temp.minPos + 1 << "\n";
            }
            set(temp.minPos, false, 0, n - 1, 0);
        } else {
            set(index, true, 0, n - 1, 0);
        }
    }
    return 0;
}
