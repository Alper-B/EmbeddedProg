#include "dragon_cave.hpp"

DragonCave::DragonCave() {
}

DragonCave::~DragonCave() {
    for (auto dragon : dragons_) {
        delete dragon;
    }
    dragons_.clear();
}

const std::list<Dragon*>& DragonCave::GetDragons() const {
    return dragons_;
}

void DragonCave::Accommodate(Dragon* dragon) {
    dragons_.push_back(dragon);
}

void DragonCave::Evict(const std::string& name) {
    for (auto it = dragons_.begin(); it != dragons_.end(); ++it) {
        if ((*it)->GetName() == name) {
            dragons_.erase(it);
            return;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const DragonCave& cave) {
    os << "DragonCave dwellers:\n\n";
    for (auto it = cave.dragons_.begin(); it != cave.dragons_.end(); ++it) {
        os << **it;
        if (std::next(it) != cave.dragons_.end()) {
            os << "\n";
        }
    }
    return os;
}