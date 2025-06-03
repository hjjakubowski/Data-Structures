#include <iostream>

template <typename KeyType, typename ValueType>
class HashMapBucketList {
private:
    struct Node {
        KeyType key;
        ValueType value;
        Node* next;
        Node(const KeyType& k, const ValueType& v);
    };

    Node** table;
    int capacity;
    int numOfElements;
    int hashFunction(const KeyType&) const;

public:
    HashMapBucketList(int cap = 100);
    ~HashMapBucketList();

    void insert(const KeyType& key, const ValueType& value);
    void remove(const KeyType& key);
	void print() const;
    int getSize() const;
};


template <typename KeyType, typename ValueType>
HashMapBucketList<KeyType, ValueType>::Node::Node(const KeyType& k, const ValueType& v)
    : key(k), value(v), next(nullptr) {
}


template <typename KeyType, typename ValueType>
HashMapBucketList<KeyType, ValueType>::HashMapBucketList(int cap): capacity(cap), numOfElements(0){
    table = new Node * [capacity];
    for (int i = 0; i < capacity; ++i)
        table[i] = nullptr;
}

template <typename KeyType, typename ValueType>
HashMapBucketList<KeyType, ValueType>::~HashMapBucketList() {
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

template <typename KeyType, typename ValueType>
int HashMapBucketList<KeyType, ValueType>::hashFunction(const KeyType& key) const
{
    return static_cast<int>(key) % capacity;
}
template <typename KeyType, typename ValueType>
void HashMapBucketList<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
	int bucketIndex = hashFunction(key);
    Node* node = table[bucketIndex];
    while (node) {
        if (node->key == key) {
            node->value = value;
            return;
        }
        node = node->next;
    }
    Node* newNode = new Node(key, value);
    newNode->next = table[bucketIndex];
    table[bucketIndex] = newNode;
    ++numOfElements;
}

template <typename KeyType, typename ValueType>
void HashMapBucketList<KeyType, ValueType>::remove(const KeyType& key) {
	if (numOfElements == 0) {
		throw std::out_of_range("HashMap is empty");
	}
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

template <typename KeyType, typename ValueType>
void HashMapBucketList<KeyType, ValueType>::print() const {
    for (int i = 0; i < capacity; ++i) {
        std::cout << "Bucket " << i << ": ";
        Node* node = table[i];
        if (!node) {
            std::cout << "pusty";
        }
        while (node) {
            std::cout << "[" << node->key << " : " << node->value << "]";
            if (node->next) std::cout << " -> ";
            node = node->next;
        }
        std::cout << std::endl;
    }
}
template <typename KeyType, typename ValueType>
int HashMapBucketList<KeyType, ValueType>::getSize() const {
    return numOfElements;
}
