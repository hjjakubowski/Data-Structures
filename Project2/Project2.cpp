#include <iostream>
#include "linkedQueue.hpp"

int main() {
    LinkedQueue<int> queue;
    queue.insert(10, 5);
    
    queue.insert(20, 1);
    
    queue.insert(30, 8);
    queue.insert(40, 3);
    queue.insert(25, 4);
    queue.insert(100, 1);
    queue.modifyKey(30, 15);
    queue.modifyKey(100, 15);
    queue.print();
    std::cout << "Queue size: " << queue.getSize() << std::endl;
    return 0;
}
