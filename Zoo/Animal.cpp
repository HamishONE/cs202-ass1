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
	
	// Get the name of the food
	std::string name = food.getName();
	
	// Loop through each food in the vector
	for (unsigned int i=0; i<foodsEaten.size(); i++) {
		// If the name of the food matches return true
		if (name.compare(foodsEaten[i]) == 0) {
			return true;
		}
	}
	
	// If none of the foods match return false
	return false;
}

unsigned int Animal::feed(Food& food) {
	
	// If the animal does not like the food none will be eaten
	if (likesFood(food) == false) {
		return 0;
	}
	
	unsigned int quantConsumed = 0;
	
	// Get the food energy
	unsigned int foodEnergy = food.getEnergy();
	
	// Continue looping while there is still food avaliable and the animal is hungry
	while (food.getQuantity() > 0 && hunger > 0) {
		
		// Consume one unit of food
		food.consume(1);
		
		// If the animal is hungrier than the food energy decrement the animals hunger 
		// by the food energy
		if (hunger > foodEnergy) {
			hunger -= foodEnergy;
		}
		// Otherwise set the aniamls hunger to zero
		else {
			hunger = 0;
		}
		
		// Increment the quantity consumed counter by one
		quantConsumed++;
	}
	
	return quantConsumed;
}