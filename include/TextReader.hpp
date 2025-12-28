#ifndef TEXTREADER_HPP
#define TEXTREADER_HPP

#include <fstream>
#include <string>

using namespace std;

class TextReader{
private:
    ifstream file;
    int currentLine;

public:
    TextReader(string &filename);
    ~TextReader();

    bool isOpen();
    bool hasNextLine();
    string nextLine();
    int getCurrentLine();
};

#endif