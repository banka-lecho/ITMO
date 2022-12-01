//
// Created by Анастасия Шпилёва on 24.11.2022.
//

#include <iostream>
#include <stdlib.h>

using namespace std;

struct Element {
    int data;
    struct Element *cursor;
};

class MyLinkedList {
public:
    int size = 0;
    struct Element *last{};  // указывает на последний элемент в списке

    void push_back(int a) {
        struct Element *t = (struct Element *) malloc(sizeof(struct Element));
        t->data = a;
        t->cursor = last;
        last = t;
        size++;
    }

    void pop() {
        struct Element *t = NULL;
        t = last;
        last = last->cursor;
        free(t);
        size--;
    }

    int back() {
        return last->data;
    }

    bool isEmpty() {
        return size == 0;
    }

    void clear() {
        size = 0;
        while (last != NULL) {
            struct Element *t = last;
            last = last->cursor;
            free(t);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    MyLinkedList linkedList;
    char x;
    while (cin >> x) {
        if ((x >= '0') && (x <= '9')) {
            linkedList.push_back(x - '0');
        } else {
            int a = linkedList.back();
            linkedList.pop();
            int b = linkedList.back();
            linkedList.pop();
            if (x == '-') {
                linkedList.push_back(b - a);
            } else if (x == '+') {
                linkedList.push_back(a + b);
            } else if (x == '*') {
                linkedList.push_back(a * b);
            }
        }
    }
    cout << linkedList.back();
    return 0;
}