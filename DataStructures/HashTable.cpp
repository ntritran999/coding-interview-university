#include <iostream>
#include <string>

using namespace std;

enum State
{
    ALIVE,
    DEAD,
    NONE,
};

struct Entry
{
    int key, value;
    State state;
};

class HashTable
{
    Entry *entries;
    int size, capacity;
    void resize(int);
    int hash(int);
    HashTable(int);
public:
    HashTable();
    ~HashTable();
    void add(int, int);
    bool exists(int);
    int get(int);
    void remove(int);
    void show();
};

HashTable::HashTable() : HashTable(8) {}

HashTable::HashTable(int n) {
    size = 0;
    capacity = n;
    entries = new Entry[capacity];
    for (int i = 0; i < capacity; i++) {
        entries[i].key = entries[i].value = 0;
        entries[i].state = NONE;
    }    
}

HashTable::~HashTable() {
    // delete[] entries;
    // entries = nullptr;
    // size = capacity = 0;
}

void HashTable::resize(int n) {
    HashTable tmp(n);
    for (int i = 0; i < capacity; i++)
        if (entries[i].state == ALIVE)
            tmp.add(entries[i].key, entries[i].value);

    delete[] entries;
    size = tmp.size;
    capacity = n;
    entries = new Entry[capacity];
    for (int i = 0; i < capacity; i++)
        entries[i] = tmp.entries[i];
}

int HashTable::hash(int key) {
    return key % capacity;
}

void HashTable::add(int key, int value) {
    int h = hash(key);
    while (entries[h].state == ALIVE) {
        if (entries[h].key == key) {
            entries[h].value = value;
            return;
        }
        h = (h + 1) % capacity;
    }
    
    entries[h].key = key;
    entries[h].value = value;
    entries[h].state = ALIVE;
    size++;

    if ((capacity * 2) / 3 <= size)
        resize(capacity * 2);
}

bool HashTable::exists(int key) {
    int h = hash(key);
    while (entries[h].state != NONE) {
        if (entries[h].state == ALIVE && entries[h].key == key)
            return true;

        h = (h + 1) % capacity;
    }
    return false;
}

int HashTable::get(int key) {
    int h = hash(key);
    while (entries[h].state != NONE) {
        if (entries[h].state == ALIVE && entries[h].key == key)
            return entries[h].value;

        h = (h + 1) % capacity;
    }

    return -1;
}

void HashTable::remove(int key) {
    int h = hash(key);
    while (entries[h].state != NONE) {
        if (entries[h].state == ALIVE && entries[h].key == key) {
            entries[h].state = DEAD;
            return;
        }

        h = (h + 1) % capacity;
    }
}

void HashTable::show() {
    cout << "Table details:\n";
    for (int i = 0; i < capacity; i++)
        cout << "{ key=" << entries[i].key << " , value=" << entries[i].value << " }\n";
    cout << "\n";
}

int main() {
    HashTable table;
    table.add(0, 10);
    table.add(1, 12);
    table.add(32, 10);
    table.add(32, 100);
    table.show();
    cout << "Does key 30 exist?: " << ((table.exists(30)) ? "Yes" : "No") << "\n";
    cout << "Does key 32 exist?: ";
    if (table.exists(32))
        cout << "Yes, and the value of that key is " << table.get(32) << ".\n";
    else
        cout << "No\n";

    table.remove(1);
    cout << "Does key 1 exist?: ";
    if (table.exists(1))
        cout << "Yes, and the value of that key is " << table.get(1) << ".\n";
    else
        cout << "No\n";
    
    cout << "\n";
    table.add(3, 3);
    table.add(4, 4);
    table.show();

    return 0;
}