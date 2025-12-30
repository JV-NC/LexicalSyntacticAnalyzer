#include "../include/Token.hpp"
#include <string>

Token::Token(): text(""), frequency(0) {}

Token::Token(const string &t): text(t), frequency(0) {}

Token::Token(const Token &other): text(other.text), frequency(other.frequency), occurrences(other.occurrences) {}

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