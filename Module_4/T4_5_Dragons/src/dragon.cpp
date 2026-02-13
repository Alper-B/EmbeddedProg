#include "dragon.hpp"

Dragon::Dragon(const std::string& name, size_t age, size_t size)
    : name_(name), age_(age), size_(size) {
}

const std::string& Dragon::GetName() const {
    return name_;
}

size_t Dragon::GetAge() const {
    return age_;
}

size_t Dragon::GetSize() const {
    return size_;
}

const std::list<Treasure>& Dragon::GetTreasures() const {
    return treasures_;
}

std::ostream& operator<<(std::ostream& os, const Dragon& dragon) {
    os << "Dragon named: " << dragon.name_ << ", age: " << dragon.age_ << ", size: " << dragon.size_ << "\n";
    os << "Treasures:\n";
    for (const auto& treasure : dragon.treasures_) {
        os << treasure.name << "\n";
    }
    return os;
}