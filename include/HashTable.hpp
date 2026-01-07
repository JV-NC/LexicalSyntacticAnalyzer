/**
 * @file HashTable.hpp
 * @brief Generic hash table implementation using separate chaining.
 */

#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <string>
#include "LinkedList.hpp"

using namespace std;
/**
 * @class HashTable
 * @brief Generic hash table with chaining.
 * 
 * @tparam T Type stored in the hash table.
 */
template <typename T>
struct HashTable{
private:
	/** Fixed table size */
	static const int TABLE_SIZE = 101;
	/** Buckets */
	LinkedList<T> *table;
	
	/**
	 * @brief Hash function for strings.
	 * 
	 * Complexity: O(k), k = key length
	 * @return Hash value.
	 */
	int hashFunction(const string &key) const{
		int hash = 0;
		for(char c : key)
			hash = (hash * 31 + c) % TABLE_SIZE;
		return hash;
	}

public:
	/** Constructor */
	HashTable(){
		table = new LinkedList<T>[TABLE_SIZE];
	}
	/** Copy constructor */
	HashTable(const HashTable &other){
		table = new LinkedList<T>[TABLE_SIZE];
		for(int i=0; i<TABLE_SIZE; i++){
			table[i] = other.table[i]; //uses LinkedList copy constructor
		}
	}
	/** Destructor */
	~HashTable(){
		delete[] table;
	}
	/** Inserts a key (specialized for string) */
	void insert(const string &key); //declaration for class specialization of HashTable<string>
	/**
	 * @brief Inserts a token occurrence.
	 * 
	 * Complexity: Averege O(1), worst O(n)
	 */
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
	/**
	 * @brief Inserts a expression occurrence.
	 * 
	 * Complexity: Averege O(1), worst O(n)
	 */
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
	/** Access bucket */
	LinkedList<T>& getBucket(int index){
		return table[index];
	}
	/** Table size */
	int getTableSize(){
		return TABLE_SIZE;
	}
	/**
	 * @brief Counts total objects.
	 * 
	 * Complexity: O(n)
	 * @return Number of objects on Hash Table.
	 */
	int countObjects(){
		int count=0;

		for(int i=0; i<TABLE_SIZE; i++){
			int temp = table[i].getSize();
			count += temp;
		}

		return count;
	}
	/** Checks if key exists */
	bool contains(const string &key){
		int index = hashFunction(key);
		for(auto it = table[index].begin(); it!=table[index].end(); it++){
			if(it->getText()==key){
				return true;
			}
		}
		return false;
	}
	/**
	 * @brief Converts table to array.
	 * 
	 * Complexity: O(n)
	 * @param outSize Output size of the obtained array.
	 * @return Array of T with size outSize.
	 */
	T* toArray(int &outSize){
		outSize = countObjects();

		if(outSize==0)
			return nullptr;

		T *array = new T[outSize];

		int index = 0;

		for(int i=0; i<TABLE_SIZE; i++){
			for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                array[index++] = *it;
            }
		}

		return array;
	}
	/** Clears all buckets */
	void clear(){
		for(int i=0; i<TABLE_SIZE; i++){
			table[i].clear();
		}
	}
};

/** Specialization for HashTable<string> */
template<>
inline void HashTable<string>::insert(const string &key){
	int index = hashFunction(key);

	for(auto it=table[index].begin(); it!=table[index].end(); it++){
		if((*it)==key){
			return;
		}
		table[index].insert(key);
	}
}
template<>
inline bool HashTable<string>::contains(const string &key){
	int index = hashFunction(key);
	for(auto it=table[index].begin(); it!=table[index].end(); it++){
		if((*it)==key){
			return true;
		}
	}
	return false;
}

/** Alias for set behavior */
using HashSet = HashTable<string>;

#endif