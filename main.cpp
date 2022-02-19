#include <iostream>
#include <vector>
#include "sorting.h"
#include "LinkedList.h"
#include "BinaryTree.h"

int main() {

    BinaryTree<int> tree[6];
    tree[0].makeTree(tree[5],1,tree[5]);
    tree[1].makeTree(tree[5],2,tree[5]);
    tree[2].makeTree(tree[5],3,tree[5]);
    tree[3].makeTree(tree[0],4,tree[1]);
    //tree[4].makeTree(tree[2],5,tree[3]);

   //BinaryTree<int> t1(tree[0],7,tree[2]);

    LinkedList<int> v = {1,2,3,4};
    LinkedList<int> v2 = {5,6,7,8};

    v.concat(v2);

    for (const auto &item : v){
        std::cout << item << " ";
    }
    return 0;
}
