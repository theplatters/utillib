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

        bool operator==(iterator b) const { return curr->prev == b.curr->prev; }

        bool operator!=(iterator b) const { return curr->prev != b.curr->prev; }

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

    void remove(iterator it);

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
    if(firstN->next)
        return LinkedList::iterator(firstN->next);
    return LinkedList::iterator(new Node{.prev = firstN});
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::end() {
    return LinkedList::iterator(new Node{.prev = lastN});
}

template<typename T>
void LinkedList<T>::insert(T value, LinkedList::iterator it){
    Node* n = new Node({.data = value, .next = it.curr, .prev = it.curr->prev});
        it.curr->prev->next = n;
        it.curr->prev = n;
        if(lastN == n->prev){
            lastN = n;
        }
}

template<typename T>
void LinkedList<T>::append(T value) {
    insert(value, end());
}

template<typename T>
void LinkedList<T>::remove(LinkedList::iterator it) {
    it.curr->prev->next = it.curr->next;
    it.curr->next->prev = it.curr->prev;

    delete it.curr;
}


#endif //UTILLIB_LINKEDLIST_H
