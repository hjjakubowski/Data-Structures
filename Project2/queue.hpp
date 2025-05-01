#pragma once

template<typename T>
class Queue {
protected:
    int size = 0;

public:
    Queue() {}
    virtual ~Queue() {}

    virtual void insert(const T& e, int p) = 0;
    virtual T extractMax() = 0;
    virtual T findMax() const = 0;
    virtual void modifyKey(const T& e, int p) = 0;
    virtual int getSize() const { return size; }
    virtual bool empty() const = 0;
};
