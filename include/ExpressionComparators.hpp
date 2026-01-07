/**
 * @file ExpressionComparators.hpp
 * @brief Comparators functions for Expression sorting.
 * 
 * @see Sorter
 * @see Expression
 * @see SortMetrics
 */

#ifndef EXPRESSION_COMPARATORS_HPP
#define EXPRESSION_COMPARATORS_HPP

#include "Expression.hpp"
#include "SortMetrics.hpp"

/**
 * @brief Alphabetical comparator.
 * @param a First expression.
 * @param b Second expression.
 * @param m Sort Metrics used on Sorter.
 * @return Correct alphabetical order.
 */
inline bool expressionAlpha(Expression &a, Expression &b, SortMetrics &m){
    m.comparisons++;
    return a.getText() < b.getText();
}
/**
 * @brief Frequency comparator (descending).
 * @param a First expression.
 * @param b Second expression.
 * @param m Sort Metrics used on Sorter.
 * @return Correct descending frequency order.
 */
inline bool expressionFreq(Expression &a, Expression &b, SortMetrics &m){
    m.comparisons++;
    return a.getFrequency() > b.getFrequency();
}

#endif