//
// Created by Franz on 19.01.2022.
//

#ifndef GRAPHS_ADIACENCYGRAPH_H
#define GRAPHS_ADIACENCYGRAPH_H

#include <array>
#include <cstdint>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <list>
#include "Edge.h"

template<typename T, int maxVertices>
class AdiacencyGraph {
    std::array<std::array<bool, maxVertices>, maxVertices> matrix{};
    std::vector<T *> vertices;
    uint32_t size = 0;

    void depthFirstSearch(T &startVertex, std::vector<T *> &visited, std::vector<Edge<T>> &edges);

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

template<typename T, int vertices>
void AdiacencyGraph<T, vertices>::addVertex(T &v) {
    if (size++ > matrix.size()) throw std::length_error("Size limit reached");
    vertices.push_back(&v);
}

template<typename T, int verticesCount>
void AdiacencyGraph<T, verticesCount>::addEdge(Edge<T> e) {
    int v1Index = std::find(vertices.begin(), vertices.end(), e.first()) - vertices.begin();
    int v2Index = std::find(vertices.begin(), vertices.end(), e.second()) - vertices.begin();

    matrix[v1Index][v2Index] = true;
    matrix[v2Index][v1Index] = true;
}

template<typename T, int verticesCount>
bool AdiacencyGraph<T, verticesCount>::adjacent(T &v1, T &v2) {
    int v1Index = std::find(vertices.begin(), vertices.end(), &v1) - vertices.begin();
    int v2Index = std::find(vertices.begin(), vertices.end(), &v2) - vertices.begin();

    return matrix[v1Index][v2Index];
}

template<typename T, int verticesCount>
std::list<T *> AdiacencyGraph<T, verticesCount>::neighbours(T &v) {
    std::list<T *> neighbours{};
    int v1Index = std::find(vertices.begin(), vertices.end(), &v) - vertices.begin();
    for (int i = 0; i < size; ++i) {
        if (matrix[v1Index][i]){
            neighbours.push_back(vertices[i]);
        }
    }
    return neighbours;
}

template<typename T, int verticesCount>
void AdiacencyGraph<T, verticesCount>::removeVertex(T &v) {
    size--;
    int vIndex = std::find(vertices.begin(), vertices.end(), &v) - vertices.begin();
    for (auto it = matrix.begin() + vIndex; it != matrix.end(); it++) {
        std::iter_swap(it, it + 1);
    }

    for (int i = 0; i < verticesCount; ++i) {
        for (int j = size; j < verticesCount; ++j) {
            matrix[i][j] = matrix[i][j + 1];
        }
    }

    std::array<bool, verticesCount> falseArray;
    std::fill(falseArray.begin(), falseArray.end(), false);
    std::fill(matrix.begin() + size, matrix.end(), falseArray);
    for (int i = 0; i < verticesCount; ++i) {
        for (int j = size; j < verticesCount; ++j) {
            matrix[i][j] = false;
        }
    }
}

template<typename T, int verticesCount>
void AdiacencyGraph<T, verticesCount>::removeEdge(Edge<T> e) {
    int v1Index = std::find(vertices.begin(), vertices.end(), e.first()) - vertices.begin();
    int v2Index = std::find(vertices.begin(), vertices.end(), e.second()) - vertices.begin();

    matrix[v1Index][v2Index] = false;
    matrix[v2Index][v1Index] = false;

}

template<typename T, int verticesCount>
std::vector<Edge<T>> AdiacencyGraph<T, verticesCount>::depthFirstSearch(T &startVertex) {

    std::vector<T *> visited;
    std::vector<Edge<T>> edges;

    depthFirstSearch(startVertex, visited, edges);

    return edges;
}

template<typename T, int verticesCount>
void AdiacencyGraph<T, verticesCount>::depthFirstSearch(T &startVertex, std::vector<T *> &visited,
                                                        std::vector<Edge<T>> &edges) {
    int vIndex = std::find(vertices.begin(), vertices.end(), &startVertex) - vertices.begin();

    visited.push_back(&startVertex);

    for (int i = 0; i < size; ++i) {
        if (matrix[vIndex][i]) {
            edges.emplace_back(startVertex, *vertices[i]);
            if (std::find(visited.begin(), visited.end(), vertices[i]) == visited.end())
                depthFirstSearch(*vertices[i], visited, edges);
        }
    }
}

template<typename T, int verticesCount>
void AdiacencyGraph<T, verticesCount>::dumpGraph() {
    for (const auto &item: matrix) {
        for (const auto num: item) {
            std::cout << (num ? "1" : "0") << "\t";
        }
        std::cout << "\n";
    }

    for (const auto &item: vertices) {
        std::cout << *item << " ";
    }
}

template<typename T, int maxVertices>
std::vector<Edge<T>> AdiacencyGraph<T, maxVertices>::breathFirstSearch(T &startVertex) {
    std::queue<T *> queue;
    std::vector<T *> visited = {&startVertex};
    std::vector<Edge<T>> edges;

    queue.push(&startVertex);

    while (!queue.empty()) {
        auto curr = queue.front();
        auto neighbourNode = neighbours(*curr);
        queue.pop();
        visited.push_back(curr);
        for (auto& n: neighbourNode) {
            if (std::find(visited.begin(), visited.end(), n) == visited.end()) {
                queue.push(n);
                edges.emplace_back(*curr, *n);
            }
        }
    }

    return edges;
}


#endif //GRAPHS_ADIACENCYGRAPH_H