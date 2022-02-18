#include <iostream>
#include <vector>
#include "contains.h"
#include "sorting.h"

int main() {

    std::vector<int> v = {6,2,1,3,5,8,9,12,98,15,4};

    quickSort(v.begin(),v.end());

    for (const auto &item : v){
        std::cout << item << " ";
    }
    return 0;
}
