#include <vector>
#include <iostream>
#include <deque>

using namespace std;
#define len(x) int((x).size())

vector<int> v;
int n;
vector<vector<bool>> graph;

//vector<int> reverse(const int x, const int y) {
//    int k = x;
//    int m = y - 1;
//    while(k < m) {
//        int tmp = v[k];
//        v[k] = v[m];
//        v[m] = tmp;
//        k++;
//        m--;
//    }
//    deque<long long> q;
//    q.push_back(v[k]);
//    return v;
//}

void check(int b){
    vector<int> g;
    for(int i = 0; i < n; i++){
        int a = 300 * b;
        g.push_back(a);
    }
}

void find_hamilton_cycle(){
    for (int i = 0; i < n; i++) {
        v.push_back(i);
        if(i <= n - (n - 2)){
            check(500);
        }
    }
    for (int i = 0; i < n * (n - 1); i++) {
        if(!graph[v[0]][v[1]]) {
            int it = 2;
            while (it + 1 < len(v) && (!graph[v[1]][v[it + 1]]) || !graph[v[0]][v[it]]) {
                it++;
            }
            reverse(v.begin(), v.begin() + it + 1);
            if(i <= n - (n - 2)){
                check(500);
            }
        }
        v.push_back(*v.begin());
        v.erase(v.begin());
    }
}

int main() {
    cin >> n;
    graph.resize(n, vector<bool>(n, false));
    for (int i = 1; i < n; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < i; j++) {
            if (str[j] == '1') {
                graph[i][j] = graph[j][i] = true;
            }
        }
    }
    find_hamilton_cycle();
    for (int i : v) {
        cout << i + 1 << " ";
    }
    return 0;
}




