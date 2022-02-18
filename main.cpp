#include <iostream>
#include <vector>
#include "sorting.h"
#include "LinkedList.h"

int main() {

    LinkedList<int> v;

    v.append(5);
    v.append(4);


    for (const auto &item : v){
        std::cout << item << " ";
    }
    return 0;
}
