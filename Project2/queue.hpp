#pragma once

template<typename T>
class Queue {
protected:
    int size;
    class Node {
    public:
        T item;
        int priority;
        Node() : item(T()), priority(0) {}
        Node(T e, int p) : item(e), priority(p) {}
    };

public:
    Queue(int size_) : size(size_) {}
    Queue() : size(0) {}
    virtual void insert(const T& e, int p) = 0;
    virtual T extractMax() = 0;
    virtual T findMax() const = 0;
    virtual void modifyKey(const T& e, int p) = 0;

    int getSize() { return size; }

    virtual ~Queue() {}
};
