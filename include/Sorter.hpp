#ifndef SORTER_HPP
#define SORTER_HPP

#include "Token.hpp"
#include "SortMetrics.hpp"

using namespace std;

class Sorter{
public:
    //MergeSort
    static void mergeSortAlpha(Token arr[], int n, SortMetrics &metrics);
    static void mergeSortFreq(Token arr[], int n, SortMetrics &metrics);

    //QuickSort
    static void quickSortAlpha(Token arr[], int n, SortMetrics &metrics);
    static void quickSortFreq(Token arr[], int n, SortMetrics &metrics);
};

#endif