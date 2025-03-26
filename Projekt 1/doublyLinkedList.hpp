#pragma once
#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include <iostream>
using namespace std;

template <typename Elem>
class DLinkedList { 
public:
	DLinkedList(); 
	~DLinkedList(); 

	bool empty() const; 
	int getSize();
	void addFront(const Elem& e);
	void addBack(const Elem& e); 
	void add(const Elem&, int pos);
	void removeFront(); 
	void removeBack(); 
	void remove(int pos);
	int Find(const Elem& e);

private: 
	
	struct DNode { 
		Elem elem; 
		DNode* prev; 
		DNode* next; 
	};

	DNode* header;
	DNode* trailer;


};
#endif 
