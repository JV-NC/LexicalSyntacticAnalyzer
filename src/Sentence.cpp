#include "../include/Sentence.hpp"

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