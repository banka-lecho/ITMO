//
// Created by Анастасия Шпилёва on 24.11.2022.
//

#include <iostream>
#include <stdlib.h>

using namespace std;

class MyVector {
public:
    int cursor = 0;
    int sizeOfVector = 1;
    int *p = (int *) malloc(1 * sizeof(int));

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
        resize_vector(1);
    }

    void resize_vector(int s) {
        int *p1 = (int *) malloc(s * sizeof(int));
        sizeOfVector = s;
        for (int i = 0; i < cursor; i++) {
            p1[i] = p[i];
        }
        p = p1;
    }
};

class MyQueue {
public:
    void push_back(int a) {
        vector1.push_back(a);
    }

    void pop() {
        cursor++;
        if ((vector1.sizeOfVector > 2 * (vector1.cursor - cursor)) && !empty()) {
            resizeMyQueue();
        }
    }

    int size() {
        return vector1.cursor - cursor;
    }

    int back() {
        return vector1.get(vector1.size() - 1);
    }

    int front() {
        return vector1.get(cursor);
    }

    bool empty() {
        return (vector1.cursor - cursor == 0);
    }

private:
    MyVector vector1;
    int cursor = 0;

    void resizeMyQueue() {
        int *p1 = (int *) malloc(vector1.sizeOfVector / 2 * sizeof(int));
        for (int i = 0; i < vector1.cursor - cursor; i++) {
            p1[i] = vector1.p[i + cursor];
        }
        vector1.p = p1;
        vector1.cursor -= cursor;
        cursor = 0;
        vector1.sizeOfVector /= 2;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    MyQueue queue;
    for (int i = 0; i < n; i++) {
        char sign;
        cin >> sign;
        if (sign == '+') {
            int a;
            cin >> a;
            queue.push_back(a);
        } else {
            cout << queue.front() << endl;
            queue.pop();
        }
    }
    return 0;
}