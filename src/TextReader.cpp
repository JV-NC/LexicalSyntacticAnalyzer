#include "../include/TextReader.hpp"

TextReader::TextReader(string &filename): currentLine(0){
    file.open(filename.c_str());
}
TextReader::~TextReader(){
    if(file.is_open()){
        file.close();
    }
}

bool TextReader::isOpen(){
    return file.is_open();
}
bool TextReader::hasNextLine(){
    return file && !file.eof();
}
string TextReader::nextLine(){
    string line;
    if(getline(file,line)){
        currentLine++;
        return line;
    }
    return "";
}
int TextReader::getCurrentLine(){
    return currentLine;
}