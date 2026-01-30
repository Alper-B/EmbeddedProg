#ifndef AALTO_ELEC_CPP_PERSON
#define AALTO_ELEC_CPP_PERSON

#include <string>

class Person {
private:
    std::string Name;
    int birthyear;

public:
    Person(const std::string& name, int year);
    std::string GetName() const;
    int GetAge(int year) const;
};

#endif