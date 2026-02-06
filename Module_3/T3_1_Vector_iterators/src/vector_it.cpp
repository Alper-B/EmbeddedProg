#include "vector_it.hpp"
#include <iostream>
#include <vector>

std::vector<int> ReadVector() {
    std::vector<int> v;
    int value;
    
    while (std::cin >> value) {
        v.push_back(value);
    }
    
    return v;
}

void PrintSum1(const std::vector<int>& v) {

    if (v.size() < 2) {
        std::cout << "\n";
        return;
    }

    for (auto it = v.begin(); it != v.end() - 1; ++it) {
        std::cout << *it + *(it + 1) << " ";
    }
    std::cout << "\n";
}

void PrintSum2(const std::vector<int>& v) {
    if (v.empty()) {
        std::cout << "\n";
        return;
    }

    auto beg = v.begin();
    auto end = v.end() - 1;

    while (beg < end) {
        std::cout << *beg + *end << " ";
        
        ++beg;
        --end;
    }
    std::cout << "\n";
}