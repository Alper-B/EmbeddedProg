#ifndef AALTO_ELEC_CPP_DOG_CLASS
#define AALTO_ELEC_CPP_DOG_CLASS

#include "mammal.hpp"
#include <string>

/**
 * \brief Inherits class Mammal.
 */
class Dog : public Mammal {
public:
    /**
     * \brief Constructor
     * \param name Name of the dog
     * \param weight Weight of the dog
     */
    Dog(const std::string& name, double weight);

    /**
     * \brief Accessor for the name
     * \return The name of the dog
     */
    std::string GetName() const;

    /**
     * \brief Static function to get the sound
     * \return "Wuff!"
     */
    static std::string MakeSound();

private:
    std::string name_;
};

#endif