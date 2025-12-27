#ifndef SENTENCE_HPP
#define SENTENCE_HPP

using namespace std;

class Sentence{
private:
    int paragraphNumber;
    int sentenceNumber;
    int stopWords;
    int nonStopWords;
    double averageWordLength;
public:
    Sentence(int pN, int sN, int sWords, int nWords, int avrWordLength);
    
};
#endif