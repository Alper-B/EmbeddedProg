#ifndef AALTO_ELEC_CPP_DUCK_CLASS
#define AALTO_ELEC_CPP_DUCK_CLASS

#include "bird.hpp"

/**
 * \brief TODO: Implement the Duck class.
 */
class Duck : public Bird {
public:
    /**
     * \brief Constructor for Duck
     * \param name The name of the duck
     */
    Duck(const std::string& name) : Bird(name) {}

    /**
     * \brief Implements the Speak method
     * \param os Output stream to write to
     */
    void Speak(std::ostream& os) const override {
        os << GetName() << ": QUACK" << std::endl;
    }
};

#endif