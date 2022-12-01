#include <iostream>
#include <vector>

using namespace std;

int first, second;
int checking_for_emptiness(vector<pair<int,int>> m){
    if(m.empty()){
        return 0;
    }else{
        return 1;
    }
}
pair<int, int> check1(int a, int b){
    if (b == second || b == first) {
        int c = a;
        a = b;
        b = c;
    }
    pair<int, int> ab = {a,b};
    return ab;
}

int right(vector<pair<int,int>> matrix){
    for(int i = 0; i < 5; i++){
        if(matrix.empty()){

        }else{

        }
    }
}

vector<pair<int,int>> tightening(vector<pair<int,int>> matrix, int n){
    vector<bool> visited(n);
    vector<pair<int, int>> matrix_from_check;
    for (auto edge: matrix) {
        pair<int, int> ba = check1(edge.first, edge.second);
        edge.first = ba.first;
        edge.second = ba.second;
        if (edge.first == first || edge.first == second) {
            edge.first = first;
            if (!visited[edge.second]) {
                visited[edge.second] = true;
                matrix_from_check.push_back(edge);
            }
        } else {
            matrix_from_check.push_back(edge);
        }
    }
    return matrix_from_check;
}
vector<int> Polynom(int n, vector<pair<int,int>> matrix){
    if(checking_for_emptiness(matrix) == 0){
        vector<int> graph_uv(n);
        graph_uv.pop_back();
        graph_uv.push_back(1);
        return graph_uv;
    }
    right(matrix);
    first = matrix[matrix.size() - 1].first;
    second = matrix[matrix.size() - 1].second;
    matrix.pop_back();
    vector<bool> visited(n);
    vector<pair<int, int>> matrix1 = tightening(matrix, n);
    vector<int> graph_uv = Polynom(n, matrix);
    vector<int> graph_tightening = Polynom(n - 1, matrix1);
    for (int i = 0; i + 1 < n; i++) {
        graph_uv[i] -= graph_tightening[i];
    }
    return graph_uv;
}
int main(){
    int n, m;
    cin >> n >> m;
    int a, b;
    vector<pair<int,int>> matrix;
    for(int i = 0; i < m; i++){
        cin >> a >> b;
        matrix.emplace_back(a - 1, b - 1);
    }
    vector<int> answer = Polynom(n, matrix);
    cout << n << endl;
    reverse(answer.begin(), answer.end());
    answer.push_back(0);
    for (int an : answer) {
        cout << an << " ";
    }
}