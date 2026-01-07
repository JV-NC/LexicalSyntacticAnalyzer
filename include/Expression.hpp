/**
 * @file Expression.hpp
 * @brief Defines the Expression class.
 */

#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <string>
#include "LinkedList.hpp"

using namespace std;
/**
 * @class Expression
 * @brief Represents a multi-word expression found in the text.
 */
class Expression{
private:
    /** Expression text */
    string text;
    /** Number of occurrences */
    int frequency;
    /** Line numbers where the expression appears */
    LinkedList<int> lines;

public:
    /** Default constructor */
    Expression();
    /** Constructs an expression with given text */
    Expression(const string &t);
    /** Copy constructor */
    Expression(const Expression &other);
    /** Assignment operator */
    Expression& operator=(const Expression& other);

    /**
     * @brief Adds new occurence.
     * @param line Line of the new occurence.
     */
    void addOccurrence(int line);

    /** @return Expression text. */
    string getText();
    /** @return Expression frequency. */
    int getFrequency();
    /** @return Reference to the list of lines. */
    LinkedList<int>& getLines();
};

#endif