#include <iostream>
#include "HeapyPriorityQueue.hpp"


int main() {
    HeapyPriorityQueue<int> heapy_queue;
    heapy_queue.insert(10, 5);
    heapy_queue.insert(20, 1);
    heapy_queue.insert(30, 8);
    heapy_queue.insert(40, 3);
    heapy_queue.insert(25, 4);
    heapy_queue.insert(100, 1);
    heapy_queue.print();

    heapy_queue.modifyKey(30, 15);
    heapy_queue.modifyKey(100, 15);
    heapy_queue.print();

	heapy_queue.findMax();
	heapy_queue.print();
	
	heapy_queue.extractMax();
	heapy_queue.print();

    heapy_queue.extractMax();
    heapy_queue.print();
    
    return 0;
}