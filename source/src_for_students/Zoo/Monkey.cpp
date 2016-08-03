#include "Monkey.hpp"

using namespace std;

Monkey::Monkey() {
}

Animal::AnimalType Monkey::type() const {
    // TODO: Implement
    return AT_INVALID;
}

unsigned int Monkey::hungerLevel() const {
    // TODO: Implement
    return 0;
}

void Monkey::resetToHungry() {
    // TODO: Implement
}

bool Monkey::likesFood(const Food& food) const {
    // TODO: Implement
    return false;
}

unsigned int Monkey::feed(Food& food) {
    // TODO: Implement
    return 0;
}