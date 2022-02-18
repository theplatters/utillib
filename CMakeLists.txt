cmake_minimum_required(VERSION 3.21)
project(utillib)

set(CMAKE_CXX_STANDARD 20)

include_directories(algs d)

add_executable(utillib main.cpp algs/contains.h algs/sorting.h ds/Edge.h ds/AdiacencyGraph.h ds/ListGraph.h)
