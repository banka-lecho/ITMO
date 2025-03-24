#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

unsigned int q;
unsigned int a, b;
unsigned int cur = 0;
vector<unsigned int> arr;

struct node {
    vector<unsigned int> sorted_vector;
    unsigned int left;
    unsigned int right;
};

vector<node> tree;

unsigned int nextRand17() {
    cur = cur * a + b;
    return cur >> 15;
}

unsigned int nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

void build_tree(unsigned int left, unsigned int right, int node) {
    if (left == right) {
        tree[node] = {{arr[left]}, left, left};
        return;
    }
    unsigned int middle = (left + right) / 2;
    build_tree(left, middle, node * 2 + 1);
    build_tree(middle + 1, right, node * 2 + 2);
    unsigned int first_size = tree[node * 2 + 1].sorted_vector.size();
    unsigned int second_size = tree[node * 2 + 2].sorted_vector.size();
    vector<unsigned int> res(first_size + second_size);
    unsigned int index_first = 0, index_second = 0;
    unsigned int index = 0;
    while (index != first_size + second_size) {
        if (index_first == first_size) {
            res[index] = tree[node * 2 + 2].sorted_vector[index_second];
            index_second++;
        } else if (index_second == second_size) {
            res[index] = tree[node * 2 + 1].sorted_vector[index_first];
            index_first++;
        } else {
            if (tree[node * 2 + 1].sorted_vector[index_first]
                < tree[node * 2 + 2].sorted_vector[index_second]) {
                res[index] = tree[node * 2 + 1].sorted_vector[index_first];
                index_first++;
            } else {
                res[index] = tree[node * 2 + 2].sorted_vector[index_second];
                index_second++;
            }
        }
        index++;
    }
    tree[node] = {res, left, right};
}

unsigned int query(int node, unsigned int l, unsigned int r, unsigned int x, unsigned int y) {
    if (tree[node].left == l && tree[node].right == r) {
        vector<unsigned int> &w = tree[node].sorted_vector;
        unsigned int left_ind = (unsigned int) (lower_bound(w.begin(), w.end(), x) - w.begin());
        unsigned int right_ind = (unsigned int) (upper_bound(w.begin(), w.end(), y) - w.begin());
        return right_ind - left_ind;
    }
    unsigned int middle = (tree[node].right + tree[node].left) / 2;
    if (r <= middle) {
        return query(2 * node + 1, l, r, x, y);
    }
    if (l > middle) {
        return query(2 * node + 2, l, r, x, y);
    }
    return query(2 * node + 1, l, middle, x, y) + query(2 * node + 2, middle + 1, r, x, y);
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> q >> a >> b;
    arr.resize(1 << 17);
    for (unsigned int &i : arr) {
        i = nextRand24();
    }
    tree.resize(1 << 18);
    build_tree(0, (1 << 17) - 1, 0);
    unsigned int answer = 0;
    for (unsigned int i = 0; i < q; i++) {
        unsigned int l = nextRand17();
        unsigned int r = nextRand17();
        if (l > r) {
            swap(l, r);
        }
        unsigned int x = nextRand24();
        unsigned int y = nextRand24();
        if (x > y) {
            swap(x, y);
        }
        unsigned int ans = query(0, l, r, x, y);
        answer += ans;
        b += ans;
    }
    cout << answer;
    return 0;
}
