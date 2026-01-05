#ifndef REPORT_HPP
#define REPORT_HPP

#include <ostream>
#include "Analyzer.hpp"

class Report{
private:
    Analyzer &analyzer;
    ostream &out;

    void printLine(char c, int n);
    void printTitle(const string &title);

    void printPartialResult();
    void printParagraphPartial(Paragraph p, Queue<Sentence> &sq, LinkedList<HashTable<Token>>::Iterator &tokenIt, LinkedList<HashTable<Expression>>::Iterator &expIt, Stack<char> ps);
    void printFullResult();
    void printSortedTokenTable(HashTable<Token> &hash, int paragraph, int sentence);
    void printFrequentlyUsedWords(HashTable<Token> &hash);
    void printSortedExpressionTable(HashTable<Expression> &hash);
    void printFullResultSortMetrics(HashTable<Token> &hash);
    void printMostLeastFrequentWords(HashTable<Token> &hash, int X);
    void printLengthDist();
    void printSentenceStats();
    void printParagraphStats();

    void exportSortMetricsCSV();

public:
    Report(Analyzer &a, ostream &output);

    void generate();
};

#endif