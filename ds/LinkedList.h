//
// Created by franzs on 18.02.22.
//

#ifndef UTILLIB_LINKEDLIST_H
#define UTILLIB_LINKEDLIST_H

template <typename T>
class LinkedList {

    struct Node {
        T data;
        Node *next;
        Node *prev;
    };

    Node *firstN;
    Node *lastN;

    Node* next(Node* node);
    Node* prev(Node* node);
    bool bol(Node* node);
    bool eol(Node* node);
    bool nodeInList(Node* node);

public:
    LinkedList();
    ~LinkedList();
    void empty();
    Node* front();
    Node* last();
    void insert(Node* node, T value); //insert after node
    void remove(Node* node);
    void concat(LinkedList& tail);
    bool isEmpty();
    Node* find(T value);
    T retrieve(Node* node);
    void printList();
    void printCompleteList(); // only for debug purposes
};
#endif //UTILLIB_LINKEDLIST_H
