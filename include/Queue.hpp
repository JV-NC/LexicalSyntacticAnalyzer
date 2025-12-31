#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "Node.hpp"

using namespace std;
template <typename T>

class Queue{
private:
    Node<T> *front;
	Node<T> *rear;
	int size;
public:
	Queue(): front(nullptr), rear(nullptr), size(0) {}
	~Queue(){
		clear();
	}
	
	void enqueue(T &value){
		Node<T> newNode = new Node<T>(value);
		
		if(isEmpty()){
			front = rear = newNode;
		} else{
			rear->next = newNode;
			rear = newNode;
		}
		size++;
	}
    bool dequeue(T &removed){
		if(isEmpty())
			return false;
		
		Node<T> *temp = front;
		removed = temp->data;
		front = front->next;
		
		if(!front)
			rear = nullptr;
		
		delete temp;
		size--;
		return true;
	}
	bool isEmpty(){
		return front == nullptr;
	}
	int getSize(){
		return size;
	}
	void clear(){
		T dummy;
		while(!isEmpty())
			dequeue(dummy);
	}
};
#endif