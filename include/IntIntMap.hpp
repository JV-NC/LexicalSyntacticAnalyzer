/**
 * @file IntIntMap.hpp
 * @brief Defines a simple integer-to-integer map.
 */

#ifndef INTINTMAP_HPP
#define INTINTMAP_HPP

#include "LinkedList.hpp"
#include "MapEntry.hpp"

/**
 * @class IntIntMap
 * @brief Custom map implementation (int to int).
 * 
 * Used to avoid STL and support frequency distribution.
 * 
 * @see MapEntry
 */
class IntIntMap{
private:
    /** Internal storage */
    LinkedList<MapEntry> list;

public:
    /** Constructor */
    IntIntMap();
    /** Destructor */
    ~IntIntMap();
    /**
     * @brief Increments value by 1.
     * 
     * Complexity: O(n)
     * @param key Key value for search on map.
     */
    void increment(int key);
    /**
     * @brief Increments value by a given amount.
     * 
     * Complexity: O(n)
     * @param key Key value for search on map.
     * @param amount Value that will be incremented.
     */
    void increment(int key, int amount);
    /**
     * @brief Retrieves value for key.
     * 
     * Complexity: O(n)
     * @param key Search key value.
     * @return Int value.
     */
    int get(int key);
    /** 
     * @brief Returns number of entries.
     * 
     * Complexity: O(1)
     * @return Number of entries.
     */
    int size();
    /** Access Entries */
    LinkedList<MapEntry>& getEntries();
    /** Clears map */
    void clear();
};

#endif