cmake_minimum_required(VERSION 3.21)
project(utillib)

set(CMAKE_CXX_STANDARD 20)

include_directories(algs ds)

add_executable(utillib main.cpp algs/contains.h algs/sorting.h ds/Edge.h ds/AdiacencyGraph.h ds/ListGraph.h ds/DirectedListGraph.h ds/LinkedList.h ds/Queue.h ds/BinaryTree.h)
