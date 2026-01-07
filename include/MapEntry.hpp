/**
 * @file MapEntry.hpp
 * @brief Defines MapEntry struct, responsible for key- value pair used in custom map structures.
 */

#ifndef MAPENTRY_HPP
#define MAPENTRY_HPP

/**
 * @struct MapEntry
 * @brief Key-value pair used in custom map structures.
 * 
 * Represents a mapping from an integer key to an integer value, commonly used for frequency counting.
 * 
 * @see IntIntMap
 */
struct MapEntry{
    int key; /**< Map key */
    int value; /**< Associated value */

    /**
     * @brief Constructs a MapEntry.
     * @param key Key value.
     * @param value Initial value.
     */
    MapEntry(int key=0, int value=0): key(key), value(value) {}
};

#endif