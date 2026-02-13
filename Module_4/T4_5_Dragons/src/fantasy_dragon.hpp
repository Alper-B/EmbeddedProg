#pragma once

#include "dragon.hpp"

/**
 * \brief class FantasyDragon describes a fantasy dragon. Inherits from class Dragon.
 */
class FantasyDragon : public Dragon {
public:
    FantasyDragon(const std::string& name, size_t age, size_t size);

    void Eat(std::list<Food>& food) override;
    void Hoard(std::list<Treasure>& treasures) override;
};