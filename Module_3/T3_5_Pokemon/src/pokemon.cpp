#include "pokemon.hpp"
#include <algorithm> // for std::unique, std::remove_if
#include <iostream>

PokemonCollection::PokemonCollection(PokemonCollection collection1,
                                     PokemonCollection collection2) {
    // Merge both collections
    pokemons_ = collection1.pokemons_;
    pokemons_.insert(pokemons_.end(), collection2.pokemons_.begin(), collection2.pokemons_.end());

    // Sort first so duplicates are consecutive
    pokemons_.sort([](const auto &a, const auto &b) {
        return a.first < b.first || (a.first == b.first && a.second < b.second);
    });

    // Remove duplicates
    pokemons_.unique([](const auto &a, const auto &b) {
        return a.first == b.first && a.second == b.second;
    });
}

void PokemonCollection::Add(const std::string &name, size_t id) {
    pokemons_.emplace_back(name, id);
}

bool PokemonCollection::Remove(const std::string &name, size_t id) {
    auto it = std::find_if(pokemons_.begin(), pokemons_.end(),
                           [&](const auto &p) { return p.first == name && p.second == id; });
    if (it != pokemons_.end()) {
        pokemons_.erase(it);
        return true;
    }
    return false;
}

void PokemonCollection::Print() const {
    for (const auto &p : pokemons_) {
        std::cout << "id: " << p.second << ", name: " << p.first << "\n";
    }
}

void PokemonCollection::SortByName() {
    pokemons_.sort([](const auto &a, const auto &b) {
        return a.first < b.first || (a.first == b.first && a.second < b.second);
    });
}

void PokemonCollection::SortById() {
    pokemons_.sort([](const auto &a, const auto &b) {
        return a.second < b.second || (a.second == b.second && a.first < b.first);
    });
}
