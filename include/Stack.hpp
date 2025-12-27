#ifndef STACK_HPP
#define STACK_HPP

#include "Node.hpp"

using namespace std;
template <typename T>

class Stack{
private:
    Node<T> *topNode;
	int size;
public:
	Stack(): topNode(nullptr), size(0) {}
	~Stack(){
		clear();
	}
	
    void push(T &value){
		Node<T> *newNode = new Node<T>(value);
		newNode->next = topNode;
		topNode = newNode;
		size++;
	}
	bool pop(T &removed){
		if(isEmpty())
			return false;
		
		Node<T> *temp = topNode;
		removed = temp->data;
		topNode = temp->next;
		delete temp;
		size--;
		return true;
	}
	bool peek(T &value){
		if(isEmpty())
			return false;
		
		value = topNode->data;
		return true;
	}
	bool isEmpty(){
		return topNode == nullptr;
	}
	void getSize(){
		return size;
	}
	void clear(){
		T dummy;
		while(!isEmpty())
			pop(dummy);
	}
};
#endif