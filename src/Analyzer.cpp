#include "../include/Analyzer.hpp"
#include "cctype"
#include <fstream>

Analyzer::Analyzer(const string &stopWordsFilename){
    loadStopWords(stopWordsFilename);
}

void Analyzer::loadStopWords(const string &filename){
    ifstream file(filename.c_str());
    string word;

    while(file>>word){
        stopWords.insert(normalizeWord(word));
    }
}
bool Analyzer::isSentenceEnd(char c){
    return c=='.' || c=='!' || c=='?';
}
bool Analyzer::isWordChar(unsigned char c){
    return (c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        c >= 128;
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

        if(c== 0xC3 && i+1<word.size()){
            unsigned char next = word[i+1];

            switch(next){
                //A
                case 0x80: case 0x81: case 0x82: case 0x83:
                case 0xA0: case 0xA1: case 0xA2: case 0xA3:
                    result+='a';
                break;
                //E
                case 0x88: case 0x89:
                case 0xA9: case 0xAA:
                    result+='e';
                break;
                //I
                case 0x8D:
                case 0xAD:
                    result+='i';
                break;
                // O
                case 0x93: case 0x94: case 0x95:
                case 0xB3: case 0xB4: case 0xB5:
                    result+='o';
                break;
                // U
                case 0x9A:
                case 0xBA:
                    result+='u';
                break;
                // C
                case 0x87:
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
    HashTable current;

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

        int stopWords = 0, nonStopWords = 0, totalWordLength = 0, position = 0;
        string word;

        for(size_t i=0; i<=line.size(); i++){
            unsigned char c = (i< line.size()) ? line[i]: ' ';

            if(isWordChar(c)){
                word+=c;
            }else{
                if(!word.empty()){
                    word = normalizeWord(word);
                    if(!word.empty()){
                        position++;

                        if(!isStopWord(word)){
                            current.insert(
                                word,
                                paragraphNumber,
                                sentenceNumber+1,
                                reader.getCurrentLine(),
                                position
                            );
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

                    current.clear();
                    stopWords=0;
                    nonStopWords=0;
                    totalWordLength=0;
                    position=0;
                }
            }
        }
    }

    paragraphs.insert(
        Paragraph(paragraphNumber, startingLine, sentenceNumber)
    );
}

HashTable& Analyzer::getTokens(){
    return tokens;
}
LinkedList<HashTable>& Analyzer::getSentenceTokens(){
    return sentenceTokens;
}
LinkedList<Sentence>& Analyzer::getSentences(){
    return sentences;
}
LinkedList<Paragraph>& Analyzer::getParagraphs(){
    return paragraphs;
}