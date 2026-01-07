/**
 * @file TokenComparators.hpp
 * @brief Comparators functions for Token sorting.
 * 
 * @see Sorter
 * @see Token
 * @see SortMetrics
 */

#ifndef TOKEN_COMPARATORS_HPP
#define TOKEN_COMPARATORS_HPP

#include "Token.hpp"
#include "SortMetrics.hpp"

/**
 * @brief Alphabetical comparator for Token objects.
 *
 * @param a First token.
 * @param b Second token.
 * @param m Metrics collector.
 * @return True if a precedes b alphabetically.
 */
inline bool tokenAlpha(Token &a, Token &b, SortMetrics &m){
    m.comparisons++;
    return a.getText() < b.getText();
}

/**
 * @brief Frequency-based comparator for Token objects.
 *
 * Orders tokens from highest to lowest frequency.
 *
 * @param a First token.
 * @param b Second token.
 * @param m Metrics collector.
 * @return True if a has higher frequency than b.
 */
inline bool tokenFreq(Token &a, Token &b, SortMetrics &m){
    m.comparisons++;
    return a.getFrequency() > b.getFrequency();
}

#endif