#include "dog.hpp"

// Constructor: Initializes the base Mammal class with weight, 
// and the local name_ variable with name.
Dog::Dog(const std::string& name, double weight) : Mammal(weight), name_(name) {
}

std::string Dog::GetName() const {
    return name_;
}

// Static member function
std::string Dog::MakeSound() {
    return "Wuff!";
}