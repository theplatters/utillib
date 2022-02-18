//
// Created by Franz on 19.01.2022.
//

#ifndef GRAPHS_EDGE_H
#define GRAPHS_EDGE_H


#include <memory>

template<typename T>
class Edge {
    std::pair<T *, T *> edge;

public:
    Edge(T &v1, T &v2);
    T* first();
    T* second();

    const std::pair<T *, T *> &getEdge() const;
};

template<typename T>
Edge<T>::Edge(T &v1, T &v2) {
    edge = std::make_pair(&v1, &v2);
}

template<typename T>
const std::pair<T *, T *> &Edge<T>::getEdge() const {
    return edge;
}

template<typename T>
T *Edge<T>::first() {
    return edge.first;
}

template<typename T>
T *Edge<T>::second() {
    return edge.second;
}


#endif //GRAPHS_EDGE_H