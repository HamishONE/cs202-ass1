#include "Elephant.hpp"

using namespace std;

Elephant::Elephant() {
	defaultHunger = 8400;
	resetToHungry();
	animalType = AT_ELEPHANT;
	
	foodsEaten[0] = "banana";
	foodsEaten[1] = "watermelon";
	foodsEaten[2] = "hay";
}