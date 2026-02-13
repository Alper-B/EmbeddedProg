#ifndef AALTO_ELEC_CPP_CAT_CLASS
#define AALTO_ELEC_CPP_CAT_CLASS

#include "mammal.hpp"
#include <string>

/**
 * \brief Inherits class Mammal.
 */
class Cat : public Mammal {
public:
    /**
     * \brief Constructor
     * \param name Name of the cat
     * \param weight Weight of the cat
     */
    Cat(const std::string& name, double weight);

    /**
     * \brief Accessor for the name
     * \return The name of the cat
     */
    std::string GetName() const;

    /**
     * \brief Static function to get the sound
     * \return "Meow"
     */
    static std::string MakeSound();

private:
    std::string name_;
};

#endif