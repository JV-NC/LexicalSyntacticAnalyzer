#ifndef SENTENCE_HPP
#define SENTENCE_HPP

class Sentence{
private:
    int paragraphNumber;
    int sentenceNumber;
    int stopWords;
    int nonStopWords;
    double averageWordLength;
public:
    Sentence();
    Sentence(int pN, int sN, int sWords, int nWords, double avrWordLength);
    
    int getParagraphNumber();
    int getSentenceNumber();
    int getAllWords();
    int getNormalWords();
    double getAverageWordLength();
};
#endif