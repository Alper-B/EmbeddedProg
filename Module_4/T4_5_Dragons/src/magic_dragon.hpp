#pragma once

#include "dragon.hpp"

/**
 * \brief class MagicDragon describes a magic dragon. Inherits from class Dragon.
 */
class MagicDragon : public Dragon {
public:
    MagicDragon(const std::string& name, size_t age, size_t size);

    void Eat(std::list<Food>& food) override;
    void Hoard(std::list<Treasure>& treasures) override;
};