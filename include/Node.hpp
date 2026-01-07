/**
 * @file Node.hpp
 * @brief Defines Node struct.
 */

#ifndef NODE_HPP
#define NODE_HPP

using namespace std;

/**
 * @struct Node
 * @brief Node structure for singly linked lists.
 *
 * Stores a data element and a pointer to the next node.
 *
 * @tparam T Type of stored data.
 */
template <typename T>
struct Node {
    T data; /**< Stored data */
    Node<T>* next; /**< Pointer to the next node */
	
	/**
     * @brief Constructs a node with given value.
     * @param value Data to store.
     */
    Node(const T &value) : data(value), next(nullptr) {}
};

#endif