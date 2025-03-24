//
// Created by Анастасия Шпилёва on 24.11.2022.
//

#include <iostream>
#include <stdlib.h>
#include <assert.h>

using namespace std;

struct Element {
    int data;
    struct Element *next;
    struct Element *prev;
};

class MyLinkedList {
public:
    int size = 0;
    struct Element *last{};  // указывает на последний элемент в списке
    struct Element *first{};  // указывает на первый элемент

    void push_back(int a) {
        struct Element *t = (struct Element *) malloc(sizeof(struct Element));
        t->data = a;
        t->prev = last;
        t->next = NULL;
        if (isEmpty()) {
            first = t;
        } else {
            last->next = t;
        }
        if (size == 1) {
            first->next = t;
        }
        last = t;
        size++;
    }

    int pop() {
        struct Element *t = NULL;
        int a;
        t = last;
        a = t->data;
        last = last->prev;
        free(t);
        size--;
        return a;
    }

    int pop_front() {
        struct Element *t = NULL;
        int a;
        t = first;
        a = t->data;
        first = first->next;
        if (first != NULL) {
            first->prev = NULL;
        }
        free(t);
        size--;
        return a;
    }

    bool isEmpty() {
        return size == 0;
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
            cout << linkedList.pop_front() << endl;
        }
    }
    return 0;
}