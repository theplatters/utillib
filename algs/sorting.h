//
// Created by franzs on 18.02.22.
//

#ifndef UTILLIB_SORTING_H
#define UTILLIB_SORTING_H

#include <algorithm>

void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = source[i];
}

template <typename ForwardIt>
void selectionSort(ForwardIt beg, ForwardIt end) {
    ForwardIt m,aux;
    for (auto it = beg; it != end; it++) {
        m = it;
        for (auto j = it + 1; j < end; j++)
            if (*j < *m)
                m = j;
        std::iter_swap(it,m);
    }
}

template <typename ForwardIt>
void insertionSort(ForwardIt beg, ForwardIt end) {
    for (auto i = beg; i != end; ++i) {
        std::rotate(std::upper_bound(beg, i, *i), i, i+1);
    }
}

void merge(int arr[], int start, int middle, int end) {
    int aux1[middle - start + 1], aux2[end - start + 1];
    int n1 = middle - start, n2 = end - middle;
    copyArray(&arr[start], aux1, n1);
    copyArray(&arr[middle], aux2, n2);
    // instead of dealing separately with the remaining elements of
    // one of the merged arrays, we set the last element in each
    // array on the maximum possible value and in this way we are
    // guaranteed that we will finish both aux's in the main while
    aux1[n1] = aux2[n2] = INT16_MAX;

    int i = start, i1 = 0, i2 = 0;
    while (i1 < n1 || i2 < n2) {
        if (aux1[i1] < aux2[i2])
            arr[i++] = aux1[i1++];
        else
            arr[i++] = aux2[i2++];
    }
}

void mergeSort(int arr[], int start, int end) {
    if (start >= end - 1) return;
    int middle = (start + end + 1) / 2;
    mergeSort(arr, start, middle);
    mergeSort(arr, middle, end);
    merge(arr, start, middle, end);
}

template<typename ForwardIt>
ForwardIt partition(ForwardIt begin, ForwardIt end) 
{
    //last element is chosen as pivot
    ForwardIt piv = end;
    end--;

    while(std::distance(begin,end)<=0)
    {
        if(*end<*piv)
            end--;
        else if(*begin<*piv)
            begin++;
        else
            std::iter_swap(begin++,end--);
    }
    std::iter_swap(piv,begin);
    return begin;
}

template<typename ForwardIt>
void quickSort(ForwardIt begin, ForwardIt end) 
{

    if(begin <= end)
    {
        ForwardIt split = partition(begin, end);

        quickSort(begin,split);
        quickSort(++split,end);
    }
}


#endif //UTILLIB_SORTING_H
