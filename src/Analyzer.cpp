#include "../include/Analyzer.hpp"
#include "cctype"
#include <fstream>

Analyzer::Analyzer() {}

void Analyzer::loadStopWords(string& filename){
    ifstream file(filename.c_str());
    string word;

    while(file>>word){
        stopWords.insert(normalizeWord(word));
    }
}
bool Analyzer::isSentenceEnd(char c){
    return c=='.' || c=='!' || c=='?';
}
bool Analyzer::isWordChar(char c){
    return isalpha(c);
}
bool Analyzer::isStopWord(string &word){
    Node<string> *current = stopWords.getHead();
    while(current){
        if(current->data == word)
            return true;
        current = current->next;
    }
    return false;
}
string Analyzer::normalizeWord(string &word){
    string result;

    for(size_t i=0; i<word.size(); i++){
        unsigned char c = word[i];

        if(c== 0x63 && i+1<word.size()){
            unsigned char next = word[i+1];

            switch(next){
                case 0xA0: case 0xA1: case 0xA2: case 0xA3:
                    result+='a';
                break;
                case 0xA9: case 0xAA:
                    result+='e';
                break;
                case 0xAD:
                    result+='i';
                break;
                case 0xB3: case 0xB4: case 0xB5:
                    result+='o';
                break;
                case 0xBA:
                    result+='u';
                break;
                case 0xA7:
                    result+='c';
                break;
                default: break;
            }
            i++;
        }
        else if(isalpha(c)){
            result+=tolower(c);
        }
    }

    return result;
}

void Analyzer::analyze(TextReader &reader){
    int paragraphNumber = 1, sentenceNumber = 0, startingLine = 1;

    while(reader.hasNextLine()){
        string line = reader.nextLine();

        if(line.empty()){
            paragraphs.insert(
                Paragraph(paragraphNumber, startingLine, sentenceNumber)
            );

            paragraphNumber++;
            sentenceNumber = 0;
            startingLine = reader.getCurrentLine()+1;
            continue;
        }

        int i = 0, stopWords = 0, nonStopWords = 0, totalWordLength = 0, position = 0;
        string word;

        for(size_t i=0; i<=line.size(); i++){
            unsigned char c = (i< line.size()) ? line[i]: ' ';

            if(isWordChar(c) || c==0xC3){
                word+=c;
            }else{
                if(!word.empty()){
                    word = normalizeWord(word);
                    if(!word.empty()){
                        position++;

                        if(!isStopWord(word)){
                            tokens.insert(
                                word,
                                paragraphNumber,
                                sentenceNumber+1,
                                reader.getCurrentLine(),
                                position
                            );

                            nonStopWords++;
                            totalWordLength += word.length();
                        }else{
                            stopWords++;
                        }
                    }
                    
                    word.clear();
                }

                if(isSentenceEnd(c)){
                    sentenceNumber++;

                    double avg = (nonStopWords>0)
                        ? static_cast<double>(totalWordLength)/nonStopWords
                        : 0.0;

                    sentences.insert(
                        Sentence(paragraphNumber, sentenceNumber, stopWords, nonStopWords, avg)
                    );

                    stopWords=0;
                    nonStopWords=0;
                    totalWordLength=0;
                    position=0;
                }
            }
            i++;
        }
    }

    paragraphs.insert(
        Paragraph(paragraphNumber, startingLine, sentenceNumber)
    );
}

HashTable& Analyzer::getTokens(){
    return tokens;
}
LinkedList<Sentence>& Analyzer::getSentences(){
    return sentences;
}
LinkedList<Paragraph>& Analyzer::getParagraphs(){
    return paragraphs;
}