// pokemon.cpp
#include "pokemon.hpp"

#include <algorithm> // not strictly necessary but fine to include

PokemonCollection::PokemonCollection(PokemonCollection collection,
                                     PokemonCollection collection2) {
    // copy pokemons from first collection
    pokemons_ = collection.pokemons_;

    // append pokemons from second collection
    pokemons_.insert(pokemons_.end(),
                     collection2.pokemons_.begin(),
                     collection2.pokemons_.end());

    // sort so duplicates become adjacent (sort by name, then id)
    pokemons_.sort([](const std::pair<std::string, size_t> &a,
                      const std::pair<std::string, size_t> &b) {
        if (a.first < b.first) return true;
        if (b.first < a.first) return false;
        return a.second < b.second;
    });

    // remove consecutive duplicates (same name and same id)
    pokemons_.unique([](const std::pair<std::string, size_t> &a,
                        const std::pair<std::string, size_t> &b) {
        return a.first == b.first && a.second == b.second;
    });
}

void PokemonCollection::Add(const std::string &name, size_t id) {
    pokemons_.emplace_back(name, id);
}

bool PokemonCollection::Remove(const std::string &name, size_t id) {
    for (auto it = pokemons_.begin(); it != pokemons_.end(); ++it) {
        if (it->first == name && it->second == id) {
            pokemons_.erase(it);
            return true;
        }
    }
    return false;
}

void PokemonCollection::Print() const {
    for (const auto &p : pokemons_) {
        std::cout << "id: " << p.second << ", name: " << p.first << std::endl;
    }
}

void PokemonCollection::SortByName() {
    pokemons_.sort([](const std::pair<std::string, size_t> &a,
                      const std::pair<std::string, size_t> &b) {
        if (a.first < b.first) return true;
        if (b.first < a.first) return false;
        return a.second < b.second;
    });
}

void PokemonCollection::SortById() {
    pokemons_.sort([](const std::pair<std::string, size_t> &a,
                      const std::pair<std::string, size_t> &b) {
        if (a.second < b.second) return true;
        if (b.second < a.second) return false;
        return a.first < b.first;
    });
}
