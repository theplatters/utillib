//
// Created by franzs on 18.02.22.
//

#ifndef UTILLIB_LINKEDLIST_H
#define UTILLIB_LINKEDLIST_H

#include <optional>
#include <ostream>
#include <memory>

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
        const bool usable;

        explicit iterator(Node *curr) : curr(curr), usable(true) {};

        iterator(iterator &it) : curr(it.curr), usable(it.usable) {};

        iterator(Node *curr, bool b) : curr(curr), usable(b) {
        }

        iterator &operator++() {
            curr = curr->next;
            return *this;
        }


        iterator &operator++(int) {
            auto &temp = *this;
            curr = curr->next;
            return temp;
        }

        iterator &operator--() {
            curr = curr->prev;
            return *this;
        }

        iterator &operator--(int) {
            auto &temp = *this;
            curr = curr->prev;
            return temp;
        }

        iterator &operator+(int amount) {
            for (int i = 0; i < amount; i++) {
                *this = ++(*this);
            }
            return *this;
        }

        iterator &operator-(int amount) {
            for (int i = 0; i < amount; i++) {
                *this = --(*this);
            }
            return *this;
        }

        bool operator==(iterator com) const { return curr->prev == com.curr->prev; }

        bool operator!=(iterator com) const { return curr->prev != com.curr->prev; }

        iterator operator=(iterator other) { return iterator(other); }

        T operator*() {
            return curr->data;
        }

    };

    Node *firstN;
    Node *lastN;


public:
    LinkedList();

    LinkedList(LinkedList &ll);

    LinkedList(std::initializer_list<T> initializerList);

    ~LinkedList();

    void emptyList();

    bool empty();

    T front();

    T last();

    void insert(T value, iterator it); //insert after node

    void append(T value);

    void remove(iterator it);

    void concat(LinkedList &tail);

    iterator find(T value);

    void printList();

    iterator begin();

    iterator begin() const;

    iterator end();

    iterator end() const;

    T operator[](int);
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
    if (firstN) {
        auto it = begin();
        while (it != end()) {
            Node *curr = it.curr;
            it++;
            delete curr;
        }
        firstN = nullptr;
        lastN = nullptr;
    }
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
    if (firstN->next)
        return LinkedList::iterator(firstN->next);
    return LinkedList::iterator(new Node{.prev = firstN}, false);
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin() const {
    if (firstN->next)
        return LinkedList::iterator(firstN->next);
    return LinkedList::iterator(new Node{.prev = firstN}, false);
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::end() const {
    return LinkedList::iterator(new Node{.prev = lastN});
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::end() {
    return LinkedList::iterator(new Node{.prev = lastN}, lastN != firstN);
}

template<typename T>
void LinkedList<T>::insert(T value, LinkedList::iterator it) {

    Node *insertedNode = new Node({.data = value, .next =  it.usable ? it.curr : nullptr, .prev = it.curr->prev});
    it.curr->prev->next = insertedNode;
    it.curr->prev = insertedNode;
    if (lastN == insertedNode->prev) {
        lastN = insertedNode;
    }
}

template<typename T>
void LinkedList<T>::append(T value) {
    insert(value, end());
}

template<typename T>
void LinkedList<T>::remove(LinkedList::iterator it) {
    if (it != end()) {

        if (it.curr == lastN) {
            lastN = lastN->prev;
        }
        it.curr->prev->next = it.curr->next;

        if (it.curr->next) {
            it.curr->next->prev = it.curr->prev;
        }


        delete it.curr;
    }
}

template<typename T>
void LinkedList<T>::concat(LinkedList &tail) {
    auto endIt = end();
    tail.firstN->next->prev = endIt.curr->prev;
    endIt.curr->prev->next = tail.firstN->next;
    lastN = tail.lastN;

    delete tail.firstN;
    tail.firstN = nullptr;
    tail.lastN = nullptr;

}

template<typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> initializerList) : LinkedList() {
    for (auto &item: initializerList) {
        append(item);
    }
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::find(T value) {
    for (auto it = begin(); it != end(); ++it) {
        if (*it == value) return it;
    }
    return end();
}

template<typename T>
void LinkedList<T>::printList() {
    for (const auto &item: *this) {
        std::cout << item << " -> ";
    }
    std::cout << "\n";
}

template<typename T>
T LinkedList<T>::operator[](int index) {
    auto it = begin();

    for (int i = 0; i < index; ++i) {
        it++;
    }

    return *it;
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList &ll) : LinkedList() {
    for (const auto &item: ll) {
        append(item);
    }
}

#endif //UTILLIB_LINKEDLIST_H
