#include "ZooManagementSystem.hpp"

// Define constants
#define CHILD_PRICE 5
#define ADULT_PRICE 14
#define FAMILY_PRICE 30
#define UPI "hone075"

using namespace std;

ZooManagementSystem::ZooManagementSystem(double initialBalance) {
	balance = initialBalance;
}

ZooManagementSystem::~ZooManagementSystem() {
	
	// Loop through all animals and call their destructor
    for (unsigned int i=0; i<allAnimals.size(); i++) {
		delete allAnimals[i];
	}
	
	// Empty the animals vector
	allAnimals.clear();
}

string ZooManagementSystem::author() {
    return UPI;
}

double ZooManagementSystem::getBalance() const {
    return balance;
}

double ZooManagementSystem::admitVisitors(unsigned int adults, unsigned int children) {  

	// Initialise a variable for the total cost to zero
	double cost = 0.0;	
	
	// Continue to loop while their are enough adults/children for a family pass
	while (adults >= 2 && children >=2) {
		
		// Decrement the number of adults and children by two
		adults -= 2;
		children -= 2;
		
		// Add a family pass to the price
		cost += FAMILY_PRICE;
	}
	
	// Charge remaining adults/children the standard rate
	cost += adults * ADULT_PRICE + children * CHILD_PRICE;
	
	// Add the cost to the zoos balance and return the cost
	balance += cost;
    return cost;
}

vector<Food> ZooManagementSystem::getFood() const {
    return allFoods;
}

void ZooManagementSystem::addFood(const Food& new_food) {
    allFoods.push_back(new_food);
}

bool ZooManagementSystem::purchaseFood(double& cost, unsigned int index, unsigned int quantity) {
    
	// If food index provided outside of vector range return false
	if (index >= allFoods.size()) {
		cost = 0.0;
		return false;
	}
	
	// Find the total cost for the quantity of food requested
	double costSingle = allFoods[index].getCost();
	cost = costSingle * quantity;
	
	// If the total cost exceeds the zoos balance return false
	if (cost > balance) {
		return false;
	}
	
	// Otherwise decrement the zoos balance by the cost and make the purchase
	balance -= cost;
	allFoods[index].purchase(quantity);
    return true;
}

vector<Animal*> ZooManagementSystem::getAnimals() const {
    return allAnimals;
}

bool ZooManagementSystem::addAnimal(Animal::AnimalType new_animal_type) {
	
	Animal *animal = 0;	
	
	// Create an object on the stack based on the animal type
	switch (new_animal_type) {
		case Animal::AT_LION:
			animal = new Lion();
			break;
		case Animal::AT_ELEPHANT:
			animal = new Elephant();
			break;
		case Animal::AT_MONKEY:
			animal = new Monkey();
			break;
		case Animal::AT_SNAKE:
			animal = new Snake();
			break;
		case Animal::AT_OTTER:
			animal = new Otter();
			break;
			
		// If the animal type is invalid return false
		default:
			return false;
	}
	
	// Add the new animal to the vector
    allAnimals.push_back(animal);
	return true;
}

ZooManagementSystem::FeedResult ZooManagementSystem::feedAnimal(unsigned int& quantity_eaten, 
		unsigned int animal_index, unsigned int food_index) {
	
	// Set the quantity eaten return paramter to zero
	quantity_eaten = 0;
	
	// If animal index out of vector range return invalid animal
	if (animal_index >= allAnimals.size()) {
		return FR_INVALID_ANIMAL;
	} 
	// Otherwise if food index out of vector range return invalid food
	else if (food_index >= allFoods.size()) {
		return FR_INVALID_FOOD;
	}
	
	// Get animal and food from the vectors
	Animal *animal = allAnimals[animal_index];
	Food& food = allFoods[food_index];
	
	// If the animal does not like the food return incompatiable
	if (animal->likesFood(food) == false) {
		return FR_INCOMPATIBLE;
	}
	
	// Otherwise feed the animal
	quantity_eaten = animal->feed(food);
	
	// If the animal still hungry return food exhausted
	if (animal->hungerLevel() > 0) {
		return FR_EXHAUSTED;
	}
	
	// Otherwise return success
	return FR_SUCCESS;
}

void ZooManagementSystem::resetAllAnimals() {
	
	// Loop through all animals in the vector and call resetToHungry for each
    for (unsigned int i=0; i<allAnimals.size(); i++) {
		allAnimals[i]->resetToHungry();
	}
}

// This helper function checks in an animal has already been fed
bool isAlreadyFed(unsigned int animal_index, vector<unsigned int>& animalsFed) {
	
	// Loop through the vector of animals already fed
	for (unsigned int i=0; i<animalsFed.size(); i++) {
		// If the vector matches the index provided return true
		if (animalsFed[i] == animal_index) {
			return true;
		}
	}
	
	// Otherwise return false
	return false;
}

void ZooManagementSystem::feedAllAnimals() {

	vector<unsigned int> animalsFed;
	unsigned int animal_index;
	unsigned int hunger;
	unsigned int food_index;
	unsigned int quant;
	unsigned int quantity_eaten;
	
	// Continually look for hungry animals until there are no more
	// Loop no more times than the number of animals as protection from hanging
	for (unsigned int j=0; j<allAnimals.size(); j++) {
		
		//animal_index = 0;
		hunger = 0;
		
		// Loop through all animals
		for (unsigned int i=0; i<allAnimals.size(); i++) {
			
			// Skip animal if it is already fed
			if (isAlreadyFed(i, animalsFed)) {
				continue;
			}
			
			// Find the hungriest animal
			if (allAnimals[i]->hungerLevel() > hunger) {
				animal_index = i;
				hunger = allAnimals[i]->hungerLevel();
			}
		}
		
		// If no animals are hungry (or already tried to feed them all) return
		if (hunger == 0) {
			return;
		}
		
		// Store this animal in the already fed vector
		animalsFed.push_back(animal_index);
		
		// Try to feed this animal different foods while it is hungry
		Animal *animal = allAnimals[animal_index];
		while (animal->hungerLevel() > 0) {
			
			// Loop through all foods
			quant = 0;
			for (unsigned int i=0; i<allFoods.size(); i++) {
				
				// Find the food that animal likes and the zoo has the most of
				Food& food = allFoods[i];
				if (animal->likesFood(food) && food.getQuantity() > quant) {
					quant = food.getQuantity();
					food_index = i;
				}
			}
			
			// Skip the animal if it doesn't like any food
			if (quant == 0) {
				break;
			}
			
			// Otherwise feed the animal
			feedAnimal(quantity_eaten, animal_index, food_index);
		}
	}
	
}
