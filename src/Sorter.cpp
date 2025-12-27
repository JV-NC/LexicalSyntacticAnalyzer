#include "../include/Sorter.hpp"
#include <cstring>
#include <chrono>

using Clock = chrono::high_resolution_clock;
//TODO: docstring and comment all .hpp .cpp files
//TODO: implement Analyzer, TextReader, Sentence, Paragraph, Report, main
//COMPARATORS
static bool compareAlpha(Token &a, Token &b, SortMetrics &m){
    m.comparisons++;
    return a.getText() < b.getText();
}

static bool compareFreq(Token &a, Token &b, SortMetrics &m){
    m.comparisons++;
    return a.getFrequency() > b.getFrequency();
}

//MERGESORT
//not in private for encapsulation
//high-order function
static void merge(Token arr[], int left, int mid, int right, bool (*cmp)(Token&, Token&, SortMetrics&), SortMetrics& metrics){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Token *L = new Token[n1];
    Token *R = new Token[n2];

    //copying arr to the divided arrays
    for(int i=0; i<n1; i++) L[i] = arr[left + i];
    for(int j=0; j<n2; j++) R[j] = arr[mid + 1 + j];

    int i=0, j=0, k=left;

    while(i<n1 && j<n2){
        if(cmp(L[i], R[j], metrics)){
            arr[k++] = L[i++];
        }else{
            arr[k++] = R[j++];
        }
        metrics.swaps++;
    }

    //copying back divided arrays to arr
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

static void mergeSortRec(Token arr[], int left, int right, bool (*cmp)(Token&, Token&, SortMetrics&), SortMetrics &metrics){
    if(left<right){
        int mid = (left+right)/2;
        mergeSortRec(arr, left, mid, cmp, metrics);
        mergeSortRec(arr, mid+1, right, cmp, metrics);
        merge(arr, left, mid, right, cmp, metrics);
    }
}

void Sorter::mergeSortAlpha(Token arr[], int n, SortMetrics &metrics){
    auto start = Clock::now();
    mergeSortRec(arr, 0, n-1, compareAlpha, metrics);
    auto end = Clock::now();
    metrics.elapsedTime = chrono::duration<double>(end - start).count();
}

void Sorter::mergeSortFreq(Token arr[], int n, SortMetrics &metrics){
    auto start = Clock::now();
    mergeSortRec(arr, 0, n-1, compareFreq, metrics);
    auto end = Clock::now();
    metrics.elapsedTime = chrono::duration<double>(end - start).count();
}

//QUICKSORT
static int partition(Token arr[], int low, int high, bool (*cmp)(Token&, Token&, SortMetrics&), SortMetrics &metrics){
    Token pivot = arr[high];
    int i = low-1;

    for(int j=low; j<high; j++){
        if(cmp(arr[j], pivot, metrics)){
            i++;
            Token temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            metrics.swaps++;
        }
    }

    Token temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    metrics.swaps++;

    return i+1;
}

static void quickSortRec(Token arr[], int low, int high, bool (*cmp)(Token&, Token&, SortMetrics&), SortMetrics &metrics){
    if(low<high){
        int pi = partition(arr, low, high, cmp, metrics);
        quickSortRec(arr, low, pi-1, cmp, metrics);
        quickSortRec(arr, pi+1, high, cmp, metrics);
    }
}

void Sorter::quickSortAlpha(Token arr[], int n, SortMetrics &metrics){
    auto start = Clock::now();
    quickSortRec(arr, 0, n-1, compareAlpha, metrics);
    auto end = Clock::now();
    metrics.elapsedTime = chrono::duration<double>(end - start).count();
}

void Sorter::quickSortFreq(Token arr[], int n, SortMetrics &metrics){
    auto start = Clock::now();
    quickSortRec(arr, 0, n-1, compareFreq, metrics);
    auto end = Clock::now();
    metrics.elapsedTime = chrono::duration<double>(end - start).count();
}