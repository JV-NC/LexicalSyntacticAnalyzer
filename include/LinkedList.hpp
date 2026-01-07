/**
 * @file LinkedList.hpp
 * @brief Generic linked list implementation.
 */

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Node.hpp"
#include <stdexcept>

using namespace std;

/**
 * @class LinkedList
 * @brief Generic linked list implementation.
 * 
 * Provides a generic singly linked list with sequential insertion, indexed access, iteration support and conversion to array.
 * 
 * @tparam T Type of the elements stored in the list
 * 
 * @see Node
 * @see HashTable
 */
template <typename T>
class LinkedList{
private:
    Node<T> *head; /**< Pointer to the first node. */
	int size; /**< Number of elements in the list */

	/**
     * @brief Returns the head node.
     * @return Pointer to the first node.
     */
	Node<T>* getHead() const{
		return head;
	}

public:
	/**
     * @brief Constructs an empty linked list.
     */
    LinkedList() : head(nullptr), size(0) {}
	/**
     * @brief Copy constructor.
     * @param other List to be copied.
     */
	LinkedList(const LinkedList<T> &other): head(nullptr), size(0){
		Node<T> *current = other.getHead();
		while(current){
			insert(current->data);
			current = current->next;
		}
	}
	/**
     * @brief Destructor. Releases all allocated nodes.
     */
	~LinkedList(){
		clear();
	}
	/**
     * @brief Assignment operator.
     * @param other List to be assigned.
     * @return Reference to this list.
     */
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
	
	/**
     * @brief Inserts an element at the end of the list.
	 * 
	 * Complexity: O(n).
     * @param value Element to be inserted.
     */
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
	/**
     * @brief Returns the element at a given index.
	 * 
	 * Complexity: O(n).
     * @param i Index of the element.
     * @return Element stored at index i.
     * @throws std::out_of_range If index is invalid.
     */
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
	/**
     * @brief Checks whether the list is empty.
     * @return True if empty, false otherwise.
     */
	bool isEmpty(){
		return head == nullptr;
	}
	/**
     * @brief Returns the number of elements in the list.
     * @return List size.
     */
	int getSize(){
		return size;
	}
	/**
     * @brief Removes all elements from the list.
	 * 
	 * Complexity: O(n).
     */
	void clear(){
		Node<T> *temp;
		while(head){
			temp = head;
			head = head->next;
			delete temp;
		}
		size = 0;
	}
	/**
     * @brief Converts the list to a dynamic array.
     *
     * The caller is responsible for freeing the returned array.
	 * 
	 * Complexity: O(n).
     *
     * @param outSize Receives the number of elements copied.
     * @return Pointer to the allocated array or nullptr if empty.
     */
	T* toArray(int &outSize){
		outSize = size;
		if(outSize==0){
			return nullptr;
		}

		T *arr = new T[outSize];

		int i=0;
		Node<T> *current = head;
		while(current){
			arr[i] = current->data;
			current = current->next;
			i++;
		}
		return arr;
	}

	/**
	 * @class Iterator
     * @brief Forward iterator for LinkedList.
     */
	class Iterator{
	private:
		Node<T> *current;
	public:
		/**
         * @brief Constructs an iterator.
         * @param start Starting node.
         */
		Iterator(Node<T> *start): current(start) {}

		/**
         * @brief Dereference operator.
         * @return Reference to the current element.
         */
		T& operator*(){
			return current->data;
		}
		/**
         * @brief Pre-increment operator.
         * @return Reference to the iterator.
         */
		Iterator& operator++(){
			if(current){
				current = current->next;
			}
			return *this;
		}
		/**
         * @brief Post-increment operator.
         * @return Copy of the iterator before increment.
         */
		Iterator operator++(int){
        Iterator temp = *this;
        if (current) {
            current = current->next;
        }
        return temp;  
    }
		/**
         * @brief Inequality comparison.
         */
		bool operator!=(const Iterator &other){
			return current!=other.current;
		}
		/**
         * @brief Equality comparison.
         */
		bool operator==(const Iterator& other){
            return current==other.current;
        }
	};
	/**
     * @brief Returns iterator to the beginning.
     */
	Iterator begin(){
		return Iterator(head);
	}
	/**
     * @brief Returns iterator to the end.
     */
	Iterator end(){
		return Iterator(nullptr);
	}
};
#endif