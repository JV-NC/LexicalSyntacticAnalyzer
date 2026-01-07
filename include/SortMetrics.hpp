/**
 * @file SortMetrics.hpp
 * @brief Defines SortMetrics struct.
 */

#ifndef SORTMETRICS_HPP
#define SORTMETRICS_HPP

/**
 * @struct SortMetrics
 * @brief Stores performance metrics of a sorting algorithm.
 *
 * Used to collect empirical data such as comparisons, swaps, and elapsed execution time.
 */
struct SortMetrics{
    long comparisons; ///< Number of comparisons
    long swaps; ///< Number of swaps
    double elapsedTime; ///< Execution time in seconds

    /** @brief Initializes all metrics to zero. */
    SortMetrics(): comparisons(0), swaps(0), elapsedTime(0.0) {}

    /** @brief Resets all metrics. */
    void clear() {
        comparisons = 0;
        swaps = 0;
        elapsedTime = 0.0;
    }
};

#endif
