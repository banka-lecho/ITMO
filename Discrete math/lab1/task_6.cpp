#include <vector>
#include <iostream>
#include <set>

using namespace std;

vector<int> prufer;
vector<int> deg;
set<int> v;
int n;

void decode_prufer(){
    for (int i = 0; i < n - 2; i++) {
        int min_v = *v.begin();
        v.erase(v.begin());
        cout << min_v + 1 << " " << prufer[i] + 1 << "\n";
        deg[prufer[i]]--;
        if (deg[prufer[i]] == 1) {
            v.insert(prufer[i]);
        }
    }
}

int main() {
    cin >> n;
    prufer.resize(n - 2);
    deg.resize(n, 1);
    // ошибка в том, что я не проверяю, дублируются ли вершины в коде прюфера и в массиве v
    for (int i = 0; i < n - 2; i++) {
        cin >> prufer[i];
        prufer[i]--;
        deg[prufer[i]]++;
    }
    for (int i = 0; i < deg.size(); i++) {
        if (deg[i] == 1) {
            v.insert(i);
        }
    }
    decode_prufer();
    cout << *v.begin() + 1 << " " << *--v.end() + 1;
    return 0;
}