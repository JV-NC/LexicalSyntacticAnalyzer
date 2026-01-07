/**
 * @file Token.hpp
 * @brief Defines Token class.
 */

#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include "LinkedList.hpp"
#include "Occurrence.hpp"

using namespace std;

/**
 * @brief Represents a lexical token (word) extracted from the text.
 *
 * Stores the token string, its frequency, and all its occurrences.
 * 
 * @see LinkedList
 */
class Token{
private:
    string text; ///< Token text
    int frequency; ///< Occurrence count
    LinkedList<Occurrence> occurrences; ///< List of occurrences
public:
    /** @brief Default constructor. */
    Token();
    /**
     * @brief Constructs a token with given text.
     * @param t Token string.
     */
    Token(const string &t);
    /**
     * @brief Copy constructor.
     * @param other Token to copy.
     */
    Token(const Token &other);
    /**
     * @brief Assignment operator.
     * @param other Token to assign from.
     * @return Reference to this token.
     */
    Token& operator=(const Token &other);

    /**
     * @brief Adds a new occurrence of the token.
     * @param p Paragraph number.
     * @param s Sentence number.
     * @param l Line number.
     * @param pos Position in the sentence.
     */
    void addOccurrence(int p, int s, int l, int pos);
    /** @return Token text. */
    string getText();
    /** @return Token frequency. */
    int getFrequency();
    /** @return Reference to the list of occurrences. */
    LinkedList<Occurrence>& getOccurrences();
};
#endif