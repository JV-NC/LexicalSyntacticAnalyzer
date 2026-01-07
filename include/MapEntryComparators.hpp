/**
 * @file MapEntryComparators.hpp
 * @brief Comparators functions for Expression sorting.
 * 
 * @see Sorter
 * @see MapEntry
 * @see SortMetrics
 */

#ifndef MAPENTRYCOMPARATORS_HPP
#define MAPENTRYCOMPARATORS_HPP

#include "MapEntry.hpp"
#include "SortMetrics.hpp"

/**
 * @brief Comparator for ascending key order.
 *
 * @param a First entry.
 * @param b Second entry.
 * @param m Metrics collector.
 * @return True if a.key < b.key.
 */
inline bool mapEntryKeyAsc(MapEntry &a, MapEntry &b, SortMetrics &m){
    m.comparisons++;
    return a.key < b.key;
}

/**
 * @brief Comparator for descending value order.
 *
 * @param a First entry.
 * @param b Second entry.
 * @param m Metrics collector.
 * @return True if a.value > b.value.
 */
inline bool mapEntryValueDesc(MapEntry &a, MapEntry &b, SortMetrics &m){
    m.comparisons++;
    return a.value > b.value;
}

#endif