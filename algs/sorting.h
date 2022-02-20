//
// Created by franzs on 18.02.22.
//

#ifndef UTILLIB_SORTING_H
#define UTILLIB_SORTING_H

#include <algorithm>
#include <cmath>


int *merge(int *arr, int *aux, int begin, int mid, int end) {
    for (int i = begin; i <= end; i++)
        aux[i] = arr[i];
    int i = begin;
    int j = mid;
    while (i < mid && j <= end) {
        if (aux[i] < aux[j]) {
            arr[begin] = aux[i];
            begin++;
            i++;
        } else {
            arr[begin] = aux[j];
            begin++;
            j++;
        }
    }
    while (i < mid)
        arr[begin++] = aux[i++];
    while (j <= end)
        arr[begin++] = aux[j++];
    return arr;
}

int *mergeSort(int *arr, int *aux, int begin, int end) {
    if (begin >= end)
        return arr;
    int mid = floor((begin + end) / 2);
    arr = mergeSort(arr, aux, begin, mid);
    arr = mergeSort(arr, aux, mid + 1, end);
    return merge(arr, aux, begin, mid + 1, end);
}


void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = source[i];
}

template<typename ForwardIt>
void selectionSort(ForwardIt beg, ForwardIt end) {
    ForwardIt m, aux;
    for (auto it = beg; it != end; it++) {
        m = it;
        for (auto j = it + 1; j < end; j++)
            if (*j < *m)
                m = j;
        std::iter_swap(it, m);
    }
}

template<typename ForwardIt>
void insertionSort(ForwardIt beg, ForwardIt end) {
    for (auto i = beg; i != end; ++i) {
        std::rotate(std::upper_bound(beg, i, *i), i, i + 1);
    }
}


template<typename ForwardIt>
ForwardIt partition(ForwardIt begin, ForwardIt end) {
    //last element is chosen as pivot
    ForwardIt piv = end;
    end--;

    while (std::distance(begin, end) >= 0) {
        if (*end > *piv)
            end--;
        else if (*begin < *piv)
            begin++;
        else
            std::iter_swap(begin++, end--);
    }
    std::iter_swap(piv, begin);
    return begin;
}

template<typename ForwardIt>
void quickSort(ForwardIt begin, ForwardIt end) {

    if (std::distance(begin, end) > 0) {
        ForwardIt split = partition(begin, end);

        quickSort(begin, std::prev(split));
        quickSort(std::next(split), end);
    }
}

#endif //UTILLIB_SORTING_H
