//
// Created by franzs on 18.02.22.
//

#ifndef UTILLIB_LINKEDLIST_H
#define UTILLIB_LINKEDLIST_H

#include <optional>

template<typename T>
class LinkedList {

    struct Node {
        T data;
        Node *next;
        Node *prev;
    };

    struct iterator : public std::iterator<
            std::forward_iterator_tag,   // iterator_category
            Node,                      // value_type
            long,                      // difference_type
            const Node *,               // pointer
            Node                       // reference
    > {
        Node* curr;

        iterator& operator++() {
            curr = curr->next_;
            return *this;
        }

        bool operator==(iterator b) const { return curr== b.curr; }
        bool operator!=(iterator b) const { return curr != curr; }

    };

    Node *firstN;
    Node *lastN;

    Node *next(Node *node);

    Node *prev(Node *node);

    bool bol(Node *node);

    bool eol(Node *node);

    bool nodeInList(Node *node);

public:


    LinkedList();

    ~LinkedList();

    void emptyList();

    bool empty();

    T front();

    T last();

    void insert(Node *node, T value); //insert after node
    void remove(Node *node);

    void concat(LinkedList &tail);

    bool isEmpty();

    Node *find(T value);

    T retrieve(Node *node);

    void printList();

    void printCompleteList(); // only for debug purposes

    iterator begin();
    iterator end();
};

template<typename T>
LinkedList<T>::LinkedList() {
    firstN = new Node();
    firstN->next = nullptr;
    firstN->prev = nullptr;
}

template<typename T>
void LinkedList<T>::emptyList() {
    while (firstN != nullptr) {
        Node *curr = firstN;
        firstN = next(firstN);
        delete curr;
    }
    firstN = nullptr;
    lastN = nullptr;
}

template<typename T>
bool LinkedList<T>::empty() {
    return !(firstN->next);
}

template<typename T>
T LinkedList<T>::front() {
    return firstN->next->data;
}

template<typename T>
T LinkedList<T>::last() {
    return firstN->prev->data;
}

template<typename T>
void LinkedList<T>::insert(LinkedList::Node *node, T value) {

}

template<typename T>
LinkedList::iterator LinkedList<T>::begin() {
    return LinkedList::iterator();
}

template<typename T>
LinkedList::iterator LinkedList<T>::end() {
    return LinkedList::iterator();
}

#endif //UTILLIB_LINKEDLIST_H
