#ifndef NODE_HPP
#define NODE_HPP

using namespace std;
template <typename T>

struct Node {
    T data;
    Node<T>* next;
	
	//inline constructor
    Node(T &value) : data(value), next(nullptr) {}
};

#endif