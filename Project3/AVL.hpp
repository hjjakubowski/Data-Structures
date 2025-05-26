#include <iostream>
using namespace std;


int max(int a, int b) {
    return (a > b) ? a : b;
}

template <typename T>
class AVL {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;
        int height;

        Node(T val);
    };

    Node* root;

    int height(Node* node);
    int getBF(Node* node);
    Node* rotateLeft(Node* z);
    Node* rotateRight(Node* y);
    Node* insert(Node* node, T value);
    void inOrder(Node* node);
    void deleteTree(Node* node);

    void printBalanceFactors(Node* node);
public:
    AVL();
    ~AVL();

    void insert(T value);
    void inOrder();
    void printBalanceFactors();
};


template <typename T>
AVL<T>::Node::Node(T val) : value(val), left(nullptr), right(nullptr), height(0) {}


template <typename T>
AVL<T>::AVL() : root(nullptr) {}




template <typename T>
int AVL<T>::height(Node* node) {
    return node ? node->height : -1;
}


template <typename T>
int AVL<T>::getBF(Node* node) {
    return height(node->left) - height(node->right);
}


template <typename T>
typename AVL<T>::Node* AVL<T>::rotateLeft(Node* z) {
    Node* y = z->right;
    Node* T2 = y->left;

    y->left = z;
    z->right = T2;

    z->height = 1 + max(height(z->left), height(z->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}


template <typename T>
typename AVL<T>::Node* AVL<T>::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}


template <typename T>
typename AVL<T>::Node* AVL<T>::insert(Node* node, T value) {
    if (!node)
        return new Node(value);

    if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBF(node);

    if (balance > 1 && value < node->left->value)
        return rotateRight(node);

    if (balance < -1 && value > node->right->value)
        return rotateLeft(node);

    if (balance > 1 && value > node->left->value) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && value < node->right->value) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

template <typename T>
void AVL<T>::insert(T value) {
    root = insert(root, value);
}

template <typename T>
void AVL<T>::inOrder(Node* node) {
    if (!node) return;
    inOrder(node->left);
    cout << node->value << " ";
    inOrder(node->right);
}


template <typename T>
void AVL<T>::inOrder() {
    inOrder(root);
    cout << endl;
}




template <typename T>
void AVL<T>::printBalanceFactors(Node* node) {
    if (!node) return;
    printBalanceFactors(node->left);
    cout << node->value << ": " << getBF(node) << endl;
    printBalanceFactors(node->right);
}

template <typename T>
void AVL<T>::printBalanceFactors() {
    printBalanceFactors(root);
}
