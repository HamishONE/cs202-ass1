#include "Lion.hpp"

#include "Food.hpp"

using namespace std;

Lion::Lion() {
}

Animal::AnimalType Lion::type() const {
    // TODO: Implement
    return AT_INVALID;
}

unsigned int Lion::hungerLevel() const {
    // TODO: Implement
    return 0;
}

void Lion::resetToHungry() {
    // TODO: Implement
}

bool Lion::likesFood(const Food& food) const {
    // TODO: Implement
    return false;
}

unsigned int Lion::feed(Food& food) {
    // TODO: Implement
    return 0;
}