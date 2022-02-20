#include <iostream>

#ifndef BINARYTREE_H
#define BINARYTREE_H
template <typename T>
class BinaryTree
{
private:
    struct Node
    {
        T data;
        Node* left;
        Node* right;
    };
    Node* root;

    Node* copyTree(Node* node);
    void emptyRec(Node* node);
    void printBinaryTreeRec(Node* node);
public:
    BinaryTree();
    BinaryTree(Node* node);
    BinaryTree(BinaryTree& left, T element, BinaryTree& right);
    ~BinaryTree();
    void empty();
    bool isEmpty();
    void makeTree(BinaryTree& left, T element, BinaryTree& right);
    BinaryTree leftTree();
    BinaryTree rightTree();
    T key();
    void printBinaryTree();

};



template <typename T>
BinaryTree<T>::BinaryTree(): root(nullptr){}

template <typename T>
BinaryTree<T>::BinaryTree(Node* node):root(copyTree(node)){}

template<typename T>
BinaryTree<T>::BinaryTree(BinaryTree& left, T element, BinaryTree& right)
{
    root = new Node({.data = element,.left = copyTree(left.root),.right = copyTree(right.root)});
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::copyTree(Node* node)
{
    if(node==nullptr)
        return node;
    return new Node({.data = node->data,.left = copyTree(node->left),.right = copyTree(node->right)});
}

template <typename T>
BinaryTree<T>::~BinaryTree(){empty();}

template <typename T>
void BinaryTree<T>::emptyRec(Node* node)
{
    if(node!=nullptr)
    {
        emptyRec(node->left);
        emptyRec(node->right);
        delete node;
    }
}

template<typename T>
void BinaryTree<T>::empty()
{
    emptyRec(root);
    root = nullptr;
}

template <typename T>
bool BinaryTree<T>::isEmpty(){return root==nullptr;}

template<typename T>
void BinaryTree<T>::makeTree(BinaryTree& left, T element, BinaryTree& right)
{
    if(isEmpty())
        root = new Node({.data = element,.left = copyTree(left.root), .right = copyTree(right.root)});
    else
        std::cout << "Tree non-empty, cannot make new tree" << std::endl;

}

template <typename T>
BinaryTree<T> BinaryTree<T>::leftTree()
{
    return BinaryTree(this->root == nullptr?nullptr:copyTree(this->root->left));
}

template <typename T>
BinaryTree<T> BinaryTree<T>::rightTree()
{
    return BinaryTree(this->root == nullptr?nullptr:copyTree(this->root->right));
}

template <typename T>
T BinaryTree<T>::key()
{
    if(isEmpty())
    {
        T dummy;
        std::cout << "Tree is empty, cannot retrieve key" << std::endl;
        return dummy;
    }
    return root->data;
}

template <typename T>
void BinaryTree<T>::printBinaryTree(){std::cout <<"["; printBinaryTreeRec(root); std::cout <<"]" << std::endl;}

template <typename T>
void BinaryTree<T>::printBinaryTreeRec(Node* node)
{
    if(node!= nullptr)
    {
        printBinaryTreeRec(node->left);
        std::cout << node->data << " ";
        printBinaryTreeRec(node->right);
    }
}

#endif