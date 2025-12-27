#include "../include/Token.hpp"
#include <string>

Token::Token(string &t): text(t), frequency(0) {} //TODO: 0 or 1?

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