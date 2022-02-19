#ifndef TREES_BINARYTREE_H
#define TREES_BINARYTREE_H

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

    Node* copyTree(Node* node);
    void emptyRec(Node* node);
public:
    BinaryTree();
    BinaryTree(BinaryTree& left, T element, BinaryTree& right);
    ~BinaryTree();
    void empty();
    BinaryTree leftTree();
    BinaryTree righTree();

};


template <typename T>
BinaryTree<T>::BinaryTree(): root(nullptr){}

template<typename T>
BinaryTree<T>::BinaryTree(BinaryTree& left, T element, BinaryTree& right)
{
    root = new Node({.data = element,.left = copyTree(left.root),.right = copyTree(right.root)});
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::copyTree(Node* node)
{
    if(node!=nullptr)
        return new Node({.data = node->data,.left = copyTree(node->left),.right = copyTree(node->right)});
}

template<typename T>
void BinaryTree<T>::empty()
{
    emptyRec(root);
    root = nullptr;
}

template <typename T>
void BinaryTree<T>::emptyRec(Node* node)
{
    if(node!=nullptr)
    {
        empytRec(node->left);
        emptyRec(node->right);
        delete node;
    }
}

template <typename T>
BinaryTree<T>::~BinaryTree(){empty();}

template <typename T>
BinaryTree<T> BinaryTree<T>::leftTree()
{
    return BinaryTree({.root = this->root == nullptr?nullptr:copyTree(this->root->left)});
}

#endif