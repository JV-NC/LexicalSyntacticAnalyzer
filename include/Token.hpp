#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

using namespace std;

//TODO: it must need to have many paragraph/sentence/line/position (vector or linkedlist?)
class Token{
private:
    int paragraph;
    int sentence;
    int line;
    int position;
    string text;
public:
    Token(string t, int p, int s, int l, int pos);
    string getText();
};
#endif