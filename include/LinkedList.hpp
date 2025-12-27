#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Node.hpp"

using namespace std;
template <typename T>

//TODO: implement remove and getat
class LinkedList{
private:
    Node<T> *head;
	int size;
public:
    LinkedList() : head(nullptr), size(0) {}
	~LinkedList(){
		clear();
	}
	
	void insert(T &value){
		Node<T> *newNode = new Node<T>(value);
		
		if(!head){
			head = newNode;
		} else{
			Node<T> *temp = head;
			while(temp->next)
				temp = temp->next;
			temp->next = newNode;
		}
		size++;
	}
	bool isEmpty(){
		return head == nullptr;
	}
	int getSize(){
		return size;
	}
	Node<T>* getHead(){
		return head;
	}
	void clear(){
		Node<T> *temp;
		while(head){
			temp = head;
			head = head->next;
			delete temp;
		}
		size = 0;
	}
};
#endif