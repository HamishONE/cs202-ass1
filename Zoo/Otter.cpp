#include "Otter.hpp"

using namespace std;

Otter::Otter() {
	defaultHunger = 750;
	resetToHungry();
	animalType = AT_OTTER;
	
	foodsEaten.push_back("fish");
	foodsEaten.push_back("mouse");
	foodsEaten.push_back("");
}