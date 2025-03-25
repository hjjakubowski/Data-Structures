#pragma once

class Node {
public:
    int item;
    Node* next;

    Node(int item, Node* next = nullptr);
};
