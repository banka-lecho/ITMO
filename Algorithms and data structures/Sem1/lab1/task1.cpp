//
// Created by Анастасия Шпилёва on 24.11.2022.
//

#include <iostream>
#include <stdlib.h>

using namespace std;

class MyVector {
public:
    MyVector() {
        cursor = 0;
        sizeOfVector = 2;
        p = (int *) malloc(2 * sizeof(int));
    }

    void push_back(int a) {
        if (sizeOfVector == cursor) {
            resize_vector(sizeOfVector * 2);
        }
        p[cursor] = a;
        cursor++;
    }

    void pop_back() {
        if (sizeOfVector > 2 * cursor) {
            resize_vector(cursor);
        }
        cursor--;
    }

    int size() {
        return cursor;
    }

    int get(int i) {
        return p[i];
    }

    bool empty() {
        return (cursor == 0);
    }

    void clear() {
        cursor = 0;
        resize_vector(2);
    }

private:
    int *p = (int *) malloc(2 * sizeof(int));
    int cursor = 0;
    int sizeOfVector = 2;

    void resize_vector(int s) {
        int *p1 = (int *) malloc(s * sizeof(int));
        sizeOfVector = s;
        for (int i = 0; i < cursor; i++) {
            p1[i] = p[i];
        }
        p = p1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    MyVector vector1;
    for (int i = 0; i < n; i++) {
        char sign;
        cin >> sign;
        if (sign == '+') {
            int a;
            cin >> a;
            vector1.push_back(a);
        } else {
            cout << vector1.get(vector1.size() - 1) << endl;
            vector1.pop_back();
        }
    }
    return 0;
}