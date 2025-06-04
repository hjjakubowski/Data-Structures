#pragma once
#include <iostream>
using namespace std;

// Klasa szablonowa AVL Tree, przechowująca pary klucz-wartość
template<typename K, typename V>
class AVL {
private:
    // Struktura węzła drzewa
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
        int height;
        Node(K k, V val) : key(k), value(val), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root; // Wskaźnik na korzeń drzewa

    // Zwraca wysokość danego węzła (0 jeśli nullptr)
    int height(Node* node) {
        return node ? node->height : 0;
    }

    // Zwraca różnicę wysokości lewej i prawej podgałęzi
    int getBalance(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    // Zwraca maksimum z dwóch wartości
    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    // Rotacja w prawo (prawoskręt) - używana w przypadku niezrównoważenia na lewo
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        // Aktualizacja wysokości
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x; // Nowy korzeń poddrzewa
    }

    // Rotacja w lewo (lewoskręt) - używana w przypadku niezrównoważenia na prawo
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        // Aktualizacja wysokości
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y; // Nowy korzeń poddrzewa
    }

    // Rekurencyjne wstawianie elementu
    Node* insert(Node* node, const K& key, const V& value) {
        if (!node) return new Node(key, value);

        // Standardowe wstawianie do drzewa BST
        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else {
            node->value = value; // Nadpisanie wartości, jeśli klucz już istnieje
            return node;
        }

        // Aktualizacja wysokości i równoważenie drzewa
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        // Cztery przypadki niezrównoważenia
        if (balance > 1 && key < node->left->key)
            return rotateRight(node); // Lewo-lewo
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node); // Prawo-prawo
        if (balance > 1 && key > node->left->key) { // Lewo-prawo
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && key < node->right->key) { // Prawo-lewo
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node; // Węzeł jest już zrównoważony
    }

    // Zwraca węzeł o najmniejszym kluczu (używany przy usuwaniu)
    Node* minValueNode(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    // Rekurencyjne usuwanie elementu
    Node* remove(Node* root, const K& key) {
        if (!root) return root;

        // Przejście do odpowiedniego poddrzewa
        if (key < root->key)
            root->left = remove(root->left, key);
        else if (key > root->key)
            root->right = remove(root->right, key);
        else {
            // Węzeł z jednym lub bez dzieci
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    // Brak dzieci
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp; // Jeden potomek
                delete temp;
            } else {
                // Dwa dzieci – znajdź następnika
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->value = temp->value;
                root->right = remove(root->right, temp->key);
            }
        }

        if (!root) return root;

        // Aktualizacja wysokości i równoważenie
        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getBalance(root);

        // Cztery przypadki rotacji przy usuwaniu
        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    // Wypisuje zawartość drzewa w porządku in-order (klucze posortowane)
    void inOrder(Node* node) const {
        if (!node) return;
        inOrder(node->left);
        cout << "(" << node->key << ":" << node->value << ") ";
        inOrder(node->right);
    }

    // Usuwa wszystkie węzły drzewa (rekurencyjnie)
    void deleteTree(Node* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    // Ogólna funkcja in-order przyjmująca funkcję jako argument
    template<typename Func>
    void inOrderApply(Node* node, Func f) const {
        if (!node) return;
        inOrderApply(node->left, f);
        f(node->key, node->value);
        inOrderApply(node->right, f);
    }

public:
    AVL() : root(nullptr) {}            // Konstruktor
    ~AVL() { deleteTree(root); }        // Destruktor

    // Publiczne wstawianie
    void insert(const K& key, const V& value) {
        root = insert(root, key, value);
    }

    // Publiczne usuwanie
    void remove(const K& key) {
        root = remove(root, key);
    }

    // Publiczne wypisywanie (in-order)
    void inOrder() const {
        inOrder(root);
        cout << endl;
    }

    // Zastosowanie funkcji dla każdego elementu
    template<typename Func>
    void forEach(Func f) const {
        inOrderApply(root, f);
    }
};
