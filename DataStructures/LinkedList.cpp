#include <iostream>

using namespace std;

struct Node 
{
    int value;
    Node *next;
};

Node* createNode(int v) {
    Node *p = new Node;
    p->value = v;
    p->next = nullptr;

    return p;
}

class LinkedList
{
    Node *head;
    int size;
public:
    LinkedList();
    ~LinkedList();
    int size_();
    bool empty();
    int value_at(int);
    void push_front(int);
    void push_back(int);
    void pop_front();
    void pop_back();
    int front();
    int back();
    void insert(int, int);
    void erase(int);
    int value_n_from_end(int);
    LinkedList* reverse();
    void remove_value(int);
    void printList();
};

LinkedList::LinkedList() {
    size = 0;
    head = nullptr;
}

LinkedList::~LinkedList() {
    while (size > 0)
        pop_front();
}

int LinkedList::size_() {
    return size;
}

bool LinkedList::empty() {
    return size == 0;
}

int LinkedList::value_at(int index) {
    if (index < 0 || index >= size) {
        cout << "Error: Index out of bound.\n";
        exit(1);
    }

    Node *p = head;
    for (int i = 1; i <= index; i++)
        p = p->next;

    return p->value;
}

void LinkedList::push_front(int item) {
    Node *p = createNode(item);
    if (head != nullptr)
        p->next = head;
    head = p;
    size++;
}

void LinkedList::push_back(int item) {
    if (head == nullptr) {
        head = createNode(item);
        return;
    }
    Node *p = head;
    while (p->next)
        p = p->next;
    p->next = createNode(item);
    size++;
}

void LinkedList::pop_front() {
    if (empty()) {
        cout << "Error: List empty!\n";
        return;
    }

    Node *p = head;
    head = head->next;
    delete p;
    size--;
}

void LinkedList::pop_back() {
    if (empty()) {
        cout << "Error: List empty!\n";
        return;
    }

    Node *cur = head;
    Node *prev = nullptr;
    while (cur->next) {
        prev = cur;
        cur = cur->next;
    }
    delete cur;
    if (prev)
        prev->next = nullptr;
    else 
        head = nullptr;
    size--;
}

int LinkedList::front() {
    if (empty()) {
        cout << "Error: List empty!\n";
        exit(2);
    }

    return head->value;
}

int LinkedList::back() {
    if (empty()) {
        cout << "Error: List empty!\n";
        exit(2);
    }

    Node *p = head;
    while (p->next)
        p = p->next;

    return p->value;
}

void LinkedList::insert(int index, int item) {
    if (index < 0 || index >= size) {
        cout << "Error: Index out of bound!\n";
        return;
    }

    if (index == 0) {
        push_front(item);
        return;
    }
    
    Node *p = head;
    for (int i = 1; i <= index; i++)
        p = p->next;
    Node *q = createNode(item);
    *q = *p;
    p->value = item;
    p->next = q;
    size++;
}

void LinkedList::erase(int index) {
    if (index < 0 || index >= size) {
        cout << "Error: Index out of bound!\n";
        return;
    }
    if (index == 0) {
        pop_front();
        return;
    }
    
    Node *p = head;
    for (int i = 1; i <= index; i++)
        p = p->next;

    Node *q = p->next;
    *p = *q;
    delete q;
    size--;
}

int LinkedList::value_n_from_end(int n) {
    if (n < 0 || n >= size) {
        cout << "Error: Index out of bound!\n";
        exit(1);
    }
    return value_at(size - 1 - n);
}

LinkedList* LinkedList::reverse() {
    LinkedList* l = new LinkedList();
    Node *p = head;
    while (p) {
        l->push_front(p->value);
        p = p->next;
    }
    return l;
}

void LinkedList::remove_value(int item) {
    if (empty()) {
        cout << "Error: List empty!\n";
        return;
    }
    
    Node *p = head;
    for (int i = 0; i < size; i++) {
        if (p->value == item) {
            erase(i);
            return;
        }
        p = p->next;
    }
}

void LinkedList::printList() {
    Node *p = head;
    while (p) {
        cout << p->value << " ";
        p = p->next;
    }
    cout << "\n";
}

class TailedLinkedList
{
    Node *head;
    Node *tail;
    int size;
public:
    TailedLinkedList();
    ~TailedLinkedList();
    int size_();
    bool empty();
    int value_at(int);
    void push_front(int);
    void push_back(int);
    void pop_front();
    void pop_back();
    int front();
    int back();
    void insert(int, int);
    void erase(int);
    int value_n_from_end(int);
    TailedLinkedList* reverse();
    void remove_value(int);
    void printList();
};

TailedLinkedList::TailedLinkedList() {
    head = tail = nullptr;
    size = 0;
}

TailedLinkedList::~TailedLinkedList() {
    while (size > 0)
        pop_front();
}

int TailedLinkedList::size_() {
    return size;
}

bool TailedLinkedList::empty() {
    return size == 0;
}

int TailedLinkedList::value_at(int index) {
    if (index < 0 || index >= size) {
        cout << "Error: Index out of bound.\n";
        exit(1);
    }

    Node *p = head;
    for (int i = 1; i <= index; i++)
        p = p->next;

    return p->value;
}

void TailedLinkedList::push_front(int item) {
    Node *p = createNode(item);
    if (head != nullptr)
        p->next = head;
    else 
        tail = p;
    head = p;
    size++;
}

void TailedLinkedList::push_back(int item) {
    if (head == nullptr) {
        head = tail = createNode(item);
        return;
    }
    Node *p = head;
    while (p->next)
        p = p->next;
    p->next = createNode(item);
    tail = p->next;
    size++;
}

void TailedLinkedList::pop_front() {
    if (empty()) {
        cout << "Error: List empty!\n";
        return;
    }

    Node *p = head;
    head = head->next;
    delete p;
    size--;

    if (head == nullptr)
        tail = nullptr;
}

void TailedLinkedList::pop_back() {
    if (empty()) {
        cout << "Error: List empty!\n";
        return;
    }

    Node *cur = head;
    Node *prev = nullptr;
    while (cur->next) {
        prev = cur;
        cur = cur->next;
    }
    delete cur;
    if (prev) {
        prev->next = nullptr;
        tail = prev;
    }
    else 
        head = tail = nullptr;
    size--;
}

int TailedLinkedList::front() {
    if (empty()) {
        cout << "Error: List empty!\n";
        exit(2);
    }

    return head->value;
}

int TailedLinkedList::back() {
    if (empty()) {
        cout << "Error: List empty!\n";
        exit(2);
    }

    return tail->value;
}

void TailedLinkedList::insert(int index, int item) {
    if (index < 0 || index >= size) {
        cout << "Error: Index out of bound!\n";
        return;
    }

    if (index == 0) {
        push_front(item);
        return;
    }
    
    Node *p = head;
    for (int i = 1; i <= index; i++)
        p = p->next;
    Node *q = createNode(item);
    *q = *p;
    p->value = item;
    p->next = q;
    size++;
}

void TailedLinkedList::erase(int index) {
    if (index < 0 || index >= size) {
        cout << "Error: Index out of bound!\n";
        return;
    }
    if (index == 0) {
        pop_front();
        return;
    }
    else if (index == size - 1) {
        pop_back();
        return;
    }
    
    Node *p = head;
    for (int i = 1; i <= index; i++)
        p = p->next;

    Node *q = p->next;
    *p = *q;
    if (q->next == nullptr)
        tail = p;
    delete q;
    size--;
}

int TailedLinkedList::value_n_from_end(int n) {
    if (n < 0 || n >= size) {
        cout << "Error: Index out of bound!\n";
        exit(1);
    }
    return value_at(size - 1 - n);
}

TailedLinkedList* TailedLinkedList::reverse() {
    TailedLinkedList* l = new TailedLinkedList();
    Node *p = head;
    while (p) {
        l->push_front(p->value);
        p = p->next;
    }
    return l;
}

void TailedLinkedList::remove_value(int item) {
    if (empty()) {
        cout << "Error: List empty!\n";
        return;
    }
    
    Node *p = head;
    for (int i = 0; i < size; i++) {
        if (p->value == item) {
            erase(i);
            return;
        }
        p = p->next;
    }
}

void TailedLinkedList::printList() {
    Node *p = head;
    while (p) {
        cout << p->value << " ";
        p = p->next;
    }
    cout << "\n";
}

int main() {
    LinkedList list;
    cout << "Is list empty: " << ((list.empty()) ? "Yes" : "No") << "\n";
    for (int i = 10; i > 0; i--)
        list.push_front(i);
    cout << "list front: " << list.front() << ", list back: " << list.back() << "\n";
    list.push_back(11);
    list.push_back(12);
    list.pop_front();
    list.pop_back();
    list.insert(5, 100);
    list.erase(8);
    list.remove_value(3);
    cout << "List size: " << list.size_() << "\n";
    list.printList();
    cout << "Value at 5th position, starting from end: " << list.value_n_from_end(5) << "\n";

    LinkedList *tmp = list.reverse();
    tmp->printList();
    delete tmp;
    cout << "\n\n";

    TailedLinkedList list1;
    cout << "Is list empty: " << ((list1.empty()) ? "Yes" : "No") << "\n";
    for (int i = 10; i > 0; i--)
        list1.push_front(i);
    cout << "list front: " << list1.front() << ", list back: " << list1.back() << "\n";
    list1.push_back(11);
    list1.push_back(12);
    list1.pop_front();
    list1.pop_back();
    list1.insert(5, 100);
    list1.erase(8);
    list1.remove_value(3);
    cout << "List size: " << list1.size_() << "\n";
    list1.printList();
    cout << "Value at 5th position, starting from end: " << list1.value_n_from_end(5) << "\n";

    TailedLinkedList *tmp1 = list1.reverse();
    tmp1->printList();
    delete tmp1;
    return 0;
}