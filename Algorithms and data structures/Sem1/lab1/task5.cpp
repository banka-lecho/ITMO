//
// Created by Анастасия Шпилёва on 24.11.2022.
//

#include <iostream>
#include <stdlib.h>

using namespace std;

struct Element {
    char data;
    struct Element *cursor;
};

class MyLinkedList {
public:
    int size = 0;
    struct Element *last{};  // указывает на последний элемент в списке

    void push_back(char a) {
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

    char back() {
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
    string str;
    while (cin >> str) {
        for (unsigned int i = 0; i < str.size(); i++) {
            char x = str[i];
            if (!linkedList.isEmpty()) {
                if (x == ']') {
                    if (linkedList.back() == '[') {
                        linkedList.pop();
                    } else {
                        linkedList.push_back(']');
                    }
                } else if (x == '[') {
                    linkedList.push_back('[');
                } else if (x == '(') {
                    linkedList.push_back('(');
                } else {
                    if (linkedList.back() == '(') {
                        linkedList.pop();
                    } else {
                        linkedList.push_back(')');
                    }
                }
            } else {
                linkedList.push_back(x);
            }
        }
        if (linkedList.isEmpty()) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
            linkedList.clear();
        }
    }
    return 0;
}