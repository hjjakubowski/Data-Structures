#pragma once

template <typename T>
class AVL {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;

        Node();
        Node(T value_);
    };

    int size;
    Node* root;

public:
    AVL() : size(0), root(nullptr) {}
    int height(Node* node);
    int getBF(Node* node); //balance factor
    void insert(int value);
    void inOrder();
    void inOrder(Node *node);
};


template <typename T>
AVL<T>::Node::Node() : left(nullptr), right(nullptr) {}


template <typename T>
AVL<T>::Node::Node(T value_) : value(value_), left(nullptr), right(nullptr) {}


template <typename T>
int AVL<T>::height(Node* node) {
    if (node == nullptr) {  return -1;}

    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return 1 + std::max(leftHeight, rightHeight);
}


template <typename T>
int AVL<T>::getBF(Node* node) {
    if (node == nullptr) {
        return -1;
    }
    return height(node->left) - height(node->right);
}


template <typename T>
void AVL<T>::insert(int value) {
    Node* newNode = new Node(value);

    if (root == nullptr) {
        root = newNode;
        return;
    }

    Node* current = root;
    Node* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (value < current->value) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    if (value < parent->value) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }
}


template <typename T>
void AVL<T>::inOrder() {
    inOrder(root);
    std::cout << std::endl;
}


template <typename T>
void AVL<T>::inOrder(Node* node) {
    if (node == nullptr) {  return ; }
    inOrder(node->left);
    std::cout << node->value << " ";
    inOrder(node->right);
}
