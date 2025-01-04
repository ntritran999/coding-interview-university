#include <iostream>

using namespace std;

class Array
{
    int size, capacity;
    int *data;

    void resize(int);
public:
    Array();
    Array(int);
    ~Array();
    int size_();
    int capacity_();
    bool is_empty();
    int at(int);
    void push(int);
    void insert(int, int);
    void prepend(int);
    int pop();
    void delete_(int);
    void remove(int);
    int find(int);
};

Array::Array() {
    this->size = 0;
    this->capacity = 16;
    this->data = new int[this->capacity];
}

Array::Array(int n) : Array(){
    int new_capacity = 16;
    while(n >= new_capacity)
        new_capacity *= 2;

    resize(new_capacity);
    size = n;
    for (int i = 0; i < size; i++)
        *(data + i) = 0;
}

Array::~Array() {
    delete[] data;
    data = nullptr;
    size = capacity = 0;
}

void Array::resize(int new_capacity) {
    int *tmp = data;
    capacity = new_capacity;
    data = new int[capacity];
    for (int i = 0; i < capacity; i++)
        *(data + i) = *(tmp + i);

    delete[] tmp;
}

int Array::size_() {
    return size;
}

int Array::capacity_() {
    return capacity;
}

bool Array::is_empty() {
    return size == 0;
}

int Array::at(int index) {
    if (index >= size || index < 0) {
        cout << "Error: Index out of bound!\n";
        exit(1);
    }

    return *(data + index);
}

void Array::push(int item) {
    if (size == capacity)
        resize(capacity * 2);

    *(data + size++) = item;
}

void Array::insert(int index, int item) {
    if (index < 0) {
        cout << "Error: Index out of bound!\n";
        exit(1);
    }

    if (index >= size)
        push(item);

    size++;
    if (size == capacity)
        resize(capacity * 2);

    for (int i = size - 1; i > index; i--)
        *(data + i) = *(data + i - 1);

    *(data + index) = item;
}

void Array::prepend(int item) {
    insert(0, item);
}

int Array::pop() {
    if (is_empty()) {
        cout << "Error: Empty array!\n";
        exit(2);
    }

    int res = *(data + (size - 1));
    size--;
    if (size == capacity / 4)
        resize(capacity / 2);
    return res;
}

void Array::delete_(int index) {
    if (index < 0 || index >= size) {
        cout << "Error: Index out of bound!\n";
        exit(1);
    }

    for (int i = index; i < size; i++)
        *(data + i) = *(data + i + 1);

    size--;
    if (size == capacity / 4)
        resize(capacity / 2);
}

void Array::remove(int item) {
    for (int i = 0; i < this->size; i++)
        if (*(data + i) == item) {
            delete_(i);
            i--;
        }
}

int Array::find(int item) {
    for (int i = 0; i < size; i++)
        if (*(data + i) == item)
            return i;

    return -1;
}

void printArr(Array& a) {
    for (int i = 0; i < a.size_(); i++)
        cout << a.at(i) << " ";
    cout << "\n";
}

int main() {
    Array a, b(100);
    cout << "a size: " << a.size_() << ",b size: " << b.size_() << "\n";
    cout << "a capacity: " << a.capacity_() << ",b capacity: " << b.capacity_() << "\n";
    cout << "Is a empty: " << (a.is_empty() ? "yes" : "no") << "\n";
    cout << "Is b empty: " << (b.is_empty() ? "yes" : "no") << "\n";
    cout << b.at(0) << "\n";
    cout << "\n";
    
    for (int i = 0; i < 10; i++)
        a.push(i);
    a.insert(1, 100);
    a.pop();
    a.delete_(6);
    cout << "Array a after: ";
    printArr(a);
    cout << "\n";

    for (int i = 0; i < 5; i++) {
        a.delete_(i);
        a.insert(i, 1);
    }
    a.remove(1);
    cout << "Array a after: ";
    printArr(a);

    cout << ((a.find(7) != -1) ? "7 found!" : "7 not found.") << "\n";
    
    return 0;
}