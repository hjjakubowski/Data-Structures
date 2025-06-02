#include <iostream>
#include <stdexcept>


template <typename KeyType, typename ValueType>
class HashMapLinearProbing {
    struct HashNode {
        ValueType value;
        KeyType key;
        HashNode(KeyType key, ValueType value)
            : value(value), key(key) {
        }
    };

    HashNode** arr;
    int capacity;
    int numOfElements;
    HashNode* deletedNodeMarker;
    int hashFunction(const KeyType& key) const;

public:
    HashMapLinearProbing();
    HashMapLinearProbing(int initialCapacity);
    ~HashMapLinearProbing();

    void insert(const KeyType& key, const ValueType& value);
    ValueType remove(const KeyType& key);
    void print() const;
    int getSize() const;
};


template <typename KeyType, typename ValueType>
HashMapLinearProbing<KeyType, ValueType>::HashMapLinearProbing()
    : HashMapLinearProbing(20) {}

template <typename KeyType, typename ValueType>
HashMapLinearProbing<KeyType, ValueType>::HashMapLinearProbing(int initialCapacity)
    : capacity(initialCapacity), numOfElements(0)
{
    arr = new HashNode * [capacity];
    for (int i = 0; i < capacity; i++)
        arr[i] = nullptr;

    deletedNodeMarker = new HashNode(KeyType(-1), ValueType());
}

template <typename KeyType, typename ValueType>
HashMapLinearProbing<KeyType, ValueType>::~HashMapLinearProbing()
{
    for (int i = 0; i < capacity; ++i) {
        if (arr[i] && arr[i] != deletedNodeMarker)
            delete arr[i];
    }
    delete[] arr;
    delete deletedNodeMarker;
}

template <typename KeyType, typename ValueType>
int HashMapLinearProbing<KeyType, ValueType>::hashFunction(const KeyType& key) const
{
    return static_cast<int>(key) % capacity; 
}

template <typename KeyType, typename ValueType>
void HashMapLinearProbing<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
    if (numOfElements >= capacity * 0.7) { 

        HashNode** oldArr = arr;
        int oldCapacity = capacity;

        capacity *= 2;
        arr = new HashNode * [capacity];
        for (int i = 0; i < capacity; ++i) arr[i] = nullptr;

        for (int i = 0; i < oldCapacity; ++i) {
            if (oldArr[i] && oldArr[i] != deletedNodeMarker) {
                int newIndex = hashFunction(oldArr[i]->key);
                while (arr[newIndex] != nullptr) {
                    newIndex = (newIndex + 1) % capacity;
                }
                arr[newIndex] = oldArr[i];
            }
        }
        delete[] oldArr;
    }
    int hashIndex = hashFunction(key);
    int startIndex = hashIndex;
    do {
        if (arr[hashIndex] == nullptr || arr[hashIndex] == deletedNodeMarker) {
            arr[hashIndex] = new HashNode(key, value);
            ++numOfElements;
            return;
        }
        else if (arr[hashIndex]->key == key) {
            arr[hashIndex]->value = value;
            return;
        }
        hashIndex = (hashIndex + 1) % capacity;
    } while (hashIndex != startIndex);

    throw std::overflow_error("Hash table overflow (no empty slot)");

}

template <typename KeyType, typename ValueType>
ValueType HashMapLinearProbing<KeyType, ValueType>::remove(const KeyType& key){
    if (numOfElements == 0) {
        throw std::out_of_range("HashMap is empty");
    }
    int hashIndex = hashFunction(key);
    int startIndex = hashIndex;
    do {
        if (arr[hashIndex] == nullptr) {
            throw std::out_of_range("Key not found");
        }
        if (arr[hashIndex] != deletedNodeMarker && arr[hashIndex]->key == key) {
            ValueType val = arr[hashIndex]->value;
            delete arr[hashIndex];
            arr[hashIndex] = deletedNodeMarker;
            --numOfElements;
            return val;
        }
        hashIndex = (hashIndex + 1) % capacity;
    } while (hashIndex != startIndex);

    throw std::out_of_range("Key not found");
}

template <typename KeyType, typename ValueType>
void HashMapLinearProbing<KeyType, ValueType>::print() const
{
    for (int i = 0; i < capacity; i++) {
        if (arr[i] && arr[i] != deletedNodeMarker)
            std::cout << "key = " << arr[i]->key << "  value = " << arr[i]->value << std::endl;
    }
}

template <typename KeyType, typename ValueType>
int HashMapLinearProbing<KeyType, ValueType>::getSize() const {
    return numOfElements;
}

