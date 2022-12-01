#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const long long INF = 10000000000000;

int main() {
    ifstream cin("salesman.in");
    ofstream cout("salesman.out");
    int n, m;
    cin >> n >> m;
    vector<long long> a(n, INF);
    vector<vector<long long> > r(n, a);  // храним все рёбра
    for (int i = 0; i < m; i++) {  // считываю вершины
        int first, second;
        long long weight;
        cin >> first >> second >> weight;
        first--;
        second--;
        r[first][second] = weight;
        r[second][first] = weight;
    }
    int count = 1 << n;  // сколько всего масок
    vector<vector<long long> > d(count, a);
    // d[mask][i] - минимальный если пройдены mask городов и он в вершине i
    // i - ый бит равен единице, иначе оставляем бесконечность
    for (int i = 0; i < n; i++) {
        d[(1 << i)][i] = 0;
    }
    for (int i = 1; i < count; i++) {  // перебор масок
        for (int j = 0; j < n; j++) {  // перебор вершин
            if (d[i][j] != INF) {
                for (int index = 0; index < n; index++) {  // перебиравем переходы
                    if ((i >> index) % 2 == 0) {
                        d[i + (1 << index)][index] = min(d[i + (1 << index)][index],
                                                         d[i][j] + r[index][j]);
                    }
                }
            }
        }
    }
    long long min = INF;
    for (int i = 0; i < n; i++) {
        // перебираем маску без одной вершины (из неё начинали)
        if (min > d[count - 1][i]) {
            min = d[count - 1][i];
        }
    }
    if (min < INF) {
        cout << min;
    } else {
        cout << -1;
    }
    return 0;
}
