#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include "TextReader.hpp"
#include "HashTable.hpp"
#include "Sentence.hpp"
#include "Paragraph.hpp"
#include "LinkedList.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "Token.hpp"
#include "Expression.hpp"
#include "IntIntMap.hpp"
#include "Sorter.hpp"
#include "MapEntryComparators.hpp"

class Analyzer{
private:
    HashTable<Token> tokens;
    LinkedList<HashTable<Token>> sentenceTokens;

    HashTable<Expression> allExpressions;
    LinkedList<HashTable<Expression>> paragraphExpressions;

    Queue<Stack<char>> punctuationBalance;

    Queue<Sentence> sentences;
    Queue<Paragraph> paragraphs;

    LinkedList<string> stopWords;
    LinkedList<string> expressions;
    LinkedList<string> abbreviations;

    IntIntMap lengthDist;

    void loadStopWords(const string &filename);
    void loadExpressions(const string &filename);
    void loadAbbreviations();
    bool isSentenceEnd(char c);
    bool isWordChar(unsigned char c);
    bool isStopWord(string &word);
    void checkExpressions(const string &line, int lineNumber, HashTable<Expression> &currentExpressions);
    char utf8ToAscii(unsigned char lead, unsigned char next);
    string normalizeWord(const string &word);
    string normalizeLine(const string &line);
    void finalizeSentenceIfPending(int &sentenceNumber, int paragraphNumber, int &stopWordsNum, int &nonStopWords, int &totalWordLength, int &position, HashTable<Token> &currentTokens);
    bool isDotInNumber(const string &line, size_t i);
    bool isAbbreviation(const string &word);

    bool isOpening(char c);
    bool isClosing(char c);
    bool matches(char open, char close);

    void generateLengthDistribution();

public:
    Analyzer(const string &stopWordsFilename, const string &expressionsFilename);

    void analyze(TextReader &reader);

    HashTable<Token>& getTokens();
    LinkedList<HashTable<Token>>& getSentenceTokens();
    HashTable<Expression>& getAllExpressions();
    LinkedList<HashTable<Expression>>& getParagraphExpressions();
    Queue<Sentence>& getSentences();
    Queue<Paragraph>& getParagraphs();
    Queue<Stack<char>>& getPunctuationBalance();
    LinkedList<MapEntry>& getLengthDist();
};

#endif