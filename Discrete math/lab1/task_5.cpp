//
// Created by Анастасия Шпилёва on 07.11.2022.
//

#include <iostream>
#include <vector>
#include <set>

using namespace std;

int n;
vector<vector<int>> graph;
vector<int> prufer, degree;
set<int> lists;
vector<bool> deleted;

void first_lists(){
    for(int i = 0; i < n; i++){
        if(graph[i].size() == 1){
            lists.insert(i);
        }
        degree[i] = graph[i].size();
    }
}

void codeOfPrufer(){
    first_lists();
    int free;
    for(int i = 0; i < n - 2; i++){
        int start = *lists.begin();
        deleted[start] = true;
        lists.erase(start);
        for(int j : graph[start]){
            if(!deleted[j]){
                free = j;
            }
        }
        prufer[i] = free;
        degree[free]--;
        if(degree[free] == 1){
            lists.insert(free);
        }
    }
}


int main() {
    cin >> n;
    int x, y;
    graph.resize(n);
    deleted.resize(n, false);
    prufer.resize(n-2);
    degree.resize(n);
    for(int i = 0; i < n - 1;i++) {
        cin >> x >> y;
        graph[x - 1].push_back(y - 1);
        graph[y - 1].push_back(x - 1);
    }
    codeOfPrufer();
    for(int i : prufer){
        cout << i + 1 << " ";
    }
}