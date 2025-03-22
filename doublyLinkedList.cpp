#include 'doubleLinkedList.hpp'

DLinkedList::DLinkedList() { 
	header = new DNode; 
	trailer = new DNode;
	header− > next = trailer; 
	trailer− > prev = header;
}

DLinkedList::˜DLinkedList() { 
	while (!empty()) removeFront(); 
	delete header; 
	delete trailer;
}

bool DLinkedList::empty() const 
{
	return (header− > next == trailer);
}

const Elem& DLinkedList::front() const
{
	return header− > next− > elem;
}

const Elem& DLinkedList::back() const 
{
	return trailer− > prev− > elem;
}

void DLinkedList::add(DNode* v, const Elem& e) {
	DNode* u = new DNode; u− > elem = e; 
	u− > next = v; 
	u− > prev = v− > prev; 
	v− > prev− > next = v− > prev = u;
}

void DLinkedList::addFront(const Elem& e) 
{
	add(header− > next, e);
}

void DLinkedList::addBack(const Elem& e) 
{
	add(trailer, e);
}

void DLinkedList::remove(DNode* v) { 
	DNode* u = v− > prev; 
	DNode* w = v− > next; 
	u− > next = w; 
	w− > prev = u;
	delete v;
}

void DLinkedList::removeFront() 
{
	remove(header− > next);
}

void DLinkedList::removeBack() 
{
	remove(trailer− > prev);
}

