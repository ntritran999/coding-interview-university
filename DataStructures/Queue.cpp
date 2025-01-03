#include <iostream>

using namespace std;

struct Node
{
    int value;
    Node *next;
};

Node *createNode(int v) {
    Node *p = new Node;
    p->value = v;
    p->next = nullptr;
    return p;
}

class ListQueue
{
    Node *head, *tail;
public:
    ListQueue();
    ~ListQueue();
    void enqueue(int);
    int dequeue();
    bool empty();
    void showQueue();
};

ListQueue::ListQueue() {
    head = tail = nullptr;
}

ListQueue::~ListQueue() {
    while (head)
        dequeue();
}

void ListQueue::enqueue(int item) {
    if (head == nullptr) {
        head = tail = createNode(item);
        return;
    }

    tail->next = createNode(item);
    tail = tail->next;
}

int ListQueue::dequeue() {
    if (head == nullptr) {
        cout << "Error: Queue empty!\n";
        exit(1);
    }

    Node *p = head;
    int val = p->value;
    head = head->next;
    delete p;

    if (head == nullptr)
        tail = head;
    return val;
}

bool ListQueue::empty() {
    return head == nullptr;
}

void ListQueue::showQueue() {
    Node *p = head;
    while (p) {
        cout << p->value << " ";
        p = p->next;
    }
    cout << "\n";
}

const int SIZE = 11;
class ArrayQueue
{
    int array[SIZE];
    int start, end;
public:
    ArrayQueue();
    void enqueue(int);
    int dequeue();
    bool empty();
    bool full();
    void showQueue();
};

ArrayQueue::ArrayQueue() {
    start = end = 0;
}

void ArrayQueue::enqueue(int item) {
    if (full()) {
        cout << "Error: Queue full!\n";
        return;
    }

    array[end] = item;
    end = (end + 1) % SIZE;
}

int ArrayQueue::dequeue() {
    if (empty()) {
        cout << "Error: Queue empty!\n";
        exit(1);
    }

    int val = array[start];
    start = (start + 1) % SIZE;
    return val;
}

bool ArrayQueue::empty() {
    return start == end;
}

bool ArrayQueue::full() {
    return (end + 1) % SIZE == start;
}

void ArrayQueue::showQueue() {
    int i = start;
    while (i != end) {
        cout << array[i] << " ";
        i = (i + 1) % SIZE;
    }
    cout << "\n";
}

int main() {
    ListQueue lq;
    for (int i = 1; i <= 10; i++)
        lq.enqueue(i);
    lq.dequeue();
    cout << "Is queue empty: " << ((lq.empty()) ? "Yes" : "No") << endl;
    lq.showQueue();
    cout << "\n";

    ArrayQueue aq;
    for (int i = 1; i < SIZE; i++)
        aq.enqueue(i);
    cout << "Is queue full: " << ((aq.full()) ? "Yes" : "No") << endl;
    aq.dequeue();
    aq.showQueue();
    return 0;
}