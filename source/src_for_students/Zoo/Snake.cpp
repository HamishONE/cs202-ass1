#include "Snake.hpp"

using namespace std;

Snake::Snake() {
}

Animal::AnimalType Snake::type() const {
    // TODO: Implement
    return AT_INVALID;
}

unsigned int Snake::hungerLevel() const {
    // TODO: Implement
    return 0;
}

void Snake::resetToHungry() {
    // TODO: Implement
}

bool Snake::likesFood(const Food& food) const {
    // TODO: Implement
    return false;
}

unsigned int Snake::feed(Food& food) {
    // TODO: Implement
    return 0;
}