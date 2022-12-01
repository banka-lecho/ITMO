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

    int pop() {
        struct Element *t = NULL;
        int a;
        t = last;
        a = t->data;
        last = last->cursor;
        free(t);
        size--;
        return a;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    MyLinkedList linkedList;
    for (int i = 0; i < n; i++) {
        char sign;
        cin >> sign;
        if (sign == '+') {
            int a;
            cin >> a;
            linkedList.push_back(a);
        } else {
            cout << linkedList.pop() << endl;
        }
    }
    return 0;
}