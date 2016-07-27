#include "Otter.hpp"

using namespace std;

Otter::Otter() {
	defaultHunger = 750;
	resetToHungry();
	animalType = AT_OTTER;
	
	foodsEaten[0] = "fish";
	foodsEaten[1] = "mouse";
	foodsEaten[2] = "";
}