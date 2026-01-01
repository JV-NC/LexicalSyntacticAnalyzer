#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Node.hpp"
#include <stdexcept>

using namespace std;
template <typename T>

class LinkedList{
private:
    Node<T> *head;
	int size;

	Node<T>* getHead() const{
		return head;
	}

public:
	//standard constructor, copy constructor, destructor
    LinkedList() : head(nullptr), size(0) {}
	LinkedList(const LinkedList<T> &other): head(nullptr), size(0){
		Node<T> *current = other.getHead();
		while(current){
			insert(current->data);
			current = current->next;
		}
	}
	~LinkedList(){
		clear();
	}
	LinkedList<T>& operator=(const LinkedList& other){
    if(this != &other){
        clear();
        Node<T>* current = other.head;
        while(current){
            insert(current->data);
            current = current->next;
        }
    }
    return *this;
}
	
	void insert(const T &value){
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
	T get(int i) const{
		if(i<0 || i>=getSize()){
			throw out_of_range("Index out of bounds.");
		}
		Node<T> *node = getHead();
		for(int idx=0; idx<i; ++idx){
			node = node->next;
		}
		return node->data;
	}
	bool isEmpty(){
		return head == nullptr;
	}
	int getSize(){
		return size;
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
	class Iterator{
	private:
		Node<T> *current;
	public:
		Iterator(Node<T> *start): current(start) {}

		T& operator*(){
			return current->data;
		}
		Iterator& operator++(){
			if(current){
				current = current->next;
			}
			return *this;
		}
		Iterator operator++(int) { //post increment
        Iterator temp = *this;
        if (current) {
            current = current->next;
        }
        return temp;  
    }
		bool operator!=(const Iterator &other){
			return current!=other.current;
		}
		bool operator==(const Iterator& other){
            return current==other.current;
        }
	};
	Iterator begin(){
		return Iterator(head);
	}
	Iterator end(){
		return Iterator(nullptr);
	}
};
#endif