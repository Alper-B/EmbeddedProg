#include "magic_dragon.hpp"

MagicDragon::MagicDragon(const std::string& name, size_t age, size_t size)
    : Dragon(name, age, size) {
}

void MagicDragon::Eat(std::list<Food>& food) {
    auto it = food.begin();
    while (it != food.end()) {
        if (it->type == Herbs) {
            size_++;
            std::cout << "Magic dragon ate: " << it->name << "\n";
            it = food.erase(it);
        } else {
            ++it;
        }
    }
}

void MagicDragon::Hoard(std::list<Treasure>& treasures) {
    auto it = treasures.begin();
    while (it != treasures.end()) {
        if (it->type == Potions) {
            treasures_.push_back(*it);
            std::cout << "Magic dragon received: " << it->name << "\n";
            it = treasures.erase(it);
        } else {
            ++it;
        }
    }
}