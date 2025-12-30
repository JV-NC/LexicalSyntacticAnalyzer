#include "../include/Expression.hpp"

Expression::Expression(): text(""), frequency(0) {}
Expression::Expression(const string &t): text(t), frequency(0) {}
Expression::Expression(const Expression &other): text(other.text), frequency(other.frequency), lines(other.lines) {}
Expression& Expression::operator=(const Expression& other){
    if(this!=&other){
        lines.clear();
        lines = other.lines;
    }
    return *this;
}
void Expression::addOccurrence(int line){
    lines.insert(line);
    frequency++;
}

string Expression::getText(){
    return text;
}
int Expression::getFrequency(){
    return frequency;
}
LinkedList<int>& Expression::getLines(){
    return lines;
}