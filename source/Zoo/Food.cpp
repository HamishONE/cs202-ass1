#include "Food.hpp"
#include <string>

using namespace std;

Food::Food(const string& new_name, double new_cost, unsigned int new_energy) {
}

string Food::getName() const {
    // TODO: Implement
    return "";
}

double Food::getCost() const {
    // TODO: Implement
    return 0.0;
}

unsigned int Food::getQuantity() const {
    // TODO: Implement
    return 1;
}

unsigned int Food::getEnergy() const {
    // TODO: Implement
    return 0;
}

unsigned int Food::consume(unsigned int count) {
    // TODO: Implement
    return 0;
}

void Food::purchase(unsigned int quantity) {
    // TODO: Implement
}