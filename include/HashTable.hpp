#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <string>
#include "LinkedList.hpp"
#include "HashEntry.hpp"

using namespace std;

struct HashTable{
private:
	static const int TABLE_SIZE = 101;
	LinkedList<HashEntry> *table;
	
	int hashFunction(string &key){
		int hash = 0;
		for(char c : key)
			hash = (hash * 31 + c) % TABLE_SIZE;
		return hash;
	}

public:
	HashTable(){
		table = new LinkedList<HashEntry>[TABLE_SIZE];
	}
	
	~HashTable(){
		delete[] table;
	}
	
	void insert(string &word){
		int index = hashFunction(word);
		Node<HashEntry> current = table[index].getHead();
		
		while(current){
			if(current->data.word == word){
				current->data.frequency++;
				return;
			}
			current = current->next;
		}
		
		HashEntry entry(word);
		table[index].insert(entry);
	}
	
	LinkedList<HashEntry>& getBucket(int index){
		return table[index];
	}
	
	int getTableSize(){
		return TABLE_SIZE;
	}
};

#endif