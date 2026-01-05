#ifndef INTINTMAP_HPP
#define INTINTMAP_HPP

#include "LinkedList.hpp"
#include "MapEntry.hpp"

class IntIntMap{
private:
    LinkedList<MapEntry> list;

public:
    IntIntMap();
    ~IntIntMap();
    void increment(int key);
    void increment(int key, int amount);
    int get(int key);
    int size();
    LinkedList<MapEntry>& getEntries();
    void clear();
};

#endif