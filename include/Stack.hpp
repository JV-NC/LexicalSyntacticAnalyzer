/**
 * @file Stack.hpp
 * @brief Defines Stack class.
 */

#ifndef STACK_HPP
#define STACK_HPP

#include "Node.hpp"

using namespace std;

/**
 * @class Stack
 * @brief Generic LIFO stack implementation.
 *
 * Supports push, pop, and peek operations.
 *
 * @tparam T Type of stored elements.
 * @see Node
 */
template <typename T>
class Stack{
private:
    Node<T> *topNode; ///< Pointer to the top element
	int size; ///< Number of elements
public:
	/** @brief Constructs an empty stack. */
	Stack(): topNode(nullptr), size(0) {}
	/**
     * @brief Copy constructor.
     * @param other Stack to copy.
     */
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
	/** @brief Destructor. */
	~Stack(){
		clear();
	}
	/**
     * @brief Assignment operator.
     * @param other Stack to assign from.
     * @return Reference to this stack.
     */
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
	
	/**
     * @brief Pushes an element onto the stack.
	 * 
	 * Complexity: O(1)
     * @param value Element to push.
     */
    void push(const T &value){
		Node<T> *newNode = new Node<T>(value);
		newNode->next = topNode;
		topNode = newNode;
		size++;
	}
	/**
     * @brief Removes the top element.
	 * 
	 * Complexity: O(1)
     * @param removed Receives the removed value.
     * @return True if successful, false if stack is empty.
     */
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
	/**
     * @brief Reads the top element without removing it.
	 * 
	 * Complexity: O(1)
     * @param value Receives the top value.
     * @return True if successful, false if stack is empty.
     */
	bool peek(T &value){
		if(isEmpty())
			return false;
		
		value = topNode->data;
		return true;
	}
	/** @return True if the stack is empty. */
	bool isEmpty(){
		return topNode == nullptr;
	}
	/** @return Number of elements in the stack. */
	int getSize(){
		return size;
	}
	/** @brief Clears the stack. */
	void clear(){
		T dummy;
		while(!isEmpty())
			pop(dummy);
	}
};
#endif