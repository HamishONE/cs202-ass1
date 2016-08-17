#include "Elephant.hpp"

using namespace std;

Elephant::Elephant() {
	defaultHunger = 8400;
	resetToHungry();
	animalType = AT_ELEPHANT;
	
	foodsEaten.push_back("banana");
	foodsEaten.push_back("watermelon");
	foodsEaten.push_back("hay");
}