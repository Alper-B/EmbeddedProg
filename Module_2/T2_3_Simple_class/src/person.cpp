#include "person.hpp"

Person::Person(const std::string& name, int year) : Name(name), birthyear(year) {}

std::string Person::GetName() const {
    return Name;
}

int Person::GetAge(int year) const {
    return year - birthyear;
}