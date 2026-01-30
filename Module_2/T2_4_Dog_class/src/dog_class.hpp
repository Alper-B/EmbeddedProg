#ifndef AALTO_ELEC_CPP_DOG_CLASS
#define AALTO_ELEC_CPP_DOG_CLASS

#include <string>

class Dog {
public:
    // Constructor
    Dog(int age, const std::string& name);

    // Setters
    void SetAge(int age);
    void SetName(const std::string& name);

    // Getters
    int GetAge() const;
    std::string GetName() const;

private:
    int age_;
    std::string name_;
};

#endif
