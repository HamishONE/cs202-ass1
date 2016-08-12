#include "ZooManagementSystem.hpp"

#define CHILD_PRICE 5
#define ADULT_PRICE 14
#define FAMILY_PRICE 30
#define UPI "hone075"

using namespace std;

ZooManagementSystem::ZooManagementSystem(double initialBalance) {
	balance = initialBalance;
}

ZooManagementSystem::~ZooManagementSystem() {
    for (unsigned int i=0; i<allAnimals.size(); i++) {
		delete allAnimals[i];
	}
	allAnimals.clear();
}

string ZooManagementSystem::author() {
    return UPI;
}

double ZooManagementSystem::getBalance() const {
    return balance;
}

double ZooManagementSystem::admitVisitors(unsigned int adults, unsigned int children) {  
	double cost = 0.0;	
	while (adults >= 2 && children >=2) {
		adults -= 2;
		children -= 2;
		cost += FAMILY_PRICE;
	}
	cost += adults * ADULT_PRICE + children * CHILD_PRICE;
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
    
	if (index >= allFoods.size()) {
		cost = 0.0;
		return false;
	}
	
	double costSingle = allFoods[index].getCost();
	cost = costSingle * quantity;
	
	if (cost > balance) return false;	
	balance -= cost;
	allFoods[index].purchase(quantity);
    return true;
}

vector<Animal*> ZooManagementSystem::getAnimals() const {
    return allAnimals;
}

bool ZooManagementSystem::addAnimal(Animal::AnimalType new_animal_type) {
	// TRY TO MAKE NICER
	Animal *animal;	
	if (new_animal_type == Animal::AT_MONKEY) animal = new Monkey();
	else if (new_animal_type == Animal::AT_LION) animal = new Lion();
	else if (new_animal_type == Animal::AT_ELEPHANT) animal = new Elephant();
	else if (new_animal_type == Animal::AT_SNAKE) animal = new Snake();
	else if (new_animal_type == Animal::AT_OTTER) animal = new Otter();
	else return false;
	
    allAnimals.push_back(animal);
	return true;
}

ZooManagementSystem::FeedResult ZooManagementSystem::feedAnimal(unsigned int& quantity_eaten, unsigned int animal_index, unsigned int food_index) {
	quantity_eaten = 0;
	if (animal_index >= allAnimals.size()) return FR_INVALID_ANIMAL;
	else if (food_index >= allFoods.size()) return FR_INVALID_FOOD;
	
	Animal *animal = allAnimals[animal_index];
	Food& food = allFoods[food_index];
	
	if (animal->likesFood(food) == false) return FR_INCOMPATIBLE;
	
	quantity_eaten = animal->feed(food);
	
	if (animal->hungerLevel() > 0) return FR_EXHAUSTED;	
    else return FR_SUCCESS;
}

void ZooManagementSystem::resetAllAnimals() {
    for (unsigned int i=0; i<allAnimals.size(); i++) {
		allAnimals[i]->resetToHungry();
	}
}

bool isAlreadyFed(unsigned int animal_index, vector<unsigned int>& animalsFed) {
	for (unsigned int i=0; i<animalsFed.size(); i++) {
		if (animalsFed[i] == animal_index) return true;
	}
	return false;
}

void ZooManagementSystem::feedAllAnimals() {

	vector<unsigned int> animalsFed;
	
	// Continually look for hungry animals
	// Loop no more times than the number of animals as protection from hanging
	for (unsigned int j=0; j<allAnimals.size(); j++) {
		
		// Find hungriest animal
		unsigned int animal_index = 0;
		unsigned int hunger = 0;
		for (unsigned int i=0; i<allAnimals.size(); i++) {
			if (isAlreadyFed(i, animalsFed)) continue;
			if (allAnimals[i]->hungerLevel() > hunger) {
				animal_index = i;
				hunger = allAnimals[i]->hungerLevel();
			}
		}
		
		// If no animals hungry (or already tried to feed all) return
		if (hunger == 0) return;
		
		// Store animal in already fed vector
		animalsFed.push_back(animal_index);
		
		// Cotinaully try to feed animal different foods
		Animal *animal = allAnimals[animal_index];
		while (animal->hungerLevel() > 0) { // TODO: ADD HANGING PROTECTION
			
			// Find food that animal likes and zoo has most off_type
			unsigned int food_index;
			unsigned int quant = 0;
			for (unsigned int i=0; i<allFoods.size(); i++) {
				Food& food = allFoods[i];
				if (animal->likesFood(food) && food.getQuantity() > quant) {
					quant = food.getQuantity();
					food_index = i;
				}
			}
			
			// Skip animal if it doesn't like any food
			if (quant == 0) break;
			
			// Otherwise feed the animal
			unsigned int quantity_eaten;
			feedAnimal(quantity_eaten, animal_index, food_index);
		}
	}
	
}

