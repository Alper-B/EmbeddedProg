#include "vector_strings.hpp"

#include <iostream>
#include <vector>

void Adder(std::vector<std::string>& names) {
    std::cout << "Enter a name:\n";
    std::string name;
    if (std::cin >> name) {
        names.push_back(name);
        std::cout << "Number of names in the vector:\n" << names.size() << '\n';
    }
}

void Remover(std::vector<std::string>& names) {
    if (names.empty()) return;
    std::string removed = names.back();
    names.pop_back();
    std::cout << "Removing the last element:\n" << removed << '\n';
}

void Printer(std::vector<std::string>& names) {
    for (const auto& s : names) {
        std::cout << s << '\n';
    }
}

void CMDReader() {
    std::vector<std::string> names;
    std::cout << "Commands: ADD, PRINT, REMOVE, QUIT\n";
    while (true) {
        std::cout << "Enter a command:\n";
        std::string cmd;
        if (!(std::cin >> cmd)) break;

        if (cmd == "ADD") {
            Adder(names);
        } else if (cmd == "PRINT") {
            Printer(names);
        } else if (cmd == "REMOVE") {
            Remover(names);
        } else if (cmd == "QUIT") {
            break;
        }
     
    }
}
