#include "Animal.hpp"

Animal::~Animal() {
}

Animal::AnimalType Animal::type() const {
    return animalType;
}

unsigned int Animal::hungerLevel() const {
    return hunger;
}

void Animal::resetToHungry() {
	hunger = defaultHunger;
}

bool Animal::likesFood(const Food& food) const {
		
	std::string name = food.getName();
	for (unsigned int i=0; i<foodsEaten.size(); i++) {
		if (name.compare(foodsEaten[i]) == 0) return true;
	}
	return false;
}

unsigned int Animal::feed(Food& food) {
	
	if (!likesFood(food)) return 0;
	
	unsigned int quant = 0;
	unsigned int energy = food.getEnergy();
	
	while (food.getQuantity() > 0 && hunger > 0) {
		food.consume(1);
		if (hunger > energy) hunger -= energy;
		else hunger = 0;
		quant++;
	}
	
	return quant;
}