#pragma once
template<typename T>
class Node {
public:
    T item;
    Node* next;

    Node(T item, Node* next = nullptr);
};
