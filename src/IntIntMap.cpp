#include "../include/IntIntMap.hpp"

IntIntMap::IntIntMap(){

}
IntIntMap::~IntIntMap(){

}
void IntIntMap::increment(int key){
    increment(key, 1);
}
void IntIntMap::increment(int key, int amount){
    for(LinkedList<MapEntry>::Iterator it = list.begin(); it != list.end(); it++){
        if((*it).key == key) {
            (*it).value+=amount;
            return;
        }
    }
    list.insert(MapEntry(key, amount));
}
int IntIntMap::get(int key){
    for(LinkedList<MapEntry>::Iterator it=list.begin(); it!=list.end(); it++){
        if((*it).key == key){
            return (*it).value;
        }
    }
    return 0;
}
int IntIntMap::size(){
    return list.getSize();
}
LinkedList<MapEntry>& IntIntMap::getEntries(){
    return list;
}
void IntIntMap::clear(){
    list.clear();
}