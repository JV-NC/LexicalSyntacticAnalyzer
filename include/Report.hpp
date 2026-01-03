#ifndef REPORT_HPP
#define REPORT_HPP

#include <ostream>
#include "Analyzer.hpp"
#include  "Sorter.hpp"
#include "TokenComparators.hpp"
#include "ExpressionComparators.hpp"

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
    void printSortedExpressionTable(HashTable<Expression> &hash);

    void printSentenceStats();
    void printParagraphStats();

public:
    Report(Analyzer &a, ostream &output);

    void generate();
};

#endif