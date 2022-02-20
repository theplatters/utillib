#include <iostream>
#include <vector>
#include "sorting.h"
#include "LinkedList.h"
#include "BinaryTree.h"
#include <cmath>

using namespace std;

int main() {
    BinaryTree<int> tree[10];

    cout << endl << "Create tree:" << endl;
    tree[0].makeTree(tree[9], 1, tree[9]);
    tree[0].printBinaryTree();
    tree[1].makeTree(tree[9], 2, tree[9]);
    tree[1].printBinaryTree();
    tree[2].makeTree(tree[9], 3, tree[9]);
    tree[2].printBinaryTree();
    tree[3].makeTree(tree[9], 4, tree[9]);
    tree[3].printBinaryTree();
    tree[4].makeTree(tree[9], 5, tree[9]);
    tree[4].printBinaryTree();
    tree[5].makeTree(tree[0], 6, tree[1]);
    tree[5].printBinaryTree();
    tree[6].makeTree(tree[2], 7, tree[3]);
    tree[6].printBinaryTree();
    tree[7].makeTree(tree[5], 8, tree[6]);
    tree[7].printBinaryTree();
    tree[8].makeTree(tree[7], 9, tree[4]);
    tree[8].printBinaryTree();

    cout << endl << "Fail when trying to make a tree when one exists already: ";
    tree[8].makeTree(tree[7], 9, tree[4]);
    tree[8].printBinaryTree();

    cout << endl << "Retrieve information from the big tree:" << endl;
    cout << "The root is " << tree[8].key() << endl;
    cout << "The left subtree is ";
    tree[8].leftTree().printBinaryTree();
    cout << "The root of the left subtree is " << tree[8].leftTree().key() << endl;
    cout << "The right subtree is ";
    tree[8].rightTree().printBinaryTree();
    cout << "The root of the right subtree is " << tree[8].rightTree().key() << endl;

    cout << endl << "Empty trees:" << endl;
    tree[8].empty();
    cout << "We emptied the tree: ";
    tree[8].printBinaryTree();
    cout << "Try to retrieve its key: " << endl;
    tree[8].key();







}
