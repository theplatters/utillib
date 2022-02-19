//
// Created by jakob on 19.02.22.
//

#ifndef UTILLIB_BINARYTREE_H
#define UTILLIB_BINARYTREE_H

template <typename T>
class BinaryTree
{
public:
    struct Node
    {
        T data;
        Node* left;
        Node* right;
    };

private:
    Node* root;
public:
    BinaryTree();
    BinaryTree(BinaryTree& left, T element, BinaryTree& right);

};


template <typename T>
BinaryTree<T>::BinaryTree(): root(nullptr){}

template<typename T>

#endif //UTILLIB_BINARYTREE_H
