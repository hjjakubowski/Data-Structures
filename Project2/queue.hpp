#pragma once

template<typename T>
class Queue {
protected:
    int size;
public:
    Queue(int size_) : size(size_) {}
    Queue() : size(0) {}
    virtual void insert(const T& e, int p) = 0;
    virtual T extractMax() = 0;
    virtual T findMax() const = 0;
    virtual void modifyKey(const T& e, int p) = 0;
    virtual int returnSize() const = 0;
    virtual bool empty() const = 0;

    virtual ~Queue() {} 
};
