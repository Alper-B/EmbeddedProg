#include "aviary.hpp"

void Aviary::Add(Bird* bird) {
    if (bird == nullptr) {
        throw std::logic_error("Bird pointer is NULL");
    }
    birds_.push_back(bird);
}

void Aviary::SpeakAll(std::ostream& os) const {
    for (const auto& bird : birds_) {
        bird->Speak(os);
    }
}

size_t Aviary::Size() const {
    return birds_.size();
}

Bird* Aviary::operator[](size_t idx) {
    if (idx >= birds_.size()) {
        throw std::out_of_range("Index out of bounds");
    }
    return birds_[idx];
}

const Bird* Aviary::operator[](size_t idx) const {
    if (idx >= birds_.size()) {
        throw std::out_of_range("Index out of bounds");
    }
    return birds_[idx];
}

Aviary::~Aviary() {
    for (auto bird : birds_) {
        delete bird;
    }
    birds_.clear();
}