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
        std::cout << std::endl;
        return;
    }

    for (auto it = v.begin(); it + 1 != v.end(); ++it) {
        std::cout << *it + *(it + 1) << " ";
    }

    std::cout << std::endl;
}

void PrintSum2(const std::vector<int>& v) {
    if (v.empty()) {
        std::cout << std::endl;
        return;
    }

    auto front = v.begin();
    auto back = v.end() - 1;

    while (front < back) {
        std::cout << *front + *back << " ";
        ++front;
        --back;
    }

    std::cout << std::endl;
}
