#include <iostream>
#include "AVL.hpp" 

int main() {
    AVL<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(2);
    tree.insert(7);
    tree.insert(12);
    tree.insert(20);

    std::cout << "InOrder traversal: ";
    tree.inOrder(); 

    return 0;
}
