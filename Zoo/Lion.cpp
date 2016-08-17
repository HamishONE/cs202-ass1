#include "Lion.hpp"

using namespace std;

Lion::Lion() {
	defaultHunger = 2200;
	resetToHungry();
	animalType = AT_LION;
	
	foodsEaten.push_back("steak");
	foodsEaten.push_back("mouse");
	foodsEaten.push_back("fish");
}