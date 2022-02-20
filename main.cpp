#include <iostream>
#include <vector>
#include "sorting.h"
#include "LinkedList.h"
#include "Queue.h"
#include "BinaryTree.h"
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

void testJakobMerge(){


    srand(time(0));
    int n = 10;
    int *arr = new int[n];
    int *aux = new int[n];
    // int arr[n];
    // int aux[n];


    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (10 * n);
        std::cout << arr[i] << std::endl;
    }
    std::cout << std::endl;
    mergeSort(arr, aux, 0, n);

    for (int i = 0; i < n; i++)
        std::cout << arr[i] << std::endl;

    delete[] arr;
    delete[] aux;

}

int main() {

    LinkedList<int> t = {1,2,3,4,5};
    LinkedList<int> t2 = {6,7,8,9,10};

    t.insert(10,t.end()-1);

    t.concat(t2);
    t.remove(t.find(6));


    return 0;
}
