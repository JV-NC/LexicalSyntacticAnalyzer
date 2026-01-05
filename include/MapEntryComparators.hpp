#ifndef MAPENTRYCOMPARATORS_HPP
#define MAPENTRYCOMPARATORS_HPP

#include "MapEntry.hpp"
#include "SortMetrics.hpp"

inline bool mapEntryKeyAsc(MapEntry &a, MapEntry &b, SortMetrics &m){
    m.comparisons++;
    return a.key < b.key;
}

inline bool mapEntryValueDesc(MapEntry &a, MapEntry &b, SortMetrics &m){
    m.comparisons++;
    return a.value > b.value;
}

#endif