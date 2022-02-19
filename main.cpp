#include <iostream>
#include <vector>
#include "sorting.h"
#include "LinkedList.h"
#include "BinaryTree.h"
#include <cmath>

int* merge(int* arr, int* aux, int begin, int mid, int end)
{
    for(int i=begin;i<=end;i++)
        aux[i]=arr[i];
    int i = begin;
    int j = mid;
    while(i<mid && j<end)
    {
        if(aux[i]<aux[j])
            arr[begin++] = aux[i++];
        else
            arr[begin++] = aux[j++];
    }
    while(i<=mid)
        arr[begin++] = aux[i++];
    while(j<=end)
        arr[begin++] = aux[j++];
    return arr;
}

int* mergeSort(int* arr, int* aux, int begin, int end)
{
    if(begin>=end)
        return arr;
    int mid = floor((begin+end)/2);
    arr = mergeSort(arr,aux,begin,mid);
    arr = mergeSort(arr,aux,mid+1,end);
    return merge(arr,aux,begin,mid+1,end);
}

int main() {

//    BinaryTree<int> tree[6];
//    tree[0].makeTree(tree[5],1,tree[5]);
//    tree[1].makeTree(tree[5],2,tree[5]);
//    tree[2].makeTree(tree[5],3,tree[5]);
//    tree[3].makeTree(tree[0],4,tree[1]);
//    tree[4].makeTree(tree[2],5,tree[3]);
//
//   BinaryTree<int> t1(tree[4],7,tree[3]);
//   t1.printBinaryTree();

    //    LinkedList<int> v;
//
//    v.append(5);
//    v.append(4);
//
//
//    for (const auto &item : v){
//        std::cout << item << " ";
//    }

        srand(time(0));
        int n = 10;
        int* arr = new int[n];
        int* aux = new int[n];
        // int arr[n];
        // int aux[n];


        for(int i=0;i<n;i++)
        {
            arr[i] = rand()%(10*n);
            std::cout << arr[i] << std::endl;
        }
        std::cout << std::endl;
        mergeSort(arr,aux,0,n);

        for(int i=0;i<n;i++)
            std::cout << arr[i] << std::endl;

        delete arr;
        delete aux;
        return 0;

    return 0;
}
