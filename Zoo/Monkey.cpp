#include "Monkey.hpp"

using namespace std;

Monkey::Monkey() {
	defaultHunger = 800;
	resetToHungry();
	animalType = AT_MONKEY;
	
	foodsEaten.push_back("banana");
	foodsEaten.push_back("watermelon");
	foodsEaten.push_back("mealworms");
}