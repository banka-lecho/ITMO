#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct element {
    string key;
    string element;
    bool deleted;
};

const int mod = 996487;
vector<vector<element> > hashTable;
ifstream in("map.in");
ofstream out("map.out");

int count_hash(string key) {
    long hash = 0;
    for (unsigned int i = 0; i < key.length(); i++) {
        hash += (i + 1) * key[i] * 13;
        hash %= mod;
    }
    return (int) hash;
}

void put(string key, string element1) {
    int index = count_hash(key);
    for (auto &i : hashTable[index]) {
        if (i.key == key && !i.deleted) {
            i.element = element1;
            return;
        }
    }
    element a = {key, element1, false};
    hashTable[index].push_back(a);
}

void delete_key(string key) {
    int index = count_hash(key);
    for (size_t i = 0; i < hashTable[index].size(); i++) {
        if (hashTable[index][i].key == key && !hashTable[index][i].deleted) {
            hashTable[index][i].deleted = true;
            return;
        }
    }
}

void get(string key) {
    int index = count_hash(key);
    for (auto &i : hashTable[index]) {
        if (i.key == key && !i.deleted) {
            out << i.element << "\n";
            return;
        }
    }
    out << "none\n";
}

int main() {
    string s;
    vector<element> a;
    hashTable.resize(mod, a);
    while (in >> s) {
        string key;
        in >> key;
        if (s == "put") {
            string element;
            in >> element;
            put(key, element);
        } else if (s == "delete") {
            delete_key(key);
        } else {
            get(key);
        }
    }
    return 0;
}
