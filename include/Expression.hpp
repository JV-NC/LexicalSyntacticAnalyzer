#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <string>
#include "LinkedList.hpp"

using namespace std;

class Expression{
private:
    string text;
    int frequency;
    LinkedList<int> lines;

public:
    Expression(); //standard constructor
    Expression(const string &t); //normal constructor
    Expression(const Expression &other); //copy constructor

    void addOccurrence(int line);

    string getText();
    int getFrequency();
    LinkedList<int>& getLines();
};

#endif