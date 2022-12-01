#include <iostream>
#include <vector>

using namespace std;

template<class T>
class Circular_Buffer {
private:
    int capacity;
    T *cir_buf;
    int head = 0;
    int tail = 0;
public:
    class Iterator : public iterator<random_access_iterator_tag, T> {
    private:
        T *cb;
    public:
        Iterator() : cb(nullptr) {}

        explicit Iterator(T *cb) : cb(cb) {}

        Iterator operator++() {
            cb++;
            return *this;
        }

        Iterator operator++(T) {
            Iterator tmp(*this);
            ++cb;
            return tmp;
        }

        Iterator operator--() {
            cb--;
            return *this;
        }

        Iterator operator--(T) {
            Iterator tmp(*this);
            --cb;
            return tmp;
        }

        Iterator operator+(int num) {
            return Iterator(cb + num);
        }

        Iterator operator+=(T x) {
            cb += x;
            return *this;
        }

        T operator-(const Iterator &smth) {
            return (cb - smth.cb);
        }

        Iterator operator-(int num) {
            return Iterator(cb - num);
        }

        Iterator operator-=(T num) {
            cb -= num;
            return *this;
        }

        T &operator*() const {
            return *cb;
        }

        T operator->() const {
            return cb;
        }

        T operator[](const int num) {
            return cb[num];
        }

        bool operator==(const Iterator &num) const {
            return num.cb == this->cb;
        }

        bool operator!=(const Iterator &num) const {
            return num.cb != this->cb;
        }

        bool operator>(const Iterator &num) const {
            return num.cb > this->cb;
        }

        bool operator>=(const Iterator &num) const {
            return num.cb >= this->cb;
        }

        bool operator<(const Iterator &num) const {
            return num.cb < this->cb;
        }

        bool operator<=(const Iterator &num) const {
            return num.cb <= this->cb;
        }
    };

    Circular_Buffer() {};

    Circular_Buffer(int capa) : capacity(capa) {
        head = 0;
        tail = 0;
        cir_buf = new T[capacity];
    }

    Iterator begin() const {
        return Iterator(cir_buf + head);
    }

    Iterator end() const {
        return Iterator(cir_buf + tail);
    }

    T operator[](int i) {
        return cir_buf[i % capacity];
    }

    void push_front(const T &num) {
        for (int i = tail; i >= head; i--) {
            cir_buf[i + 1] = cir_buf[i];
        }
        cir_buf[head] = num;
        tail++;
    }

    void push_back(const T &num) {
        if (tail == capacity) {
            tail--;
        }
        cir_buf[tail] = num;
        if (tail != capacity + 1) {
            tail++;
        }
    }

    void pop_front() {
        cir_buf[head] = 0;
        head++;
    }

    void pop_back() {
        cir_buf[tail] = 0;
        tail--;
    }

    void resize(const int &n) {
        T *tmp = new T[n];
        for (int i = 0; i < n; i++) {
            tmp[i] = cir_buf[i];
        }
        delete[] cir_buf;
        cir_buf = tmp;
        capacity = n;
    }

    void print_buffer() {
        for (Iterator iter = begin(); iter != end(); iter++) {
            cout << " " << *iter << " ";
        }
        cout << endl;
    }

    ~Circular_Buffer() {
        delete[] cir_buf;
    }
};

int main() {
    Circular_Buffer<int> buffer(3);
    buffer.push_front(6);
    buffer.push_front(7);
    buffer.push_front(8);

    buffer.print_buffer();

    cout << buffer[4]; // доступ по индексу
    buffer.pop_back(); // удаление конца
    buffer.pop_front(); // удаление начала

    buffer.resize(5); // изменение капасити
    buffer.push_back(5);
    buffer.push_back(10);

    buffer.print_buffer();

    sort(buffer.begin(), buffer.end());
    buffer.print_buffer();
    return 0;
}