#include "Otter.hpp"

using namespace std;

Otter::Otter() {
}

Animal::AnimalType Otter::type() const {
    // TODO: Implement
    return AT_INVALID;
}

unsigned int Otter::hungerLevel() const {
    // TODO: Implement
    return 0;
}

void Otter::resetToHungry() {
    // TODO: Implement
}

bool Otter::likesFood(const Food& food) const {
    // TODO: Implement
    return false;
}

unsigned int Otter::feed(Food& food) {
    // TODO: Implement
    return 0;
}
