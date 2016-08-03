#include "ZooManagementSystem.hpp"

using namespace std;

ZooManagementSystem::ZooManagementSystem(double initialBalance) {
}

ZooManagementSystem::~ZooManagementSystem() {
    // TODO: Implement
}

string ZooManagementSystem::author() {
    // TODO: Implement
    return "";
}

double ZooManagementSystem::getBalance() const {
    // TODO: Implement
    return 1.0;
}

double ZooManagementSystem::admitVisitors(unsigned int adults, unsigned int children) {
    // TODO: Implement
    return 0.0;
}

vector<Food> ZooManagementSystem::getFood() const {
    // TODO: Implement
    return vector<Food>();
}

void ZooManagementSystem::addFood(const Food& new_food) {
    // TODO: Implement
}

bool ZooManagementSystem::purchaseFood(double& cost, unsigned int index, unsigned int quantity) {
    // TODO: Implement
    return false;
}

vector<Animal*> ZooManagementSystem::getAnimals() const {
    // TODO: Implement
    return vector<Animal*>();
}

bool ZooManagementSystem::addAnimal(Animal::AnimalType new_animal_type) {
    // TODO: Implement
    return false;
}

ZooManagementSystem::FeedResult ZooManagementSystem::feedAnimal(unsigned int& quantity_eaten, unsigned int animal_index, unsigned int food_index) {
    // TODO: Implement
    return FR_SUCCESS;
}

void ZooManagementSystem::resetAllAnimals() {
    // TODO: Implement
}

void ZooManagementSystem::feedAllAnimals() {
    // TODO: Implement (leave until Task 4)
}