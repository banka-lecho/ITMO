#include <list>
#include <vector>
#include <iostream>

using namespace std;

list<int> path;
vector<vector<int>> graph;
vector<bool> visited;

void find_cycle(){

}

void find_gamilton_path(){
    // TODO: перед каждым добавлением вершины в путь, нужно проверить не содержится ли она в цикле
    path.push_back(0); // добавляем первую вершину
    visited[0] = true;
    int u, v_first, v_last;
    for(int i = 0; graph.size(); i++){
        // далее нам нужно выбрать вершину, которую мы добавим в путь следующей
        int k = 0;
        while(!visited[k]){
            u = k; // нашли нашу вершину
        }
        // проверим, есть ли ребро между последней вершиной в пути и этой
        if(graph[u][path.size() - 1] == 1){ // условие зависит от формата ввода, мб нужно проверить на bool
            path.push_back(u);
            // здесь нужно проверить, мб она находится не в начале и не в конце
            // v_i - первая вершина в пути, для которой ребро uv_i существует
        }else{
            for (auto const& j : path) {
                /// тут какая-то неясная хуйня с итераторами, мб он мне выдаст индекс, а не значение по индексу в path
                if(graph[u][j] == 1){
                    v_first = graph[u][j];
                    break;
                }
                // далее нужно найти такую вторую вершину, что ведет в v_first и ведет в u
                // короч, здесь трабл в том, что нужно проходится по всем вершинам и смотреть чтобы значения столбцов u и v_i совпадали
                // смотри в тердаб на матрицу
            }
        }
    }
}


list<int> find_gamilton_cycle(){
    list<int> gam_path = {1,2,4,3};
    if(graph[gam_path.size() - 1][gam_path[0]] == 1){ // если существует ребро из последней вершины путя в первую, то победа
        return gam_path;
    }
    // теперь ищем вершину, в которую идет ребро из добавляемой вершины
    for(int i = 0; i < graph.size(); i++){
        int vertex_k = gam_path.front();
        int vertex_i = -1;
        for(int j = 0; j < graph[vertex_k].size(); i++){
            if(graph[vertex_k][j] == 1){
                vertex_i = graph[vertex_k][j];
            }
        }
        if(vertex_i != -1){

        }
    }
}

int main(){
    int n;
    cin >> n;
    visited.resize(n, false);
    /// исправить ввод для орграфа
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < s.size(); j++) {
            if (s[j] == '1') {
                graph[i][j] = 1;
                graph[j][i] = 1;
            }
        }
    }
    find_gamilton_path();
}