#ifndef REPORT_HPP
#define REPORT_HPP

#include <ostream>
#include "Analyzer.hpp"
#include "Token.hpp"

class Report{
private:
    Analyzer &analyzer;
    ostream &out;

    void printLine(char c, int n);
    void printTitle(const string &title);

    void printPartialResult();
    void printParagraphPartial(int paragraphNumber);
    void printFullResult();

    void printSentenceStats();
    void printParagraphStats();

public:
    Report(Analyzer &a, ostream &output);

    void generate();
};

#endif