#include <iostream>

class HashMap {
private:
    struct Node {
        int key;
        int value;
        Node* next;
        Node(int k, int v);
    };

    Node** table;
    int capacity;
    int numOfElements;

    int hashFunction(int key) const;

public:
    HashMap(int cap = 100);
    ~HashMap();

    void insert(int key, int value);
    void remove(int key);
    bool search(int key, int& value) const;
    int size() const;
};


HashMap::Node::Node(int k, int v) : key(k), value(v), next(nullptr) {}

HashMap::HashMap(int cap) : capacity(cap), numOfElements(0) {
    table = new Node * [capacity];
    for (int i = 0; i < capacity; ++i)
        table[i] = nullptr;
}

HashMap::~HashMap() {
    for (int i = 0; i < capacity; ++i) {
        Node* node = table[i];
        while (node) {
            Node* temp = node;
            node = node->next;
            delete temp;
        }
    }
    delete[] table;
}

int HashMap::hashFunction(int key) const {
    return key % capacity;
}

void HashMap::insert(int key, int value) {
    int bucketIndex = hashFunction(key);
    Node* node = table[bucketIndex];
    // Nadpisz, jeœli ju¿ istnieje
    while (node) {
        if (node->key == key) {
            node->value = value;
            return;
        }
        node = node->next;
    }
    // Dodaj na pocz¹tek listy
    Node* newNode = new Node(key, value);
    newNode->next = table[bucketIndex];
    table[bucketIndex] = newNode;
    ++numOfElements;
}

void HashMap::remove(int key) {
    int bucketIndex = hashFunction(key);
    Node* node = table[bucketIndex];
    Node* prev = nullptr;
    while (node) {
        if (node->key == key) {
            if (prev)
                prev->next = node->next;
            else
                table[bucketIndex] = node->next;
            delete node;
            --numOfElements;
            return;
        }
        prev = node;
        node = node->next;
    }
}

bool HashMap::search(int key, int& value) const {
    int bucketIndex = hashFunction(key);
    Node* node = table[bucketIndex];
    while (node) {
        if (node->key == key) {
            value = node->value;
            return true;
        }
        node = node->next;
    }
    return false;
}

int HashMap::size() const {
    return numOfElements;
}
