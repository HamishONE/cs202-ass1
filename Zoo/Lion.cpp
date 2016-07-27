#include "Lion.hpp"

#include "Food.hpp"

using namespace std;

Lion::Lion() {
	defaultHunger = 2200;
	resetToHungry();
	animalType = AT_LION;
	
	foodsEaten[0] = "steak";
	foodsEaten[1] = "mouse";
	foodsEaten[2] = "fish";
}