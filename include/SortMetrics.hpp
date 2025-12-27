#ifndef SORTMETRICS_HPP
#define SORTMETRICS_HPP

struct SortMetrics{
    long comparisons;
    long swaps;
    double elapsedTime;

    SortMetrics(): comparisons(0), swaps(0), elapsedTime(0.0) {}
};

#endif
