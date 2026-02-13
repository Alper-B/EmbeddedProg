#include "fantasy_dragon.hpp"

FantasyDragon::FantasyDragon(const std::string& name, size_t age, size_t size)
    : Dragon(name, age, size) {
}

void FantasyDragon::Eat(std::list<Food>& food) {
    auto it = food.begin();
    while (it != food.end()) {
        if (it->type == People || it->type == PeopleFood) {
            size_++;
            std::cout << "Fantasy dragon ate: " << it->name << std::endl;
            it = food.erase(it);
        } else {
            ++it;
        }
    }
}

void FantasyDragon::Hoard(std::list<Treasure>& treasures) {
    auto it = treasures.begin();
    while (it != treasures.end()) {
        if (it->type == Jewellery) {
            treasures_.push_back(*it);
            std::cout << "Fantasy dragon received: " << it->name << std::endl;
            it = treasures.erase(it);
        } else {
            ++it;
        }
    }
}