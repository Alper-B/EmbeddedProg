#pragma once

#include <iostream>
#include <list>
#include <string>

/* Enumeration types for the different treasures */
enum TreasureType
{
    Jewellery,
    Wisdom,
    Potions
};

/* Implementation of Treasure */
struct Treasure
{
    TreasureType type;
    std::string name;
};

/* Enumeration types for the different foods */
enum FoodType
{
    PeopleFood,
    People,
    Herbs
};

/* Implementation of Food */
struct Food
{
    FoodType type;
    std::string name;
};

/**
 * \brief class Dragon is an abstract class that describes a dragon.
 */
class Dragon {
public:
    Dragon(const std::string& name, size_t age, size_t size);
    
    virtual ~Dragon() {}

    const std::string& GetName() const;
    size_t GetAge() const;
    size_t GetSize() const;
    const std::list<Treasure>& GetTreasures() const;

    virtual void Eat(std::list<Food>& food) = 0;
    virtual void Hoard(std::list<Treasure>& treasures) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Dragon& dragon);

protected:
    std::string name_;
    size_t age_;
    size_t size_;
    std::list<Treasure> treasures_;
};

std::ostream& operator<<(std::ostream& os, const Dragon& dragon);