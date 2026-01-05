#ifndef MAPENTRY_HPP
#define MAPENTRY_HPP

struct MapEntry{
    int key;
    int value;

    //constructor
    MapEntry(int key=0, int value=0): key(key), value(value) {}
};

#endif