#include "../include/Sentence.hpp"

Sentence::Sentence():
    paragraphNumber(0),
    sentenceNumber(0),
    stopWords(0),
    nonStopWords(0),
    averageWordLength(0.0) {}
Sentence::Sentence(int pN, int sN, int sWords, int nWords, double avrWordLength):
    paragraphNumber(pN),
    sentenceNumber(sN),
    stopWords(sWords),
    nonStopWords(nWords),
    averageWordLength(avrWordLength) {}
    
int Sentence::getParagraphNumber(){
    return paragraphNumber;
}
int Sentence::getSentenceNumber(){
    return sentenceNumber;
}
int Sentence::getAllWords(){
    return stopWords+nonStopWords;
}
int Sentence::getNormalWords(){
    return nonStopWords;
}
double Sentence::getAverageWordLength(){
    return averageWordLength;
}