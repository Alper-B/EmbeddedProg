#include "list.hpp"

#include <iostream>
#include <list>
#include <string>

std::istream& GetLines(std::istream& is, std::list<std::string>& list) {
    list.clear();

    std::string line;
    while (std::getline(is, line)) {
        list.push_back(line);
    }

    return is;
}

void Print(const std::list<std::string>& list) {
    for (const auto& line : list) {
        std::cout << line << std::endl;
    }
}

void SortAndUnique(std::list<std::string>& list) {
    list.sort();
    list.unique();
}
