//
// Created by franz on 27.01.22.
//

#ifndef GRAPHS_DIRECTEDLISTGRAPH_H
#define GRAPHS_DIRECTEDLISTGRAPH_H

#include <list>
#include <vector>
#include <iostream>
#include <queue>
#include "Edge.h"

template<typename T>
class DirectedListGraph {
    std::vector<std::list<T *>> edges;
    std::vector<T *> vertices;

    void dfsMod(T *node, std::vector<T *> &notVisited, std::vector<T *> &dfsVisited,
                std::vector<T *> &sorted);

    void depthFirstSearch(T &startVertex, std::vector<T *> &visited, std::vector<Edge<T>> &reachable);

public:
    DirectedListGraph(std::initializer_list<std::reference_wrapper<T>> t);

    DirectedListGraph() = default;

    bool adjacent(T &v1, T &v2);

    std::vector<T *> neighbours(T &v);

    void addVertex(T &v);

    void removeVertex(T &v);

    void addEdge(Edge<T> e);

    void removeEdge(Edge<T> e);

    std::vector<Edge<T>> depthFirstSearch(T &startVertex);

    std::vector<Edge<T>> breathFirstSearch(T &startVertex);

    void dumpGraph();

    std::list<T *> topologicalSorting();

    std::vector<T *> topologicalSortingDFS();
};

template<typename T>
void
DirectedListGraph<T>::depthFirstSearch(T &startVertex, std::vector<T *> &visited, std::vector<Edge<T>> &reachable) {
    int vIndex = std::find(vertices.begin(), vertices.end(), &startVertex) - vertices.begin();

    visited.push_back(&startVertex);

    for (auto &item: edges[vIndex]) {
        reachable.emplace_back(startVertex, *item);
        if (!std::any_of(visited.begin(), visited.end(), [&](auto &i) { return i == item; }))
            depthFirstSearch(*item, visited, reachable);
    }
}

template<typename T>
bool DirectedListGraph<T>::adjacent(T &v1, T &v2) {
    int v1Index = std::find(vertices.begin(), vertices.end(), &v1) - vertices.begin();

    for (auto &edge: edges[v1Index]) {
        if (edge == v2) return true;
    }

    return false;
}

template<typename T>
std::vector<T *> DirectedListGraph<T>::neighbours(T &v) {
    int vIndex = std::find(vertices.begin(), vertices.end(), &v) - vertices.begin();

    std::vector<T *> neighbours{};

    for (auto &edge: edges[vIndex]) {
        neighbours.push_back(edge);
    }

    return neighbours;
}

template<typename T>
void DirectedListGraph<T>::addVertex(T &v) {
    vertices.push_back(&v);
    edges.push_back({});
}

template<typename T>
void DirectedListGraph<T>::removeVertex(T &v) {
    int vIndex = std::find(vertices.begin(), vertices.end(), &v) - vertices.begin();
    edges.erase(edges.begin() + vIndex);
    vertices.erase(std::remove_if(vertices.begin(), vertices.end(), [&](auto i) { return i == &v; }), vertices.end());

    for (auto &item: edges) {
        item.erase(std::remove_if(item.begin(), item.end(), [&](auto &i) { return i == &v; }), item.end());
    }
}

template<typename T>
void DirectedListGraph<T>::addEdge(Edge<T> e) {
    int v1Index = std::find(vertices.begin(), vertices.end(), e.first()) - vertices.begin();
    edges[v1Index].push_back(e.second());
}

template<typename T>
void DirectedListGraph<T>::removeEdge(Edge<T> e) {
    int v1Index = std::find(vertices.begin(), vertices.end(), e.first());

    std::erase(
            std::remove_if(edges[v1Index].begin(), edges[v1Index].end(), e.second()),
            edges[v1Index].end());
}

template<typename T>
std::vector<Edge<T>> DirectedListGraph<T>::depthFirstSearch(T &startVertex) {


    std::vector<T *> visited;
    std::vector<Edge<T>> reachable;

    depthFirstSearch(startVertex, visited, reachable);

    return reachable;
}

template<typename T>
std::vector<Edge<T>> DirectedListGraph<T>::breathFirstSearch(T &startVertex) {
    std::queue<T *> queue;
    std::vector<T *> visited{};
    std::vector<Edge<T>> edges;

    queue.push(&startVertex);

    while (!queue.empty()) {
        auto curr = queue.front();
        auto neighbourNode = neighbours(*curr);
        visited.push_back(curr);
        queue.pop();
        for (auto &n: neighbourNode) {
            if (std::find(visited.begin(), visited.end(), n) == visited.end()) {
                queue.push(n);
                edges.emplace_back(*curr, *n);
            }
        }
    }

    return edges;
}

template<typename T>
void DirectedListGraph<T>::dumpGraph() {
    for (int i = 0; i < vertices.size(); ++i) {
        for (const auto &item: edges[i]) {
            std::cout << *vertices[i] << " <==> " << *item << " ";
        }
        std::cout << "\n";
    }
}

template<typename T>
std::list<T *> DirectedListGraph<T>::topologicalSorting() {
    std::list<T *> sortedVertices;
    std::vector<std::list<T *>> edgeCopy{};
    std::queue<T *> l;

    for (const auto &item : edges){
        edgeCopy.push_back(item);
    }

    for (const auto &item: vertices) {
        bool flag = false;
        for (int i = 0; i < edges.size(); ++i) {
            if (std::find(edges[i].begin(), edges[i].end(), item) != edges[i].end()) {
                flag = true;
            }
        }
        if (!flag) l.push(item);
    }

    while (!l.empty()) {
        T *v = l.front();
        sortedVertices.push_back(v);
        l.pop();

        int vIndex = std::find(vertices.begin(), vertices.end(), v) - vertices.begin();
        for (auto it = edgeCopy[vIndex].begin(); it != edgeCopy[vIndex].end(); it++) {
            edgeCopy[vIndex].erase(it);
            for (const auto &item: vertices) {
                bool flag = false;
                for (int i = 0; i < edgeCopy.size(); ++i) {
                    if (std::find(edgeCopy[i].begin(), edgeCopy[i].end(), item) != edgeCopy[i].end()) {
                        flag = true;
                    }
                }
                if (!flag) l.push(item);
            }
        }
    }

    return sortedVertices;
}


template<typename T>
DirectedListGraph<T>::DirectedListGraph(std::initializer_list<std::reference_wrapper<T>> t) : edges{}, vertices{} {
    for (const auto &item: t) {
        addVertex(item);
    }
}

template<typename T>
std::vector<T *> DirectedListGraph<T>::topologicalSortingDFS() {
    std::vector<T *> notVisited{};
    std::vector<T *> sorted{};
    std::vector<T *> dfsVisited{};

    for (const auto &item : vertices){
        notVisited.push_back(item);
    }

    while (!notVisited.empty()) {
        auto temp = notVisited.back();
        notVisited.pop_back();
        dfsMod(temp, notVisited, dfsVisited, sorted);
    }

    return sorted;
}

template<typename T>
void DirectedListGraph<T>::dfsMod(T *node, std::vector<T *> &notVisited, std::vector<T *> &dfsVisited,
                                  std::vector<T *> &sorted) {
    if (std::find(notVisited.begin(), notVisited.end(), node) == notVisited.end())
        return;
    if (std::find(dfsVisited.begin(), dfsVisited.end(), node) != dfsVisited.end())
        throw std::range_error("Graph has a cycle");

    dfsVisited.push_back(node);

    for (const auto &n: neighbours(*node)) {
        dfsMod(n, notVisited, dfsVisited, sorted);
    }

    notVisited.erase(std::remove(notVisited.begin(), notVisited.end(), node), notVisited.end());
    sorted.push_back(node);
}


#endif //GRAPHS_DIRECTEDLISTGRAPH_H