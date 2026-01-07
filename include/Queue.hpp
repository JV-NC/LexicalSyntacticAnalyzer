/**
 * @file Queue.hpp
 * @brief Defines generic Queue class.
 */

#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "Node.hpp"

using namespace std;
template <typename T>

/**
 * @class Queue
 * @brief Generic FIFO queue implemented.
 *
 * This queue supports enqueue and dequeue operations following
 * First-In-First-Out (FIFO) semantics.
 *
 * @tparam T Type of stored elements.
 * @see Node
 */
class Queue{
private:
    Node<T> *front; ///< Pointer to the front element
	Node<T> *rear; ///< Pointer to the rear element
	int size; ///< Number of elements in the queue
public:
	/** @brief Constructs an empty queue. */
	Queue(): front(nullptr), rear(nullptr), size(0) {}
	/**
     * @brief Copy constructor.
     * @param other Queue to copy.
     */
	Queue(const Queue<T> &other): front(nullptr), rear(nullptr), size(0){
		Node<T> *current = other.front;
		while(current){
			enqueue(current->data);
			current = current->next;
		}
	}
	/** @brief Destructor. Clears all elements. */
	~Queue(){
		clear();
	}
	/**
     * @brief Assignment operator.
     * @param other Queue to assign from.
     * @return Reference to this queue.
     */
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
	
	/**
     * @brief Inserts an element at the rear of the queue.
	 * 
	 * Complexity: O(1)
     * @param value Element to enqueue.
     */
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
	/**
     * @brief Removes the front element.
	 * 
	 * Complexity: O(1)
     * @param removed Receives the removed value.
     * @return True if successful, false if queue is empty.
     */
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
	/** @return True if the queue is empty. */
	bool isEmpty(){
		return front == nullptr;
	}
	/** @return Number of elements in the queue. */
	int getSize(){
		return size;
	}
	/** @brief Removes all elements from the queue. */
	void clear(){
		T dummy;
		while(!isEmpty())
			dequeue(dummy);
	}
};
#endif