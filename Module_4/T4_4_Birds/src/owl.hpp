#ifndef AALTO_ELEC_CPP_OWL_CLASS
#define AALTO_ELEC_CPP_OWL_CLASS

#include "bird.hpp"

/**
 * \brief TODO: Implement the Owl class.
 */
class Owl : public Bird {
public:
    /**
     * \brief Constructor for Owl
     * \param name The name of the owl
     */
    Owl(const std::string& name) : Bird(name) {}

    /**
     * \brief Implements the Speak method
     * \param os Output stream to write to
     */
    void Speak(std::ostream& os) const override {
        os << GetName() << ": WHUU" << std::endl;
    }
};

#endif