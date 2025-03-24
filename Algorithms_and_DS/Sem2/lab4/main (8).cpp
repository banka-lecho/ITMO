#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int k;

struct request {
    int left, right, id;
};

bool comp(request const &first, request const &second) {
    if (first.left / k != second.left / k) {
        return first.left < second.left;
    }
    return first.right < second.right;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    vector<request> requests(m);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        requests[i] = {l - 1, r - 1, i};
    }
    int a = 1, b = 0;  // создаём отрезок
    vector<long long> numbers(1e6, 0);
    long long answ = 0;  // ответ для отрезка
    k = (int) sqrt(n);
    sort(requests.begin(), requests.end(), comp);
    vector<long long> res(m);
    for (auto &request : requests) {
        while (a > request.left) {
            a--;
            answ += (2 * numbers[arr[a]] + 1) * arr[a];
            numbers[arr[a]]++;
        }
        while (b < request.right) {
            b++;
            answ += (2 * numbers[arr[b]] + 1) * arr[b];
            numbers[arr[b]]++;
        }
        while (a < request.left) {
            answ += (1 - 2 * numbers[arr[a]]) * arr[a];
            numbers[arr[a]]--;
            a++;
        }
        while (b > request.right) {
            answ += (1 - 2 * numbers[arr[b]]) * arr[b];
            numbers[arr[b]]--;
            b--;
        }
        res[request.id] = answ;
    }
    for (long long re : res) {
        cout << re << "\n";
    }
    return 0;
}
