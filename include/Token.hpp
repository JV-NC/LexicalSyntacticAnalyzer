#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include "LinkedList.hpp"
#include "Occurrence.hpp"

using namespace std;

class Token{
private:
    string text;
    int frequency;
    LinkedList<Occurrence> occurrences;
public:
    Token(); //standard constructor
    Token(const string &t); //normal constructor
    Token(const Token &other); //copy constructor
    Token& operator=(const Token &other);
    void addOccurrence(int p, int s, int l, int pos);
    string getText();
    int getFrequency();
    LinkedList<Occurrence>& getOccurrences();
};
#endif