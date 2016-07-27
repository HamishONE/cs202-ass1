#include "Food.hpp"
#include <string>

using namespace std;

Food::Food(const string& new_name, double new_cost, unsigned int new_energy) {
	name = new_name;
	cost = new_cost;
	energy = new_energy;
	quant = 0;
}

string Food::getName() const {
    return name;
}

double Food::getCost() const {
    return cost;
}

unsigned int Food::getQuantity() const {
    return quant;
}

unsigned int Food::getEnergy() const {
    return energy;
}

unsigned int Food::consume(unsigned int count) {
	unsigned int toComsume = (quant > count) ? count : quant;
	quant -= toComsume;
    return toComsume;
}

void Food::purchase(unsigned int quantity) {
    quant += quantity;
}