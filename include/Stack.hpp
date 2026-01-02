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
	Stack(const Stack<T> &other): topNode(nullptr), size(0) {
		Stack<T> auxStack;
		Node<T> *current = other.topNode;
		while(current){
			auxStack.push(current->data);
			current = current->next;
		}
		while(!auxStack.isEmpty()){
			T value;
			auxStack.pop(value);
			push(value);
		}
	}
	~Stack(){
		clear();
	}
	Stack<T>& operator=(const Stack<T> &other){
		if(this!= &other){
			clear();

			Stack<T> auxStack;
			Node<T> *current = other.topNode;
			while(current){
				auxStack.push(current->data);
				current = current->next;
			}
			while(!auxStack.isEmpty()){
				T value;
				auxStack.pop(value);
				push(value);
			}
		}
		return *this;
	}
	
    void push(const T &value){
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
	int getSize(){
		return size;
	}
	void clear(){
		T dummy;
		while(!isEmpty())
			pop(dummy);
	}
};
#endif