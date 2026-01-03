#ifndef EXPRESSION_COMPARATORS_HPP
#define EXPRESSION_COMPARATORS_HPP

#include "Expression.hpp"
#include "SortMetrics.hpp"

inline bool expressionAlpha(Expression &a, Expression &b, SortMetrics &m){
    m.comparisons++;
    return a.getText() < b.getText();
}

inline bool expressionFreq(Expression &a, Expression &b, SortMetrics &m){
    m.comparisons++;
    return a.getFrequency() > b.getFrequency();
}

#endif