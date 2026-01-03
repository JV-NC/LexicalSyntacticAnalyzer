#ifndef TOKEN_COMPARATORS_HPP
#define TOKEN_COMPARATORS_HPP

#include "Token.hpp"
#include "SortMetrics.hpp"

inline bool tokenAlpha(Token &a, Token &b, SortMetrics &m){
    m.comparisons++;
    return a.getText() < b.getText();
}

inline bool tokenFreq(Token &a, Token &b, SortMetrics &m){
    m.comparisons++;
    return a.getFrequency() > b.getFrequency();
}

#endif