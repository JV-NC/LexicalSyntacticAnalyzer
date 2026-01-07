/**
 * @file Analyzer.hpp
 * @brief Defines the Analyzer class, responsible for the full lexical and syntactic analysis.
 */

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
#include "TokenComparators.hpp"
#include "ExpressionComparators.hpp"

/**
 * @class Analyzer
 * @brief Core class responsible for analyzing a text file.
 * 
 * Performs:
 * - Tokenization;
 * - Stop word filtering;
 * - Sentence and paragraph detection;
 * - Expression recognition;
 * - Punctuation balance checking;
 * - Statistical analysis;
 * - Sorting benchmarks.
 * 
 * @see HashTable
 * @see LinkedList
 * @see Queue
 * @see Stack
 * @see IntIntMap
 * @see TextReader
 * @see Sorter
 */
class Analyzer{
private:
    /** Hash table containing all tokens in the document */
    HashTable<Token> tokens;
    /** Tokens grouped per sentence */
    LinkedList<HashTable<Token>> sentenceTokens;

    /** Hash table with all expressions in the document */
    HashTable<Expression> allExpressions;
    /** Expressions grouped per paragraph */
    LinkedList<HashTable<Expression>> paragraphExpressions;

    /** Stack of unmatched punctuation symbols per paragraph */
    Queue<Stack<char>> punctuationBalance;

    /** Queue of detected sentences */
    Queue<Sentence> sentences;
    /** Queue of detected paragraphs */
    Queue<Paragraph> paragraphs;

    /** Stop words list */
    LinkedList<string> stopWords;
    /** Expressions list */
    LinkedList<string> expressions;
    /** Known abbreviations */
    LinkedList<string> abbreviations;

    /** Word length distribution map (length to frequency) */
    IntIntMap lengthDist;

    /** Sorting benchmark metrics */
    LinkedList<SortMetrics> benchmarkMetrics;
    /** Input sizes used in sorting benchmarks */
    LinkedList<int> benchmarkTests;

    /** Loads stop words from file */
    void loadStopWords(const string &filename);
    /** Loads expressions from file */
    void loadExpressions(const string &filename);
    /** Loads predefined abbreviations */
    void loadAbbreviations();
    /** Checks if character ends a sentence */
    bool isSentenceEnd(char c);
    /** Checks if character is part of a word */
    bool isWordChar(unsigned char c);
    /** Checks if a word is a stop word */
    bool isStopWord(string &word);
    /**
     * @brief Detects expressions in a line.
     * 
     * Complexity: O(E*L) where E = number of expressions and L = line length.
     * @param line The line of text to search for expressions.
     * @param lineNumber The number of the line where the expressions are found.
     * @param currentExpressions The hash table to store the expressions found in the current paragraph.
     */
    void checkExpressions(const string &line, int lineNumber, HashTable<Expression> &currentExpressions);
    /** Converts UTF-8 accented characters to ASCII */
    char utf8ToAscii(unsigned char lead, unsigned char next);
    /** Normalize a single word (lowercase, remove accents) */
    string normalizeWord(const string &word);
    /** Normalize a full line */
    string normalizeLine(const string &line);
    /**
     * @brief Finalizes a sentence when reaching sentence boundary.
     * @param sentenceNumber The current sentence number, which is incremented when the sentence is finalized.
     * @param paragraphNumber The number of the paragraph where the sentence belongs.
     * @param stopWordsNum The count of stop words in the current sentence.
     * @param nonStopWords The count of non-stop words in the current sentence.
     * @param totalWordLength The total length of non-stop words in the current sentence.
     * @param position The current position in the sentence, which determines if the sentence is finalized.
     * @param currentTokens The hash table of tokens representing the words in the current sentence.
     */
    void finalizeSentenceIfPending(int &sentenceNumber, int paragraphNumber, int &stopWordsNum, int &nonStopWords, int &totalWordLength, int &position, HashTable<Token> &currentTokens);
    /** Checks if a dot is between numbers (decimals) */
    bool isDotInNumber(const string &line, size_t i);
    /** Checks if word is an abbreviation */
    bool isAbbreviation(const string &word);

    /** Opening punctuaction symbol */
    bool isOpening(char c);
    /** Closing punctuation symbol */
    bool isClosing(char c);
    /** Checks if punctuation symbols match */
    bool matches(char open, char close);

    /**
     * @brief Generates word length distribution.
     */
    void generateLengthDistribution();
    /**
     * @brief Runs sorting benchmarks using Mergesort and Quicksort.
     * 
     * Complexity: Depends on sorting algorithm (O(n log(n))) average.
     */
    void runSortingBenchmarks();

public:
    /**
     * @brief Constructs Analyzer loading stop words and expressions.
     * @param stopWordsFilename Path of the stopWords file.
     * @param expressionsFilename Path of the expressions file.
     */
    Analyzer(const string &stopWordsFilename, const string &expressionsFilename);

    /**
     * @brief Performs full analysis over input text.
     * @param reader TextReader responsable for explore text file.
     */
    void analyze(TextReader &reader);
    /**
     * @brief Clones a token array.
     * 
     * Complexity: O(n)
     * @param src Source array.
     * @param n Array size.
     * @return Cloned Token array of size n.
     */
    Token* cloneArray(Token* src, int n);

    /** @return Reference to the HashTable containing all tokens. */
    HashTable<Token>& getTokens();
    /** @return Reference to a LinkedList of HashTable<Token>, one per sentence. */
    LinkedList<HashTable<Token>>& getSentenceTokens();
    /** @return Reference to the HashTable of all expressions. */
    HashTable<Expression>& getAllExpressions();
    /** @return Reference to a LinkedList of HashTable<Expression>, one per paragraph. */
    LinkedList<HashTable<Expression>>& getParagraphExpressions();
    /** @return Reference to the Queue of Sentence objects. */
    Queue<Sentence>& getSentences();
    /** @return Reference to the Queue of Paragraph objects. */
    Queue<Paragraph>& getParagraphs();
    /** @return Reference to a Queue of Stack<char> representing punctuation balance. */
    Queue<Stack<char>>& getPunctuationBalance();
    /** @return Reference to a LinkedList of MapEntry objects representing (length, frequency) pairs. */
    LinkedList<MapEntry>& getLengthDist();
    /** @return Reference to a LinkedList of SortMetrics objects. */
    LinkedList<SortMetrics>& getBenchmarkMetrics();
    /** @return Reference to a LinkedList of integers representing test sizes. */
    LinkedList<int>& getBenchmarkTests();
};

#endif