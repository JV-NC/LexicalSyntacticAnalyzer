#include "../include/HashTable.hpp"

HashTable::HashTable(){
    table = new LinkedList<Token>[TABLE_SIZE];
}

HashTable::~HashTable(){
    delete[] table;
}

void HashTable::insert(string &word, int paragraph, int sentence, int line, int position){
    int index = hashFunction(word);
    Node<Token> *current = table[index].getHead();
    
    while(current){
        if(current->data.getText() == word){
            current->data.addOccurrence(paragraph, sentence, line, position);
            return;
        }
        current = current->next;
    }
    
    Token token(word);
    token.addOccurrence(paragraph, sentence, line, position);
    table[index].insert(token);
}

LinkedList<Token>& HashTable::getBucket(int index){
    return table[index];
}

int HashTable::getTableSize(){
    return TABLE_SIZE;
}

int HashTable::countTokens(){
    int count=0;

    for(int i=0; i<TABLE_SIZE; i++){
        int temp = table[i].getSize();
        count += temp;
    }

    return count;
}

Token* HashTable::toArray(int &outSize){
    outSize = countTokens();

    if(outSize==0)
        return nullptr;

    Token *array = new Token[outSize];

    int index = 0;

    for(int i=0; i<TABLE_SIZE; i++){
        Node<Token> *current = table[i].getHead();
        while(current){
            array[index++] = current->data;
            current = current->next;
        }
    }

    return array;
}

void HashTable::clear(){
    for(int i=0; i<TABLE_SIZE; i++){
        table[i].clear();
    }
}