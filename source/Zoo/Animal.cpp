#include "Animal.hpp"

Animal::~Animal() {
}

Animal::AnimalType Animal::type() const {
    return AT_INVALID;
}

unsigned int Animal::hungerLevel() const {
    return 0;
}

void Animal::resetToHungry() {
}

bool Animal::likesFood(const Food& food) const {
    return false;
}

unsigned int Animal::feed(Food& food) {
    return 0;
}