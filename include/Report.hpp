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
    void printExpressionTable(HashTable<Expression> &hash);

    void printSentenceStats();
    void printParagraphStats();

public:
    Report(Analyzer &a, ostream &output);

    void generate();
};

#endif