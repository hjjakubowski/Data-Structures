#pragma once
#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include <iostream>
using namespace std;

template <typename Elem>
class DNode { 
private:
	Elem elem; 
	DNode* prev; 
	DNode* next; 
	friend class DLinkedList; 
};

template <typename Elem>
class DLinkedList { 
public:
	DLinkedList(); 
	˜DLinkedList(); 
	bool empty() const; 
	const Elem& front() const; 
	const Elem& back() const; 
	void addFront(const Elem& e);
	void addBack(const Elem& e); 
	void removeFront(); 
	void removeBack(); 
	int getSize();
	int Find(const Elem& e);
private: 
	DNode<Elem>* header; 
	DNode<Elem>* trailer;
	void add(DNode<Elem>* v, const Elem& e);
	void remove(DNode<Elem>* v);


};
#endif 
