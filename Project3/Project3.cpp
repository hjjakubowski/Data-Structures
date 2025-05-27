#include <iostream>
#include "AVL.hpp" 

int main() {
    AVL<int> tree;
    int values[] = {5,4,7};
    for (int val : values)
        tree.insert(val);

    cout << "In-order traversal: ";
    tree.inOrder();

    cout << "\nBalance factors:\n";
    tree.printBalanceFactors();

    return 0;
}

