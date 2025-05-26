#include <iostream>
#include "AVL.hpp" 

int main() {
    AVL<int> tree;
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1};
    for (int val : values)
        tree.insert(val);

    cout << "In-order traversal: ";
    tree.inOrder();

    cout << "\nBalance factors:\n";
    tree.printBalanceFactors();

    return 0;
}

