#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

vector<pair<int, int> > a;
vector<int> push;  // номер операции + храним индекс в а

void siftUp(int x) {
    while (a[(x - 1) / 2].first > a[x].first) {
        swap(push[a[x].second], push[a[(x - 1) / 2].second]);
        swap(a[(x - 1) / 2], a[x]);
        x = (x - 1) / 2;
    }
}

void siftDown(unsigned int x) {
    while (2 * x + 1 < a.size()) {
        unsigned int left = 2 * x + 1;
        unsigned int right = left + 1;
        int j = left;
        if (right < a.size()) {
            if (a[right].first <= a[left].first) {
                j = right;
            }
        }
        if (a[x].first < a[j].first) {
            break;
        } else {
            swap(push[a[x].second], push[a[j].second]);
            swap(a[x], a[j]);
        }
        x = j;
    }
}

pair<int, int> extractMin() {
    push.push_back(-1);
    if (a.size() == 0) {
        return make_pair(-1, -1);
    } else {
        pair<int, int> res = a[0];
        push[a[0].second] = -1;
        /*a[0] = a[a.size() - 1];
        swap(push[a[0].second], push[a[a.size() - 1].second]);*/
        push[a[a.size() - 1].second] = 0;
        swap(a[0], a[a.size() - 1]);
        a.pop_back();
        siftDown(0);
        return res;
    }
}

int main() {
    string s;
    while (cin >> s) {
        if (s == "push") {
            push.push_back(a.size());
            int x;
            cin >> x;
            a.push_back(make_pair(x, push.size() - 1));
            siftUp(a.size() - 1);
        } else if (s == "extract-min") {
            pair<int, int> q = extractMin();
            if (q.second == -1) {
                cout << "*\n";
            } else {
                cout << q.first << " " << q.second + 1 << "\n";
            }
        } else {
            push.push_back(-1);
            int x, y;
            cin >> x >> y;
            if (push[x - 1] != -1) {
                a[push[x - 1]].first = y;
                siftUp(push[x - 1]);
            }
        }
    }
    return 0;
}


/*
 push 1
push 2
decrease-key 2 0
extract-min
extract-min
extract-min
push 3
decrease-key 7 0
extract-min
 */
