#include "dog_class.hpp"

// Constructor
Dog::Dog(int age, const std::string& name) : age_(age), name_(name) {}

// Setters
void Dog::SetAge(int age) {
    age_ = age;
}

void Dog::SetName(const std::string& name) {
    name_ = name;
}

// Getters
int Dog::GetAge() const {
    return age_;
}

std::string Dog::GetName() const {
    return name_;
}