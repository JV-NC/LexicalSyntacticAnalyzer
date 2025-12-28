#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include "TextReader.hpp"
#include "HashTable.hpp"
#include "Sentence.hpp"
#include "Paragraph.hpp"
#include "LinkedList.hpp"

class Analyzer{
private:
    HashTable tokens;
    LinkedList<Sentence> sentences;
    LinkedList<Paragraph> paragraphs;
    LinkedList<string> stopWords;

    void loadStopWords(string& filename);
    bool isSentenceEnd(char c);
    bool isWordChar(char c);
    bool isStopWord(string &word);
    string normalizeWord(string &word);

public:
    Analyzer();

    void analyze(TextReader &reader);

    HashTable& getTokens();
    LinkedList<Sentence>& getSentences();
    LinkedList<Paragraph>& getParagraphs();
};

#endif