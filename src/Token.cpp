#include "../include/Token.hpp"
#include <string>

Token::Token(): text(""), frequency(0) {}

Token::Token(string &t): text(t), frequency(0) {}

Token::Token(Token &other): text(other.text), frequency(other.frequency){
    Node<Occurrence> *current = other.occurrences.getHead();
    while(current){
        occurrences.insert(current->data);
        current = current->next;
    }
}

void Token::addOccurrence(int p, int s, int l, int pos){
    Occurrence occ(p,s,l,pos);
    occurrences.insert(occ);
    frequency++;
}

string Token::getText(){
    return text;
}

int Token::getFrequency(){
    return frequency;
}
LinkedList<Occurrence>& Token::getOccurrences(){
    return occurrences;
}