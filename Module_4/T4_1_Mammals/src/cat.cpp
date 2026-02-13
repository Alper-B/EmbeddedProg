#include "cat.hpp"

// Constructor: Initializes the base Mammal class with weight, 
// and the local name_ variable with name.
Cat::Cat(const std::string& name, double weight) : Mammal(weight), name_(name) {
}

std::string Cat::GetName() const {
    return name_;
}

// Static member function
std::string Cat::MakeSound() {
    return "Meow";
}