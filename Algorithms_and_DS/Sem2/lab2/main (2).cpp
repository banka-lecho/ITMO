#include <iostream>
#include <vector>

using namespace std;

struct element {
    int key;
    int height;  // здесь хранится высота поддерева
    element *parent;
    element *leftChild;
    element *rightChild;
};

element *start;
element *forRestore = nullptr;
bool needToRestore = true;

element *find_min(element *element1) {  // Указатель на минимальный элемент (ok)
    if (element1->leftChild != nullptr) {
        return find_min(element1->leftChild);
    } else {
        return element1;
    }
}

void countHeight(element *element1) {  // OK
    int right, left;
    if (element1->rightChild == nullptr) {
        right = 0;
    } else {
        right = element1->rightChild->height;
    }
    if (element1->leftChild == nullptr) {
        left = 0;
    } else {
        left = element1->leftChild->height;
    }
    element1->height = max(left, right) + 1;
}

int diff(element *element1) {
    int left, right;
    if (element1->leftChild == nullptr) {
        left = 0;
    } else {
        left = element1->leftChild->height;
    }
    if (element1->rightChild == nullptr) {
        right = 0;
    } else {
        right = element1->rightChild->height;
    }
    return left - right;
}

void rotateLeft(element *a) {  // справа не может быть пустого дерева, так как вызов при diff = -2
    // OK
    element *b = a->rightChild;
    if (b->leftChild == nullptr) {
        a->rightChild = nullptr;
    } else {
        a->rightChild = b->leftChild;
    }
    if (a->rightChild != nullptr) {
        a->rightChild->parent = a;
    }
    if (start == a) {
        b->parent = nullptr;
        start = b;
    } else {
        b->parent = a->parent;
        if (a->parent->rightChild == a) {
            a->parent->rightChild = b;
        } else {
            a->parent->leftChild = b;
        }
    }
    a->parent = b;
    b->leftChild = a;
    countHeight(a);
    countHeight(b);
}

void rotateRight(element *a) {  // OK
    element *b = a->leftChild;
    if (b->rightChild == nullptr) {
        a->leftChild = nullptr;
    } else {
        a->leftChild = b->rightChild;
        a->leftChild->parent = a;
    }
    if (start == a) {
        b->parent = nullptr;
        start = b;
    } else {
        b->parent = a->parent;
        if (a->parent->rightChild == a) {
            a->parent->rightChild = b;
        } else {
            a->parent->leftChild = b;
        }
    }
    a->parent = b;
    b->rightChild = a;
    countHeight(a);
    countHeight(b);
}

void bigRotateLeft(element *a) {  // OK
    rotateRight(a->rightChild);
    rotateLeft(a);
}

void bigRotateRight(element *a) {  // OK
    rotateLeft(a->leftChild);
    rotateRight(a);
}

void restore(element *x) {
    if (x == nullptr) {
        return;
    }
    countHeight(x);
    int diff_a = diff(x);
    if (diff_a == -2) {  // OK
        element *b = x->rightChild;
        int diff_b = diff(b);
        if (diff_b == -1 || diff_b == 0) {
            rotateLeft(x);
            restore(b);
            return;
        } else {
            element *c = x->rightChild->leftChild;
            bigRotateLeft(x);
            restore(c);
            return;
        }
    } else if (diff_a == 2) {
        element *b = x->leftChild;
        int diff_b = diff(b);
        if (diff_b == 1 || diff_b == 0) {
            rotateRight(x);
            restore(b);
            return;
        } else {
            element *c = x->leftChild->rightChild;
            bigRotateRight(x);
            restore(c);
            return;
        }
    }
    restore(x->parent);
}

void insert(element *x, element *element1) {  // ????
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
        restore(element1);
        return;
    } else if (element1->key < x->key) {
        if (element1->rightChild != nullptr) {
            insert(x, element1->rightChild);
            return;
        }
        x->parent = element1;
        element1->rightChild = x;
        restore(element1);
        return;
    }
}

void delete_element(int x, element *element1) {  // TODO
    if (!needToRestore) {
        forRestore = element1;
    }
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
    // если это лист (OK)
    if (element1->rightChild == nullptr && element1->leftChild == nullptr) {
        if (element1->parent != nullptr) {
            if (element1->parent->rightChild == element1) {
                element1->parent->rightChild = nullptr;
            } else {
                element1->parent->leftChild = nullptr;
            }
            if (needToRestore) {
                restore(element1->parent);
            }
        } else {
            start = nullptr;
        }
        return;
    }
    // У вершины есть только левое поддерево (OK)
    if (element1->rightChild == nullptr) {
        if (element1->parent != nullptr) {
            element1->leftChild->parent = element1->parent;
            element *a = element1->leftChild;
            if (element1->parent->rightChild == element1) {
                element1->parent->rightChild = a;
            } else {
                element1->parent->leftChild = a;
            }
            if (needToRestore) {
                restore(a->parent);
            }
            return;
        }
        element1->leftChild->parent = nullptr;
        start = element1->leftChild;
        return;
    }
    // У вершинки element1 есть только правое поддерево (OK)
    if (element1->leftChild == nullptr) {
        if (element1->parent != nullptr) {
            element1->rightChild->parent = element1->parent;
            element *a = element1->rightChild;
            if (element1->parent->rightChild == element1) {
                element1->parent->rightChild = a;
            } else {
                element1->parent->leftChild = a;
            }
            if (needToRestore) {
                restore(a->parent);
            }
            return;
        }
        element1->rightChild->parent = nullptr;
        start = element1->rightChild;
        return;
    }
    element *a = find_min(element1->rightChild);
    needToRestore = false;
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
    needToRestore = true;
    restore(forRestore);
}

bool exists(int x, element *element1) {  // OK
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

element *next(int x, element *element1) {  // OK
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

element *prev(int x, element *element1) {  // OK
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

void inorderTraversal(element *element1) {  // DEBUG
    if (element1 != nullptr) {
        inorderTraversal(element1->leftChild);
        cout << "key: " << element1->key << "; leftChild: ";
        if (element1->leftChild != nullptr) {
            cout << element1->leftChild->key << "; rightChild: ";
        } else {
            cout << "nullptr; rightChild: ";
        }
        if (element1->rightChild != nullptr) {
            cout << element1->rightChild->key << "; parent: ";
        } else {
            cout << "nullptr; parent: ";
        }
        if (element1->parent != nullptr) {
            cout << element1->parent->key << "; ";
        } else {
            cout << "nullptr; ";
        }
        cout << "height: " << element1->height << endl;
        inorderTraversal(element1->rightChild);
    }
}

int main() {
    string s;
    start = nullptr;
    forRestore = nullptr;
    while (cin >> s) {
        int x;
        cin >> x;
        if (s == "insert") {
            element *element1 = new element;
            element1->key = x;
            element1->parent = nullptr;
            element1->leftChild = nullptr;
            element1->rightChild = nullptr;
            element1->height = 1;
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
