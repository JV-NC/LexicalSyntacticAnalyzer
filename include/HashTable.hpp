#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <string>
#include "LinkedList.hpp"
#include "Token.hpp"
#include "Node.hpp"

using namespace std;

struct HashTable{
private:
	static const int TABLE_SIZE = 101;
	LinkedList<Token> *table;
	
	int hashFunction(string &key){
		int hash = 0;
		for(char c : key)
			hash = (hash * 31 + c) % TABLE_SIZE;
		return hash;
	}

public:
	HashTable();
	~HashTable();

	void insert(string &word, int paragraph, int sentence, int line, int position);
	LinkedList<Token>& getBucket(int index);
	int getTableSize();
};

#endif