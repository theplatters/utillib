//
// Created by franz on 19.01.22.
//

#ifndef GRAPHS_LISTGRAPH_H
#define GRAPHS_LISTGRAPH_H

#include <list>
#include <vector>
#include <iostream>
#include <queue>
#include "Edge.h"

template<typename T>
class ListGraph {
    std::vector<std::list<T *>> edges;
    std::vector<T *> vertices;

    void depthFirstSearch(T &startVertex, std::vector<T *> &visited, std::vector<Edge<T>> &reachable);

public:
    bool adjacent(T &v1, T &v2);

    std::list<T *> neighbours(T &v);

    void addVertex(T &v);

    void removeVertex(T &v);

    void addEdge(Edge<T> e);

    void removeEdge(Edge<T> e);

    std::vector<Edge<T>> depthFirstSearch(T &startVertex);

    std::vector<Edge<T>> breathFirstSearch(T &startVertex);

    void dumpGraph();
};

template<typename T>
bool ListGraph<T>::adjacent(T &v1, T &v2) {
    int v1Index = std::find(vertices.begin(), vertices.end(), &v1) - vertices.begin();

    for (auto &edge: edges[v1Index]) {
        if (edge == v2) return true;
    }

    return false;
}

template<typename T>
std::list<T *> ListGraph<T>::neighbours(T &v) {
    int vIndex = std::find(vertices.begin(), vertices.end(), &v) - vertices.begin();

    std::list<T *> neighbours{};

    for (auto &edge: edges[vIndex]) {
        neighbours.push_back(edge);
    }

    return neighbours;
}

template<typename T>
void ListGraph<T>::addVertex(T &v) {
    vertices.push_back(&v);
    edges.push_back({});
}

template<typename T>
void ListGraph<T>::removeVertex(T &v) {
    int vIndex = std::find(vertices.begin(), vertices.end(), &v) - vertices.begin();
    edges.erase(edges.begin() + vIndex);
    vertices.erase(std::remove_if(vertices.begin(), vertices.end(), [&](auto i) { return i == &v; }), vertices.end());

    for (auto &item: edges) {
        item.erase(std::remove_if(item.begin(), item.end(), [&](auto &i) { return i == &v; }), item.end());
    }
}

template<typename T>
void ListGraph<T>::addEdge(Edge<T> e) {

    int v1Index = std::find(vertices.begin(), vertices.end(), e.first()) - vertices.begin();
    int v2Index = std::find(vertices.begin(), vertices.end(), e.second()) - vertices.begin();

    edges[v1Index].push_back(e.second());
    edges[v2Index].push_back(e.first());

}

template<typename T>
void ListGraph<T>::removeEdge(Edge<T> e) {
    int v1Index = std::find(vertices.begin(), vertices.end(), e.first());
    int v2Index = std::find(vertices.begin(), vertices.end(), e.second());

    std::erase(
            std::remove_if(edges[v1Index].begin(), edges[v1Index].end(), e.second()),
            edges[v1Index].end());

    std::erase(
            std::remove_if(edges[v2Index].begin(), edges[v2Index].end(), e.first()),
            edges[v2Index].end());
}

template<typename T>
std::vector<Edge<T>> ListGraph<T>::depthFirstSearch(T &startVertex) {

    std::vector<T *> visited;
    std::vector<Edge<T>> reachable;

    depthFirstSearch(startVertex, visited, reachable);

    return reachable;
}

template<typename T>
void ListGraph<T>::depthFirstSearch(T &startVertex, std::vector<T *> &visited, std::vector<Edge<T>> &reachable) {
    int vIndex = std::find(vertices.begin(), vertices.end(), &startVertex) - vertices.begin();

    visited.push_back(&startVertex);

    for (auto &item: edges[vIndex]) {
        reachable.emplace_back(startVertex, *item);
        if (!std::any_of(visited.begin(), visited.end(), [&](auto &i) { return i == item; }))
            depthFirstSearch(*item, visited, reachable);
    }
}

template<typename T>
void ListGraph<T>::dumpGraph() {
    for (int i = 0; i < vertices.size(); ++i) {
        for (const auto &item: edges[i]) {
            std::cout << *vertices[i] << " <==> " << *item;
        }
        std::cout << "\n";
    }

}

template<typename T>
std::vector<Edge<T>> ListGraph<T>::breathFirstSearch(T &startVertex) {
    std::queue<T *> queue;
    std::vector<T *> visited = {};
    std::vector<Edge<T>> edgeVector;

    queue.push(&startVertex);

    while (!queue.empty()) {
        auto curr = queue.front();
        auto neighbourNode = neighbours(*curr);
        queue.pop();
        visited.push_back(curr);
        for (auto &n: neighbourNode) {
            if (std::find(visited.begin(), visited.end(), n) == visited.end()) {
                queue.push(n);
                edgeVector.emplace_back(*curr, *n);
            }
        }
    }

    return edgeVector;
}


#endif //GRAPHS_LISTGRAPH_H