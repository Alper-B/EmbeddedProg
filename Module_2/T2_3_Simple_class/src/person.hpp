#ifndef AALTO_ELEC_CPP_PERSON
#define AALTO_ELEC_CPP_PERSON

// declare your Person class here

#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

class Person {
private:
    std::string Name;
    int birthyear;

public:
    Person(const std::string& name, int year); // constructor

    std::string GetName() const;  // returns the name
    int GetAge(int year) const;   // returns age in a given year
};

#endif