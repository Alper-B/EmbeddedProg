#pragma once
#include <list>
#include <iostream>
#include "dragon.hpp"

/**
 * \brief The DragonCave class is a storage class for Dragons.
 */
class DragonCave {
public:
    DragonCave();
    ~DragonCave();

    // Disable copy constructor and assignment operator
    DragonCave(const DragonCave&) = delete;
    DragonCave& operator=(const DragonCave&) = delete;

    const std::list<Dragon*>& GetDragons() const;
    void Accommodate(Dragon* dragon);
    void Evict(const std::string& name);

    friend std::ostream& operator<<(std::ostream& os, const DragonCave& cave);

private:
    std::list<Dragon*> dragons_;
};

std::ostream& operator<<(std::ostream& os, const DragonCave& cave);