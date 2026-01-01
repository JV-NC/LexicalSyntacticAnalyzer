#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <string>
#include "LinkedList.hpp"

using namespace std;

template <typename T>
struct HashTable{
private:
	static const int TABLE_SIZE = 101;
	LinkedList<T> *table;
	
	int hashFunction(const string &key) const{
		int hash = 0;
		for(char c : key)
			hash = (hash * 31 + c) % TABLE_SIZE;
		return hash;
	}

public:
	HashTable(){
		table = new LinkedList<T>[TABLE_SIZE];
	}
	HashTable(const HashTable &other){
		table = new LinkedList<T>[TABLE_SIZE];
		for(int i=0; i<TABLE_SIZE; i++){
			table[i] = other.table[i]; //uses LinkedList copy constructor
		}
	}
	~HashTable(){
		delete[] table;
	}

	void insert(const string &key, int paragraph, int sentence, int line, int position){
		int index = hashFunction(key);
		
		for(auto it=table[index].begin(); it!=table[index].end(); it++){
			if((*it).getText() == key){
				(*it).addOccurrence(paragraph, sentence, line, position);
				return;
			}
		}
		
		T obj(key);
		obj.addOccurrence(paragraph, sentence, line, position);
		table[index].insert(obj);
	}
	void insert(const string &key, int line){
		int index = hashFunction(key);

		for(auto it=table[index].begin(); it!=table[index].end(); it++){
			if((*it).getText() == key){
				(*it).addOccurrence(line);
				return;
			}
		}

		T obj(key);
		obj.addOccurrence(line);
		table[index].insert(obj);
	}
	LinkedList<T>& getBucket(int index){
		return table[index];
	}
	int getTableSize(){
		return TABLE_SIZE;
	}
	int countObjects(){
		int count=0;

		for(int i=0; i<TABLE_SIZE; i++){
			int temp = table[i].getSize();
			count += temp;
		}

		return count;
	}
	T* toArray(int &outSize){
		outSize = countObjects();

		if(outSize==0)
			return nullptr;

		T *array = new T[outSize]; //TODO: check good practice?

		int index = 0;

		for(int i=0; i<TABLE_SIZE; i++){
			for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                array[index++] = *it;
            }
		}

		return array;
	}
	void clear(){
		for(int i=0; i<TABLE_SIZE; i++){
			table[i].clear();
		}
	}
};

#endif