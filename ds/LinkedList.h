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
            std::bidirectional_iterator_tag,   // iterator_category
            Node,                      // value_type
            long,                      // difference_type
            const Node *,               // pointer
            Node                       // reference
    > {
        Node *curr;

        explicit iterator(Node *curr) : curr(curr) {
        }

        iterator &operator++() {
            curr = curr->next;
            return *this;
        }

        iterator &operator++(int) {
            auto temp = *this;
            curr = curr->next;
            return temp;
        }

        iterator &operator--() {
            curr = curr->prev;
            return *this;
        }

        iterator &operator--(int) {
            auto temp = *this;
            curr = curr->prev;
            return temp;
        }

        bool operator==(iterator b) const { return curr == b.curr; }

        bool operator!=(iterator b) const { return curr != b.curr; }

        T operator*() {
            return curr->data;
        }

    };

    Node *firstN;
    Node *lastN;


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

    void insert(T value, iterator it); //insert after node

    void append(T value);

    void remove(Node *node);

    void concat(LinkedList &tail);

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
    lastN = firstN;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    emptyList();
}

template<typename T>
void LinkedList<T>::emptyList() {
    auto it = begin();
    while (it != end()) {
        Node *curr = it.curr;
        it++;
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
typename LinkedList<T>::iterator LinkedList<T>::begin() {
    return LinkedList::iterator(firstN->next);
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::end() {
    return LinkedList::iterator(lastN->next);
}

template<typename T>
void LinkedList<T>::insert(T value, LinkedList::iterator it) {
    if(!it.curr){
        it.curr = new Node({.data = value, .next = nullptr, .prev = firstN});
        firstN->next = it.curr;
        return;
    }

    Node *n = new Node({.data = value, .next = it.curr->next, .prev = it.curr});
    if(it.curr != lastN)
        it.curr->next->prev = n;
    else
        lastN = n;
    it.curr->next = n;

}

template<typename T>
void LinkedList<T>::append(T value) {
    insert(value,end());
}



#endif //UTILLIB_LINKEDLIST_H
