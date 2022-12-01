#include <iostream>
#include <vector>

using namespace std;

struct element {
    int key;
    element *parent;
    element *leftChild;
    element *rightChild;
};

element *start;

element *find_min(element *element1) {  // Указатель на минимальный элемент
    if (element1->leftChild != nullptr) {
        return find_min(element1->leftChild);
    } else {
        return element1;
    }
}

void insert(element *x, element *element1) {
    if (start == nullptr) {
        start = x;
        return;
    }
    if (element1->key > x->key) {
        if (element1->leftChild != nullptr) {
            insert(x, element1->leftChild);
            return;
        }
        x->parent = element1;
        element1->leftChild = x;
        return;
    } else if (element1->key < x->key) {
        if (element1->rightChild != nullptr) {
            insert(x, element1->rightChild);
            return;
        }
        x->parent = element1;
        element1->rightChild = x;
        return;
    }
}

void delete_element(int x, element *element1) {
    if (element1 == nullptr) {
        return;
    }
    if (element1->key > x) {
        delete_element(x, element1->leftChild);
        return;
    }
    if (element1->key < x) {
        delete_element(x, element1->rightChild);
        return;
    }
    // если это лист (ok)
    if (element1->rightChild == nullptr && element1->leftChild == nullptr) {
        if (element1->parent != nullptr) {
            if (element1->parent->rightChild == element1) {
                element1->parent->rightChild = nullptr;
            } else {
                element1->parent->leftChild = nullptr;
            }
        } else {
            start = nullptr;
        }
        return;
    }
    // У вершины есть только левое поддерево (ok)
    if (element1->rightChild == nullptr) {
        if (element1->parent != nullptr) {
            element1->leftChild->parent = element1->parent;
            if (element1->parent->rightChild == element1) {
                element1->parent->rightChild = element1->leftChild;
            } else {
                element1->parent->leftChild = element1->leftChild;
            }
            return;
        }
        element1->leftChild->parent = nullptr;
        start = element1->leftChild;
        return;
    }
    // У вершинки а есть только правое поддерево (ok)
    if (element1->leftChild == nullptr) {
        if (element1->parent != nullptr) {
            element1->rightChild->parent = element1->parent;
            if (element1->parent->rightChild == element1) {
                element1->parent->rightChild = element1->rightChild;
            } else {
                element1->parent->leftChild = element1->rightChild;
            }
            return;
        }
        element1->rightChild->parent = nullptr;
        start = element1->rightChild;
        return;
    }
    // Если у вершины есть оба поддерева
    element *a = find_min(element1->rightChild);
    // Разбираю вариант, когда а НЕ является листом
    if (a->rightChild != nullptr) {
        delete_element(a->key, a);
        a->parent = element1->parent;
        a->leftChild = element1->leftChild;
        a->rightChild = element1->rightChild;
        if (a->parent == nullptr) {
            start = a;
        } else {
            if (element1->parent->rightChild == element1) {
                element1->parent->rightChild = a;
            } else {
                element1->parent->leftChild = a;
            }
        }
        element1->leftChild->parent = a;
        element1->rightChild->parent = a;
        return;
    }
    // А - лист
    if (a->parent->rightChild == a) {
        a->parent->rightChild = nullptr;
    } else {
        a->parent->leftChild = nullptr;
    }
    a->leftChild = element1->leftChild;
    element1->leftChild->parent = a;
    if (element1->rightChild != nullptr) {
        a->rightChild = element1->rightChild;
        a->rightChild->parent = a;
    }
    if (element1->parent != nullptr) {
        if (element1->parent->rightChild == element1) {
            element1->parent->rightChild = a;
        } else {
            element1->parent->leftChild = a;
        }
        a->parent = element1->parent;
        return;
    }
    a->parent = nullptr;
    start = a;
}

bool exists(int x, element *element1) {
    if (start == nullptr) {
        return false;
    }
    if (x == element1->key) {
        return true;
    }
    if (element1->key > x) {
        if (element1->leftChild != nullptr) {
            return exists(x, element1->leftChild);
        }
        return false;
    }
    if (element1->rightChild != nullptr) {
        return exists(x, element1->rightChild);
    }
    return false;
}

element *next(int x, element *element1) {
    if (start == nullptr || element1 == nullptr) {
        return nullptr;
    }
    if (element1->key > x) {
        element *q = next(x, element1->leftChild);
        if (q == nullptr) {
            return element1;
        }
        return q;
    }
    element *q = next(x, element1->rightChild);
    return q;
}

element *prev(int x, element *element1) {
    if (start == nullptr || element1 == nullptr) {
        return nullptr;
    }
    if (element1->key < x) {
        element *q = prev(x, element1->rightChild);
        if (q == nullptr) {
            return element1;
        }
        return q;
    }
    element *q = prev(x, element1->leftChild);
    return q;
}

int main() {
    string s;
    start = nullptr;
    while (cin >> s) {
        int x;
        cin >> x;
        if (s == "insert") {
            element *element1 = new element;
            element1->key = x;
            element1->parent = nullptr;
            element1->leftChild = nullptr;
            element1->rightChild = nullptr;
            insert(element1, start);
        } else if (s == "delete") {
            delete_element(x, start);
        } else if (s == "exists") {
            if (exists(x, start)) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        } else if (s == "next") {
            element *q = next(x, start);
            if (q == nullptr) {
                cout << "none\n";
            } else {
                cout << q->key << "\n";
            }
        } else {  // prev
            element *q = prev(x, start);
            if (q == nullptr) {
                cout << "none\n";
            } else {
                cout << q->key << "\n";
            }
        }
    }
    return 0;
}
