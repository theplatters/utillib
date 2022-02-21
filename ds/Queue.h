//
// Created by Franz on 19.02.2022.
//

#ifndef UTILLIB_QUEUE_H
#define UTILLIB_QUEUE_H

#include <array>
#include <cstdint>
#include <stdexcept>

template <typename T, int Size = 100>
class Queue {
    std::array<T, Size> array;

    uint32_t indexFront = 0;
    uint32_t indexEnd = 0;


public:
    void push(T val);

    T pop();

    T front();


};

template<typename T, int Size>
void Queue<T, Size>::push(T val) {
    if(indexEnd == UINT32_MAX){
        indexFront = indexFront % Size;
        indexEnd = indexEnd % Size;
    }

    if(indexEnd - indexFront >= Size){
        throw std::range_error("The queue is full");
    }

    array[(indexEnd++) % Size] = val;
}

template<typename T, int Size>
T Queue<T, Size>::pop() {
    if(indexEnd - indexFront == 0){
        throw std::range_error("The queue is empty");
    }

    return array[(indexFront++) % Size];
}

template<typename T, int Size>
T Queue<T, Size>::front() {
    return array[indexFront % Size];
}

#endif //UTILLIB_QUEUE_H
