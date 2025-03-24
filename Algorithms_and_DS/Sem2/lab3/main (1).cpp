#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int mod = 996487;
vector<vector<int> > hashTable;

int count_hash(int x) {
    return abs(x) % mod;
}

bool exists(int x) {
    int index = count_hash(x);
    for (int i : hashTable[index]) {
        if (i == x) {
            return true;
        }
    }
    return false;
}

void insert(int x) {
    if (!exists(x)) {
        hashTable[count_hash(x)].push_back(x);
    }
}

void deleteElement(int x) {
    int index = count_hash(x);
    for (size_t i = 0; i < hashTable[index].size(); i++) {
        if (hashTable[index][i] == x) {
            hashTable[index].erase(hashTable[index].begin() + i);
            return;
        }
    }
}

int main() {
    ifstream in("set.in");
    ofstream out("set.out");
    string s;
    vector<int> a;
    hashTable.resize(mod, a);
    while (in >> s) {
        int number;
        in >> number;
        if (s == "exists") {
            if (exists(number)) {
                out << "true\n";
            } else {
                out << "false\n";
            }
        } else if (s == "delete") {
            deleteElement(number);
        } else {
            insert(number);
        }
    }
    return 0;
}
