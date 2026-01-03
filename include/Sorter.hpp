#ifndef SORTER_HPP
#define SORTER_HPP

#include "SortMetrics.hpp"
#include <cstring>
#include <chrono>

using namespace std;
using Clock = chrono::high_resolution_clock;
//TODO: docstring and comment all .hpp .cpp files

template<typename T>
class Sorter{
using Comparator = bool (*)(T&, T&, SortMetrics&);
private:
    //MERGESORT AUX
    static void merge(T arr[], int left, int mid, int right, Comparator cmp, SortMetrics &metrics){
        int n1 = mid - left + 1;
        int n2 = right - mid;

        T *L = new T[n1];
        T *R = new T[n2];

        //copying arr to the divided arrays
        for(int i = 0; i < n1; i++) L[i] = arr[left + i];
        for(int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;

        while(i < n1 && j < n2){
            if(cmp(L[i], R[j], metrics))
                arr[k++] = L[i++];
            else
                arr[k++] = R[j++];
            metrics.swaps++;
        }

        //copying back divided arrays to arr
        while(i < n1) arr[k++] = L[i++];
        while(j < n2) arr[k++] = R[j++];

        delete[] L;
        delete[] R;
    }
    static void mergeSortRec(T arr[], int left, int right, Comparator cmp, SortMetrics &metrics){
        if(left < right){
            int mid = (left + right) / 2;
            mergeSortRec(arr, left, mid, cmp, metrics);
            mergeSortRec(arr, mid + 1, right, cmp, metrics);
            merge(arr, left, mid, right, cmp, metrics);
        }
    }
    
    //QUICKSORT AUX
    static int partition(T arr[], int low, int high, Comparator cmp, SortMetrics &metrics){
        T pivot = arr[high];
        int i = low - 1;

        for(int j = low; j < high; j++){
            if(cmp(arr[j], pivot, metrics)){
                i++;
                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                metrics.swaps++;
            }
        }

        T temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        metrics.swaps++;

        return i + 1;
    }
    static void quickSortRec(T arr[], int low, int high, Comparator cmp, SortMetrics &metrics){
        if(low < high){
            int pi = partition(arr, low, high, cmp, metrics);
            quickSortRec(arr, low, pi - 1, cmp, metrics);
            quickSortRec(arr, pi + 1, high, cmp, metrics);
        }
    }
public:
    //MERGESORT
    static void mergeSort(T arr[], int n, Comparator cmp, SortMetrics &metrics){
        auto start = Clock::now();
        mergeSortRec(arr, 0, n - 1, cmp, metrics);
        auto end = Clock::now();
        metrics.elapsedTime = std::chrono::duration<double>(end - start).count();
    }
    
    //QUICKSORT
    static void quickSort(T arr[], int n, Comparator cmp, SortMetrics &metrics){
        auto start = Clock::now();
        quickSortRec(arr, 0, n - 1, cmp, metrics);
        auto end = Clock::now();
        metrics.elapsedTime = std::chrono::duration<double>(end - start).count();
    }
};

#endif