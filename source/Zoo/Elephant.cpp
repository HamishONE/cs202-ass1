#include "Elephant.hpp"

using namespace std;

Elephant::Elephant() {
}

Animal::AnimalType Elephant::type() const {
    // TODO: Implement
    return AT_INVALID;
}

unsigned int Elephant::hungerLevel() const {
    // TODO: Implement
    return 0;
}

void Elephant::resetToHungry() {
    // TODO: Implement
}

bool Elephant::likesFood(const Food& food) const {
    // TODO: Implement
    return false;
}

unsigned int Elephant::feed(Food& food) {
    // TODO: Implement
    return 0;
}