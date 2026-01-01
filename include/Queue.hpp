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
	Queue(const Queue<T> &other): front(nullptr), rear(nullptr), size(0){
		Node<T> *current = other.front;
		while(current){
			enqueue(current->data);
			current = current->next;
		}
	}
	~Queue(){
		clear();
	}
	Queue<T>& operator=(const Queue<T> &other){
		if(this!= &other){
			clear();
			Node<T> *current = other.front;
			while(current){
				enqueue(current->data);
				current = current->next;
			}
		}
		return *this;
	}
	
	void enqueue(const T &value){
		Node<T> *newNode = new Node<T>(value);
		
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