#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

using namespace std;

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