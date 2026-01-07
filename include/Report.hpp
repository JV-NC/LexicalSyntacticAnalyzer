/**
 * @file Report.hpp
 * @brief Defines Report class.
 */

#ifndef REPORT_HPP
#define REPORT_HPP

#include <ostream>
#include "Analyzer.hpp"

/**
 * @class Report
 * @brief Generates formatted textual reports and CSV exports based on analysis results.
 *
 * This class is responsible for producing both partial and full reports of the text analysis process, including:
 * - Token statistics
 * - Expression statistics
 * - Sentence and paragraph metrics
 * - Word length distribution
 * - Sorting benchmark metrics
 *
 * @see Analyzer
 */
class Report{
private:
    Analyzer &analyzer; /**< Reference to the Analyzer containing processed data */
    ostream &out; /**< Output stream used to write the report */

    /** @brief Prints a repeated character line. */
    void printLine(char c, int n);
    /** @brief Prints a centered title section. */
    void printTitle(const string &title);

    /** @brief Prints per-paragraph and per-sentence partial results. */
    void printPartialResult();
    /**
     * @brief Prints detailed information for a single paragraph.
     * @param p Paragraph metadata
     * @param sq Queue of sentences
     * @param tokenIt Iterator over sentence token hash tables
     * @param expIt Iterator over paragraph expression hash tables
     * @param ps Stack representing punctuation balance
     */
    void printParagraphPartial(Paragraph p, Queue<Sentence> &sq, LinkedList<HashTable<Token>>::Iterator &tokenIt, LinkedList<HashTable<Expression>>::Iterator &expIt, Stack<char> ps);
    /** @brief Prints the full aggregated analysis result. */
    void printFullResult();
    /** @brief Prints a sorted table of tokens for a given sentence. */
    void printSortedTokenTable(HashTable<Token> &hash, int paragraph, int sentence);
    /** @brief Prints words that appear frequently in a paragraph. */
    void printFrequentlyUsedWords(HashTable<Token> &hash);

    /** @brief Prints expressions sorted alphabetically. */
    void printSortedExpressionTable(HashTable<Expression> &hash);
    /** @brief Prints sorting performance metrics for all benchmark configurations. */
    void printFullResultSortMetrics(HashTable<Token> &hash);
    /**
     * @brief Prints the most and least frequent words.
     * @param X Number of words to display
     */
    void printMostLeastFrequentWords(HashTable<Token> &hash, int X);
    /** @brief Prints the word length distribution. */
    void printLengthDist();
    /** @brief Prints sentence-level statistics. */
    void printSentenceStats();
    /** @brief Prints paragraph-level statistics. */
    void printParagraphStats();

    /** @brief Exports sorting benchmark metrics to CSV. */
    void exportSortMetricsCSV();
    /** @brief Exports word length distribution to CSV. */
    void exportLengthDist();

public:
    /**
     * @brief Constructs a Report object.
     * @param a Reference to an Analyzer
     * @param output Output stream for the report
     */
    Report(Analyzer &a, ostream &output);

    /** @brief Generates the complete report and exports auxiliary CSV files. */
    void generate();
};

#endif