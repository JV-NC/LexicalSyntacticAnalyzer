#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include "TextReader.hpp"
#include "HashTable.hpp"
#include "Sentence.hpp"
#include "Paragraph.hpp"
#include "LinkedList.hpp"
#include "Queue.hpp"
#include "Token.hpp"
#include "Expression.hpp"

class Analyzer{
private:
    HashTable<Token> tokens;
    LinkedList<HashTable<Token>> sentenceTokens;

    HashTable<Expression> allExpressions;
    LinkedList<HashTable<Expression>> paragraphExpressions;

    Queue<Sentence> sentences;
    Queue<Paragraph> paragraphs;

    LinkedList<string> stopWords;
    LinkedList<string> expressions;

    void loadStopWords(const string &filename);
    void loadExpressions(const string &filename);
    bool isSentenceEnd(char c);
    bool isWordChar(unsigned char c);
    bool isStopWord(string &word);
    void checkExpressions(const string &line, int lineNumber, HashTable<Expression> &currentExpressions);
    string normalizeWord(const string &word);
    string normalizeLine(const string &line);
    void finalizeSentenceIfPending(int &sentenceNumber, int paragraphNumber, int &stopWordsNum, int &nonStopWords, int &totalWordLength, int &position, HashTable<Token> &currentTokens);

public:
    Analyzer(const string &stopWordsFilename, const string &expressionsFilename);

    void analyze(TextReader &reader);

    HashTable<Token>& getTokens();
    LinkedList<HashTable<Token>>& getSentenceTokens();
    HashTable<Expression>& getAllExpressions();
    LinkedList<HashTable<Expression>>& getParagraphExpressions();
    Queue<Sentence>& getSentences();
    Queue<Paragraph>& getParagraphs();
};

#endif